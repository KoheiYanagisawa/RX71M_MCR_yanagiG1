#ifndef AD12_H_
#define AD12_H_
//====================================//
// インクルード                  	   //
//====================================//
#include "r_smc_entry.h"
//====================================//
// シンボル定義						   //
//====================================//
#define sensorRR            A1_Sen[10]          //最右端アナログセンサ
#define sensorR             A1_Sen[9]           //右アナログセンサ
#define sensorC             A0_Sen[7]           //中心アナログセンサ
#define sensorL             A0_Sen[6]           //左アナログセンサ
#define sensorLL            A0_Sen[5]           //最左端アナログセンサ
#define gatesensor          A0_Sen[4]           //ゲートセンサ
#define potentio            A0_Sen[2]           //ポテンショメータ

#define GATE_VAL			190		            // ゲートセンサしきい値
#define DEG2AD              41                  // 1度あたりのAD値 サーボ最大切れ角時のAD値[]/サーボ最大切れ角[°]
#define AD2DEG              0.0247F             // 1ADあたりの角度 サーボ最大切れ角[°]/サーボ最大切れ角時のAD値[]
//====================================//
// グローバル変数の宣言				    //
//====================================//
extern uint16_t             A0_Sen[8];
extern uint16_t             A1_Sen[14];
//====================================//
// プロトタイプ宣言					   //
//====================================//
void init_AD(void);
void inttrruptAD0(void);
void inttrruptAD1(void);
#endif // AD12_H_