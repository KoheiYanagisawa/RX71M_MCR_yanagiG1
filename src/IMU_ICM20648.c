//=====================================
// �C���N���[�h
//=====================================
#include "IMU_ICM20648.h"
//====================================
// �O���[�o���ϐ��̐錾
//====================================
// IMU����擾�����f�[�^
volatile int32_t 	rawXa = 0, rawYa = 0, rawZa = 0;	// �����x(16bit�f�[�^)
volatile int32_t 	rawXg = 0, rawYg = 0, rawZg = 0;	// �p�����x(16bit�f�[�^)

volatile int16_t 	rawTemp;			// ���x(16bit�f�[�^)

// �f�[�^����
double 	TurningAngleIMU;	// IMU���狁�߂����[�p�x
double	RollAngleIMU;		// IMU���狁�߂����[�������p�x
double 	PichAngleIMU;		// IMU���狁�߂��s�b�`�����p�x
double	TempIMU;			// IMU�̉��x
int16_t	offsetX, offsetY, offsetZ;		// �I�t�Z�b�g�l(16bit)

uint8_t	whoami;
uint8_t cnt_imu = 0;
uint8_t	busIMU = BUS_IMU_FREE;

///////////////////////////////////////////////////////////////////////////
// ���W���[���� wait_IMU
// �����T�v   	�x������
// ����         �x������(ms)
// �߂�l       �Ȃ�
///////////////////////////////////////////////////////////////////////////
void wait_IMU ( uint16_t waitTime )
{
	volatile int32_t time, i = 0;
	
	time = (int32_t)waitTime * ( CLOCK * 1000 ) / 10;
	for ( i = 0; i < time; i++) __nop();
}
///////////////////////////////////////////////////////////////
// ���W���[���� IMUWriteByte
// �����T�v   	�w�肵�����W�X�^�Ƀf�[�^����������
// ����         reg:���W�X�^�̃A�h���X data:�������݃f�[�^
// �߂�l       �Ȃ�
///////////////////////////////////////////////////////////////
void IMUWriteByte( uint8_t reg, uint8_t data )
{
	uint8_t data_tr[2] = { reg, data }, data_re[2], numS = 2, numR = 2;
	
	#if USECOM == 0
		I2C_IMU_COMMAND;		// �R�}���h���M
		busIMU = BUS_IMU_BUSY;
		while(busIMU)__nop();
	#else
		SPI_IMU_CS = 0;
		SPI_IMU_SEND;
		busIMU = BUS_IMU_BUSY;
		while(busIMU)__nop();
		SPI_IMU_CS = 1;
	#endif
}
/////////////////////////////////////////////////////////
// ���W���[���� IMUReadByte
// �����T�v   	�w�肵�����W�X�^�̃f�[�^��ǂ�
// ����         reg:���W�X�^�̃A�h���X
// �߂�l       ���W�X�^�̒l
/////////////////////////////////////////////////////////
uint8_t IMUReadByte( uint8_t reg )
{
	uint8_t data_tr[2] = { reg | 0x80 }, data_re[2], numS = 2, numR = 2;
  	
	#if USECOM == 0
		I2C_IMU_COMMAND;		// �R�}���h���M
		busIMU = BUS_IMU_BUSY;SPI_IMU_CS = 0;
		while(busIMU)__nop();
		I2C_IMU_RECIVE;		// �f�[�^��M
		busIMU = BUS_IMU_BUSY;
		while(busIMU)__nop();
	# else
		// �A�h���X���M
		SPI_IMU_CS = 0;
		SPI_IMU_SEND;
		busIMU = BUS_IMU_BUSY;
		while(busIMU)__nop();
		SPI_IMU_CS = 1;
	#endif
	
	return data_re[1];
}
///////////////////////////////////////////////////////////////////////////////////////////////////
// ���W���[���� IMUReadArry
// �����T�v   	�w�肵�����W�X�^����w��̐������f�[�^��ǂ�
// ����         reg:���W�X�^�̃A�h���X num2 �󂯎��f�[�^�̐� reciveData �擾�f�[�^���i�[����z��
// �߂�l       �Ȃ�
///////////////////////////////////////////////////////////////////////////////////////////////////
void IMUReadArry( uint8_t reg, uint8_t num2, uint8_t* data_re )
{
	uint8_t data_tr[20] = { reg | 0x80 }, numS = num2+1, numR = num2+1;
	
	#if USECOM == 0
		I2C_IMU_COMMAND;
		busIMU = BUS_IMU_BUSY;
		while(busIMU)__nop();
		I2C_IMU_ARRY;
		busIMU = BUS_IMU_BUSY;
		while(busIMU)__nop();
	# else
		SPI_IMU_CS = 0;
		SPI_IMU_SEND;
		busIMU = BUS_IMU_BUSY;
		while(busIMU)__nop();
		SPI_IMU_CS = 1;
	#endif
}
///////////////////////////////////////////////////
// ���W���[���� init_IMU
// �����T�v   	IMU�̏�����
// ����         �Ȃ�
// �߂�l       0: ���������s 1: ����������
///////////////////////////////////////////////////
bool init_IMU (void)
{
	bool ret=false;
	#if USECOM == 1
		SPI_IMU_CS = 1;
	#endif
	if (IMUReadByte(0x0) == 0xE0) {
		ret = true;
		IMUWriteByte( PWR_MGMT_1, 0x01);	// �X���[�v���[�h����
		IMUWriteByte( USER_CTRL, 0x10);		// ���X�@�\�����@SPIonly
		IMUWriteByte( REG_BANK_SEL, 0x20);	// USER_BANK2��L����
		IMUWriteByte( GYRO_CONFIG_1, 0x17);	// �p���x�����W�}2000dps DLPF enable DLPFCFG = 2
		IMUWriteByte( ACCEL_CONFIG, 0x06);	// �����x�����W�}16g
		IMUWriteByte( REG_BANK_SEL, 0x00);	// USER_BANK0��L����
	}

	return ret;
}
///////////////////////////////////////////////////
// ���W���[���� caribrateIMU
// �����T�v   	�e���̃L�����u���[�V����
// ����         �Ȃ�
// �߂�l       �Ȃ�
///////////////////////////////////////////////////
void caribrateIMU (void) {
	int32_t sumXg=0, sumYg=0,sumZg=0, test = -10000;
	int16_t test2;
	uint8_t axisData[14];
	// X,Y���͊�ɍ��킹�ē���ւ��Ă���

	for (uint16_t i=0;i<SAMPLE;i++) {
		IMUReadArry( GYRO_XOUT_H, 6, axisData);
		sumYg += (int16_t)( (axisData[1] << 8 & 0xff00 ) | axisData[2] );
		sumXg += (int16_t)( (axisData[3] << 8 & 0xff00 ) | axisData[4] );
		sumZg += (int16_t)( (axisData[5] << 8 & 0xff00 ) | axisData[6] );
	}
	
	offsetX = sumXg/SAMPLE;
	offsetY = sumYg/SAMPLE;
	offsetZ = sumZg/SAMPLE;

	printf("x: %d y: %d z: %d\n",offsetX,offsetY,offsetZ);

	TurningAngleIMU = 0;
	RollAngleIMU = 0;
	PichAngleIMU = 0;
}
///////////////////////////////////////////////////
// ���W���[���� IMUProcess
// �����T�v   	�Z���Z�f�[�^�̎擾
// ����         �Ȃ�
// �߂�l       �Ȃ�
///////////////////////////////////////////////////
void getIMUdata (void)
{
	uint8_t 	axisData[14];	// �p�����x�A���x��8bit�����f�[�^�i�[��
	// X,Y���͊�ɍ��킹�ē���ւ��Ă���

	IMUReadArry( ACCEL_XOUT_H, 12, axisData);
	rawYa = (short)( (axisData[1] << 8 & 0xff00 ) | axisData[2] );
	rawXa = (short)( (axisData[3] << 8 & 0xff00 ) | axisData[4] );
	rawZa = (short)( (axisData[5] << 8 & 0xff00 ) | axisData[6] );

 	rawYg = (short)( (axisData[7] << 8 & 0xff00 ) | axisData[8] ) - offsetY;
	rawXg = (short)( (axisData[9] << 8 & 0xff00 ) | axisData[10] ) - offsetX;
	rawZg = (short)( (axisData[11] << 8 & 0xff00 ) | axisData[12] ) - offsetZ;

	// rawXa = (short)( (IMUReadByte(0x2d) << 8 & 0xff00 ) | IMUReadByte(0x2e) );
	// rawYa = (short)( (IMUReadByte(0x2f) << 8 & 0xff00 ) | IMUReadByte(0x30) );
	// rawZa = (short)( (IMUReadByte(0x31) << 8 & 0xff00 ) | IMUReadByte(0x32) );
}
///////////////////////////////////////////////////
// ���W���[���� getTurningAngleIMU
// �����T�v   	yaw���̊p�x���Z�o
// ����         �Ȃ�
// �߂�l       �Ȃ�
///////////////////////////////////////////////////
void getTurningAngleIMU(void) {
	double angularVelocity_zg;

	angularVelocity_zg = (double)(rawZg) / GYROLSB;	// IMU�̃f�[�^���p���x[deg/s]�ɕϊ�
	TurningAngleIMU += (double)( angularVelocity_zg) * DELTATIMU;
}
///////////////////////////////////////////////////
// ���W���[���� getRollAngleIMU
// �����T�v   	roll���̊p�x���Z�o
// ����         �Ȃ�
// �߂�l       �Ȃ�
///////////////////////////////////////////////////
void getRollAngleIMU(void)
{
	double angularVelocity_yg;

	angularVelocity_yg = (double)(rawXg) / GYROLSB;	// IMU�̃f�[�^���p���x[deg/s]�ɕϊ�
	RollAngleIMU -= (double)( angularVelocity_yg) * DELTATIMU;
}
///////////////////////////////////////////////////
// ���W���[���� getPichAngleIMU
// �����T�v   	pich���̊p�x���Z�o
// ����         �Ȃ�
// �߂�l       �Ȃ�
///////////////////////////////////////////////////
void getPichAngleIMU( void )
{
	double angularVelocity_xg;
	
	angularVelocity_xg = (double)(rawYg) / GYROLSB;	// IMU�̃f�[�^���p���x[deg/s]�ɕϊ�
	PichAngleIMU -= (double)( angularVelocity_xg) * DELTATIMU;
}