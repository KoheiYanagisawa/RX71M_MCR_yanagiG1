#ifndef SW_H
#define SW_h
//====================================//
// �C���N���[�h                        //
//====================================//
#include "r_smc_entry.h"
//====================================//
// �V���{����`						   //
//====================================//
#define UP      1
#define DOWN    2
#define LEFT    3
#define RIGHT   4
#define PUSH    5
//====================================//
// �O���[�o���ϐ��̐錾					//
//====================================//
uint8_t getRotarysw(void);
uint8_t getTactsw(void);


#endif // BUTTON_H