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
// モジュール名 init_AD
// 処理概要     ADの初期化
// 引数         なし
// 戻り値      	なし
///////////////////////////////////////////////////
void init_AD(void){
	MTU4.TGRD = 5998;						//トレースセンサー用PWM
}


///////////////////////////////////////////////////
// モジュール名 inttrruptAD0
// 処理概要   	AD0の変換終了割り込み
// 引数         なし
// 戻り値       なし
///////////////////////////////////////////////////
void inttrruptAD0(void) {
    R_Config_S12AD0_Get_ValueResult(ADCHANNEL2,&potentio);
    R_Config_S12AD0_Get_ValueResult(ADCHANNEL4,&gatesensor);
    R_Config_S12AD0_Get_ValueResult(ADCHANNEL5,&sensorLL);
    R_Config_S12AD0_Get_ValueResult(ADCHANNEL6,&sensorL);
    R_Config_S12AD0_Get_ValueResult(ADCHANNEL7,&sensorC);
}
///////////////////////////////////////////////////
// モジュール名 inttrruptAD1
// 処理概要   	AD1の変換終了割り込み
// 引数         なし
// 戻り値       なし
///////////////////////////////////////////////////
void inttrruptAD1(void) {
    R_Config_S12AD1_Get_ValueResult(ADCHANNEL8,&sensorR);
    R_Config_S12AD1_Get_ValueResult(ADCHANNEL9,&sensorRR);
}
///////////////////////////////////////////////////////////////////////////
// モジュール名 getServoAngle
// 処理概要     ポテンションメーターのアナログ値で取得
// 引数         なし
// 戻り値       センサ値
///////////////////////////////////////////////////////////////////////////
short getServoAngle(void) 
{	
	return  ( Angle0 - potentio );
}
///////////////////////////////////////////////////////////////////////////
// モジュール名 getAnalogSensor
// 処理概要     アナログセンサのアナログ値で取得
// 引数         なし
// 戻り値       センサ値
///////////////////////////////////////////////////////////////////////////
short getAnalogSensor(void) 
{
	return sensorR - sensorL;
}
///////////////////////////////////////////////////////////////////////////
// モジュール名 sensor_inp
// 処理概要     デジタルセンサの値を16進数で取得
// 引数         なし
// 戻り値       センサ値0～
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
// モジュール名 startbar_get
// 処理概要     スタートゲートの開閉の確認
// 引数         なし
// 戻り値       0; 閉じている 1; 開いている
///////////////////////////////////////////////////////////////////////////
unsigned char startbar_get(void) 
{
	char ret;
	
	if ( gatesensor <= sensorG_th )	ret = 1;
	else			ret = 0;
	
	return ret;
}