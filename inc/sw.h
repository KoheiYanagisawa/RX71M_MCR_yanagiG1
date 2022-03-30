#ifndef SW_H
#define SW_h
//====================================//
// インクルード                        //
//====================================//
#include "r_smc_entry.h"
//====================================//
// シンボル定義						   //
//====================================//
#define UP      1
#define DOWN    2
#define LEFT    3
#define RIGHT   4
#define PUSH    5
//====================================//
// グローバル変数の宣言					//
//====================================//
uint8_t getRotarysw(void);
uint8_t getTactsw(void);


#endif // BUTTON_H