#ifndef ROTARYENCODER_H_
#define ROTARYENCODER_H_
//====================================//
// �C���N���[�h
//====================================//
#include "r_smc_entry.h"
//====================================//
// �V���{����`
//====================================//

#define PALSE_METER		    14590	    // 1m�̃p���X
#define PALSE_MILLIMETER	14.59F	    // 1mm�̃p���X
#define SPEED_CURRENT		15		    // 1m/s�̎��@1ms�̃p���X


//====================================//
// �O���[�o���ϐ��̐錾
//====================================//

extern unsigned int 	ENCODER_COUNT;	//�G���R�[�_�[�l
extern unsigned int	EncoderTotal;	// �����s����
extern signed short	Encoder;		// 1ms���Ƃ̃p���X
extern unsigned int	enc1;		// ���s�p�����J�E���g
extern unsigned int	enc_slope;		// ��㋗���J�E���g



//====================================//
// �v���g�^�C�v�錾
//====================================//

void getEncoder (void);



#endif // ROTARYENCODER_H_