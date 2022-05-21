#ifndef ROTARYENCODER_H_
#define ROTARYENCODER_H_
//====================================//
// インクルード
//====================================//
#include "r_smc_entry.h"
//====================================//
// シンボル定義
//====================================//

#define PALSE_METER		    14590	    // 1mのパルス
#define PALSE_MILLIMETER	14.59F	    // 1mmのパルス
#define SPEED_CURRENT		15		    // 1m/sの時　1msのパルス


//====================================//
// グローバル変数の宣言
//====================================//

extern unsigned int 	ENCODER_COUNT;	//エンコーダー値
extern unsigned int	EncoderTotal;	// 総走行距離
extern signed short	Encoder;		// 1msごとのパルス
extern unsigned int	enc1;		// 走行用距離カウント
extern unsigned int	enc_slope;		// 坂上距離カウント



//====================================//
// プロトタイプ宣言
//====================================//

void getEncoder (void);



#endif // ROTARYENCODER_H_