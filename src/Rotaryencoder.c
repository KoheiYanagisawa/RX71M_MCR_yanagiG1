//====================================//
// インクルード
//====================================//
#include "Rotaryencoder.h"
//====================================//
// グローバル変数の宣言
//====================================//
// エンコーダ関連

static unsigned short		encbuff;		// 前回のエンコーダ値
short				Encoder;			// 1msごとのパルス
unsigned int			EncoderTotal;		// 総走行距離
unsigned int			enc1;				// 走行用距離カウント
unsigned int			enc_slope;			// 坂上距離カウント

/////////////////////////////////////////////////////////////////////////////////
// モジュール名 getEncoder
// 処理概要     エンコーダのカウントを取得し積算する(1msごとに実行)
// 引数         なし
// 戻り値       なし
/////////////////////////////////////////////////////////////////////////////////
void getEncoder (void)
{
	Encoder = ENCODER_COUNT - encbuff;// 現在地から1ms前の値を引いて1ms間のカウントを計算
	
	// 積算
	EncoderTotal += Encoder;
	enc1 += Encoder;
	enc_slope += Encoder;
	
	encbuff = ENCODER_COUNT;	// 次回はこの値が1ms前の値となる
}