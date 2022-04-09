//====================================
// �C���N���[�h
//====================================
#include "AD12.h"
//====================================
// �O���[�o���ϐ��̐錾
//====================================


//�@�^�C�}�֘A
static char				ADTimer10;	// AD�ϊ��J�E���g�p

//�@�Z���T�֘A
//  AD�ϊ����ʊi�[
uint16_t            A0_Sen[8];              //AD0�`�����l���̊i�[��
uint16_t            A1_Sen[14];             //AD1�`�����l���̊i�[��

short               Angle0;                 //�T�[�{�Z���^�[�l
short	            sensorG_th = GATE_VAL;	// �Q�[�g�J���������l

///////////////////////////////////////////////////
// ���W���[���� init_AD
// �����T�v     AD�̏�����
// ����         �Ȃ�
// �߂�l      	�Ȃ�
///////////////////////////////////////////////////
void init_AD(void){
	MTU4.TGRD = 5998;						//�g���[�X�Z���T�[�pPWM
}


///////////////////////////////////////////////////
// ���W���[���� inttrruptAD0
// �����T�v   	AD0�̕ϊ��I�����荞��
// ����         �Ȃ�
// �߂�l       �Ȃ�
///////////////////////////////////////////////////
void inttrruptAD0(void) {
    R_Config_S12AD0_Get_ValueResult(ADCHANNEL2,&potentio);
    R_Config_S12AD0_Get_ValueResult(ADCHANNEL4,&gatesensor);
    R_Config_S12AD0_Get_ValueResult(ADCHANNEL5,&sensorLL);
    R_Config_S12AD0_Get_ValueResult(ADCHANNEL6,&sensorL);
    R_Config_S12AD0_Get_ValueResult(ADCHANNEL7,&sensorC);
}
///////////////////////////////////////////////////
// ���W���[���� inttrruptAD1
// �����T�v   	AD1�̕ϊ��I�����荞��
// ����         �Ȃ�
// �߂�l       �Ȃ�
///////////////////////////////////////////////////
void inttrruptAD1(void) {
    R_Config_S12AD1_Get_ValueResult(ADCHANNEL8,&sensorR);
    R_Config_S12AD1_Get_ValueResult(ADCHANNEL9,&sensorRR);
}
///////////////////////////////////////////////////////////////////////////
// ���W���[���� getServoAngle
// �����T�v     �|�e���V�������[�^�[�̃A�i���O�l�Ŏ擾
// ����         �Ȃ�
// �߂�l       �Z���T�l
///////////////////////////////////////////////////////////////////////////
short getServoAngle(void) 
{	
	return  ( Angle0 - potentio );
}
///////////////////////////////////////////////////////////////////////////
// ���W���[���� getAnalogSensor
// �����T�v     �A�i���O�Z���T�̃A�i���O�l�Ŏ擾
// ����         �Ȃ�
// �߂�l       �Z���T�l
///////////////////////////////////////////////////////////////////////////
short getAnalogSensor(void) 
{
	return sensorR - sensorL;
}
///////////////////////////////////////////////////////////////////////////
// ���W���[���� sensor_inp
// �����T�v     �f�W�^���Z���T�̒l��16�i���Ŏ擾
// ����         �Ȃ�
// �߂�l       �Z���T�l0�`
///////////////////////////////////////////////////////////////////////////
unsigned char sensor_inp(void) 
{
	char l, c, r;
	
	if (sensorRR < 500 ) r = 0x1;
	else r = 0;
	if (sensorC < 500 ) c = 0x2;
	else c = 0;
	if (sensorLL < 500 ) l = 0x4;
	else l = 0;
	
	return l+c+r;
}
///////////////////////////////////////////////////////////////////////////
// ���W���[���� startbar_get
// �����T�v     �X�^�[�g�Q�[�g�̊J�̊m�F
// ����         �Ȃ�
// �߂�l       0; ���Ă��� 1; �J���Ă���
///////////////////////////////////////////////////////////////////////////
unsigned char startbar_get(void) 
{
	char ret;
	
	if ( gatesensor <= sensorG_th )	ret = 1;
	else			ret = 0;
	
	return ret;
}