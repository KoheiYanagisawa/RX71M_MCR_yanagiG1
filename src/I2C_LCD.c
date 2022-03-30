//====================================
// �C���N���[�h
//====================================
#include "I2C_LCD.h"
//====================================
// �O���[�o���ϐ��̐錾
//====================================
// LCD�֘A
static volatile uint8_t		buffLcdData[ LCD_MAX_X / LCD_MAX_Y ];		// �\���o�b�t�@
static uint8_t				buffLcdData2[ LCD_MAX_X / LCD_MAX_Y + 10 ]; 	// �\���o�b�t�@�ꎞ��ƃG���A
static volatile uint32_t	lcdBuffPosition;				// �o�b�t�@�ɏ������ވʒu
static volatile uint32_t	lcdMode2 = 1;					// �\������No�Ǘ�
static volatile uint32_t	lcdNowLocate;					// ���݂̕\�����Ă���ʒu
static volatile uint32_t	lcdRefreshFlag;					// ���t���b�V���t���O

uint8_t	busLCD = BUS_LCD_FREE;
/////////////////////////////////////////////////////////////////////////
// ���W���[���� lcd_put
// �����T�v     �f�[�^���M
// ����         data
// �߂�l       �Ȃ�
/////////////////////////////////////////////////////////////////////////
void lcd_put( uint8_t data )
{
	uint8_t word[2] = { RSBIT1, data };
	I2C_LCD_SEND;
	busLCD = BUS_LCD_BUSY;
	while(busLCD)__nop();
}
//////////////////////////////////////////////////////////////////////////
// ���W���[���� lcd_CMD
// �����T�v     �R�}���h���M
// ����         cmd
// �߂�l       �Ȃ�
//////////////////////////////////////////////////////////////////////////
void lcd_CMD( uint8_t cmd ) 
{
	uint8_t Command[2] = { RSBIT0, cmd };
 	I2C_LCD_CMD;
	busLCD = BUS_LCD_BUSY;
	while(busLCD)__nop();
}
//////////////////////////////////////////////////////////////////////////
// ���W���[���� wait_lcd
// �����T�v     �x������
// ����         �x������(ms)
// �߂�l       �Ȃ�
//////////////////////////////////////////////////////////////////////////
void wait_lcd ( uint16_t waitTime )
{
	volatile uint32_t time, i = 0;
	
	time = (uint32_t)waitTime * ( CLOCK * 1000 )/ 10;
	for ( i = 0; i < time; i++) __nop();
}
//////////////////////////////////////////////////////////////////////////
// ���W���[���� inti_lcd
// �����T�v     LCD�̏�����
// ����         �Ȃ�
// �߂�l       �Ȃ�
//////////////////////////////////////////////////////////////////////////
 void inti_lcd(void)
 {
	wait_lcd(4);
	lcd_CMD(0x38);	// function set				: �f�[�^����8�{�E�\���͂Q�s�E�t�H���g��5x8�h�b�g
	wait_lcd(1);
	lcd_CMD(0x39);	// function set           	: �g���R�}���h�̐ݒ��L���ɂ���
	wait_lcd(1);
	lcd_CMD(0x14);	// Internal OSC frequency 	: �o�C�A�X�̑I���Ɠ���OSC���g���̒���
	wait_lcd(1);
	lcd_CMD(0x70);	// Contrast set          	: �R���g���X�g�����f�[�^(����4�r�b�g)
	wait_lcd(1);
	lcd_CMD(0x56);	// Power/ICON/Contrast control	: ������H�L���A�R���g���X�g�����f�[�^(���2�r�b�g)
	wait_lcd(1);
	lcd_CMD(0x6c);	// Follower control     	: �t�H���A��H��ON�A�������̒������s��
	wait_lcd(200);
	lcd_CMD(0x38);	// function set         	: �g���R�}���h��ݒ�𖳌��ɂ���
	wait_lcd(1);
	lcd_CMD(0x0c);	// display ON/OFF control	: ��ʕ\����ON�E�J�[�\���\����OFF�E�J�[�\���_�ł�OFF
	wait_lcd(1);
	lcd_CMD(0x01);	// Clear Display 			: ��ʑS�̂�20H�̽�߰��ŕ\���A���ق�col=0,row=0�Ɉړ�
	wait_lcd(2);
}
//////////////////////////////////////////////////////////////////////////
// ���W���[���� lcdLocate
// �����T�v     �t���J�[�\���ړ�
// ����         x , y
// �߂�l       �Ȃ�
//////////////////////////////////////////////////////////////////////////
static void lcdLocate( uint32_t x, uint32_t y )
{
    volatile uint8_t work = 0x80;

    // x�̌v�Z
    work += x;

    // y�̌v�Z
    if( y == 1 ) {
        work += 0x40;
    } else if( y == 2 ) {
        work += 0x14;
    } else if( y == 3 ) {
        work += 0x54;
    }

    // �J�[�\���ړ�
    lcd_CMD(work);
}
//////////////////////////////////////////////////////////////////////////
// ���W���[���� lcdShowProcess
// �����T�v     �t���\������
// ����         �Ȃ�
// �߂�l       �Ȃ�
// ����         ���̊֐��͊��荞�݂�1ms���ƂɎ��s���Ă�������
//////////////////////////////////////////////////////////////////////////
void lcdShowProcess( void )
{
    switch( lcdMode2 ) {
    case 1: // �f�[�^�X�V���ꂽ���`�F�b�N
    	if( lcdRefreshFlag ) {
    		lcdRefreshFlag = 0;
    		lcdMode2 = 2;
	}
        break;

    case 2: // �ʒu������
	lcdNowLocate = 0;
    	lcdLocate( 0, 0 );
	lcdMode2 = 3;
        break;

    case 3: // ���s�ʒu�̊m�F 
	if( lcdNowLocate % LCD_MAX_X == 0 ) {
    		lcdLocate( 0, lcdNowLocate / LCD_MAX_X );
	}
	lcdMode2 = 4;
        break;

    case 4: // �f�[�^�\������
	lcd_put(buffLcdData[ lcdNowLocate++ ]);
	if( lcdNowLocate >= LCD_MAX_X * LCD_MAX_Y ) {
		lcdMode2 = 1;
	} else {
		lcdMode2 = 3;
	}
	break;

    default:
	lcdMode2 = 1;
   	break;
    }
}
//////////////////////////////////////////////////////////////////////////
// ���W���[���� lcdPrintf
// �����T�v     �t���֕\�� �\���ʒu�͉ߋ��ɕ\�������ʒu�̎�����
// ����         printf�Ɠ���
// �߂�l       ���펞�F�o�͂��������� �ُ펞�F���̐�
//////////////////////////////////////////////////////////////////////////
int32_t lcdPrintf(uint8_t *format, ...)
{
    volatile va_list	argptr;
    volatile uint8_t	*p;
    volatile uint16_t	ret = 0;

    va_start(argptr, format);
    ret = vsprintf( buffLcdData2, format, argptr );
    va_end(argptr);

    if( ret > 0 ) {
        // vsprintf������Ȃ�t���o�b�t�@�֓]��
        p = buffLcdData2;
        while( *p ) {
            buffLcdData[lcdBuffPosition++] = *p++;
            if( lcdBuffPosition >= LCD_MAX_X * LCD_MAX_Y ) {
                lcdBuffPosition = 0;
            }
        }
        lcdRefreshFlag = 1;
    }
    return ret;
}
//////////////////////////////////////////////////////////////////////////
// ���W���[���� lcdPosition
// �����T�v     �t���̕\���ʒu�w��
// ����         ���ʒu , �c�ʒu
// �߂�l       �Ȃ�
//////////////////////////////////////////////////////////////////////////
void lcdPosition(uint8_t x ,uint8_t y)
{
    if( x >= LCD_MAX_X ) return;
    if( y >= LCD_MAX_Y ) return;

    lcdBuffPosition = x + y * LCD_MAX_X;
}