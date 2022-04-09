#ifndef AD12_H_
#define AD12_H_
//====================================//
// �C���N���[�h                  	   //
//====================================//
#include "r_smc_entry.h"
//====================================//
// �V���{����`						   //
//====================================//
#define sensorRR            A1_Sen[10]          //�ŉE�[�A�i���O�Z���T
#define sensorR             A1_Sen[9]           //�E�A�i���O�Z���T
#define sensorC             A0_Sen[7]           //���S�A�i���O�Z���T
#define sensorL             A0_Sen[6]           //���A�i���O�Z���T
#define sensorLL            A0_Sen[5]           //�ō��[�A�i���O�Z���T
#define gatesensor          A0_Sen[4]           //�Q�[�g�Z���T
#define potentio            A0_Sen[2]           //�|�e���V�����[�^

#define GATE_VAL			190		            // �Q�[�g�Z���T�������l
#define DEG2AD              41                  // 1�x�������AD�l �T�[�{�ő�؂�p����AD�l[]/�T�[�{�ő�؂�p[��]
#define AD2DEG              0.0247F             // 1AD������̊p�x �T�[�{�ő�؂�p[��]/�T�[�{�ő�؂�p����AD�l[]
//====================================//
// �O���[�o���ϐ��̐錾				    //
//====================================//
extern uint16_t             A0_Sen[8];
extern uint16_t             A1_Sen[14];
//====================================//
// �v���g�^�C�v�錾					   //
//====================================//
void init_AD(void);
void inttrruptAD0(void);
void inttrruptAD1(void);
#endif // AD12_H_