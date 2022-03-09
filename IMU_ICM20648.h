#ifndef I2C_MPU9250_H_
#define I2C_MPU9250_H_
//====================================//
// �C���N���[�h                  	   //
//====================================//
#include "r_smc_entry.h"
//====================================//
// �V���{����`						   //
//====================================//
// MPU-9255 Register Map
#define WHO_AM_I	 	0x00
#define USER_CTRL		0x03
#define PWR_MGMT_1		0x06
#define REG_BANK_SEL 	0x7F
#define GYRO_CONFIG_1 	0x01
#define ACCEL_CONFIG 	0x14
#define GYRO_XOUT_H 	0x33
#define ACCEL_XOUT_H 	0x2D

#define MPU9250_ADDRESS_W     	0xd0		// �������ݎ��̃X���[�u�A�h���X
#define MPU9250_ADDRESS_R    	0xd1		// �ǂݍ��ݎ��̃X���[�u�A�h���X

#define ACCELLSB			2048	// 16[g]
#define GYROLSB				16.4	// 1000[deg/s]
#define TEMP_LSB			333.87	// LSB/��C
#define ROOMTEMPOFFSET		0		// 21��C�̂Ƃ�0

#define BUS_IMU_FREE 		0		// �ʐM�\
#define BUS_IMU_BUSY 		1		// �ʐM��

// �f�[�^�����֘A
#define CLOCK				240		// ������g��[MHz]

#define MAXDATA_RANGE		32764	// 16bit�f�[�^�̍ő�l
#define G_ACCELERATION		9.81	// �d�͉����x
#define DELTATIMU			0.005	// �擾����
#define SAMPLE				5000	// �L�����u���[�V�����̃T���v����

/*************************************** ���������֐� **********************************/
#define USECOM 			1		// 0:I2c 1:SPI
#if USECOM == 0
	//I2c
	#define I2C_IMU_COMMAND		R_Config_SCI2_IIC_Master_Send( MPU9250_ADDRESS_W, data_tr, num)
	#define I2C_IMU_RECIVE		R_Config_SCI2_IIC_Master_Receive( MPU9250_ADDRESS_R, data_re, num)
	#define I2C_IMU_ARRY		R_Config_SCI2_IIC_Master_Receive(MPU9250_ADDRESS_R, data_re, num)
#else
	//SPI
	#define SPI_IMU_CS			PORTC.PODR.BIT.B6	// CS�[�q
	#define SPI_IMU_SEND		R_Config_SCI2_SPI_Master_Send_Receive( data_tr, numS, data_re, numR)
#endif
/****************************************************************************************/
//====================================//
// �O���[�o���ϐ��̐錾					//
//====================================//
// IMU����擾�����f�[�^
extern volatile int 	rawXa, rawYa, rawZa;		// �����x(16bit�f�[�^)
extern volatile int 	rawXg, rawYg, rawZg;	// �p�����x(16bit�f�[�^)
extern volatile short 	rawTemp;				// ���x(16bit�f�[�^)

extern short 	rawXa2, rawYa2, rawZa2;	// �����x(16bit�f�[�^)
extern short 	rawXg2, rawYg2, rawZg2;	// �p�����x(16bit�f�[�^)

// �f�[�^����
extern double 		TurningAngleIMU;	// IMU���狁�߂�����p�x
extern double		RollAngleIMU;		// IMU���狁�߂����[�������p�x
extern double 		PichAngleIMU;		// IMU���狁�߂��s�b�`�����p�x
extern double		TempIMU;			// IMU�̉��x

// ���[�h�֘A
extern uint8_t	whoami;
extern uint8_t	cnt_imu;
extern uint8_t	busIMU;
//====================================//
// �v���g�^�C�v�錾					   //
//====================================//
void wait_IMU ( uint16_t waitTime );
void IMUWriteByte( uint8_t reg, uint8_t data );
uint8_t IMUReadByte( uint8_t reg );
void IMUReadArry( uint8_t reg, uint8_t num2, uint8_t* data_re );
bool init_IMU (void);
void getIMUdata (void);
void caribrateIMU (void);
void getTurningAngleIMU(void);
void getRollAngleIMU(void);
void getPichAngleIMU( void );
#endif // I2C_MPU9250_H_