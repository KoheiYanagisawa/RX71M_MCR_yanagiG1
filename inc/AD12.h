#ifndef AD12_H_
#define AD12_H_
//====================================//
// �C���N���[�h                  	   //
//====================================//
#include "r_smc_entry.h"
//====================================//
// �V���{����`						   //
//====================================//
#define sensor1             A1_Sen[10]
#define sensor2             A1_Sen[9]
#define sensor3             A0_Sen[7]
#define sensor4             A0_Sen[6]
#define sensor5             A0_Sen[5]
#define gatesensor          A0_Sen[4]
#define potentio            A0_Sen[2]
//====================================//
// �O���[�o���ϐ��̐錾				    //
//====================================//
extern uint16_t             A0_Sen[8];
extern uint16_t             A1_Sen[14];
//====================================//
// �v���g�^�C�v�錾					   //
//====================================//
void inttrruptAD0(void);
void inttrruptAD1(void);
#endif // AD12_H_