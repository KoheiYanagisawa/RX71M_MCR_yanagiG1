//====================================
// インクルード
//====================================
#include "AD12.h"
//====================================
// グローバル変数の宣言
//====================================


//　タイマ関連
static char				ADTimer10;	// AD変換カウント用

//　センサ関連
//  AD変換結果格納
uint16_t            A0_Sen[8];              //AD0チャンネルの格納先
uint16_t            A1_Sen[14];             //AD1チャンネルの格納先

short               Angle0;                 //サーボセンター値
short	            sensorG_th = GATE_VAL;	// ゲート開放しきい値


///////////////////////////////////////////////////
// モジュール名 inttrruptAD0
// 処理概要   	AD0の変換終了割り込み
// 引数         なし
// 戻り値       なし
///////////////////////////////////////////////////
void inttrruptAD0(void) {
    R_Config_S12AD0_Get_ValueResult(ADCHANNEL2,&potentio);
    R_Config_S12AD0_Get_ValueResult(ADCHANNEL4,&gatesensor);
    R_Config_S12AD0_Get_ValueResult(ADCHANNEL5,&sensor5);
    R_Config_S12AD0_Get_ValueResult(ADCHANNEL6,&sensor4);
    R_Config_S12AD0_Get_ValueResult(ADCHANNEL7,&sensor3);
}
///////////////////////////////////////////////////
// モジュール名 inttrruptAD1
// 処理概要   	AD1の変換終了割り込み
// 引数         なし
// 戻り値       なし
///////////////////////////////////////////////////
void inttrruptAD1(void) {
    R_Config_S12AD1_Get_ValueResult(ADCHANNEL8,&sensor2);
    R_Config_S12AD1_Get_ValueResult(ADCHANNEL9,&sensor1);
}
void sensorthreshold(){
      
}