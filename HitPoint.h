//=============================================================================
//GP11A341_34_増田光汰
// HP [HitPoint.h]
// Author : 
//
//=============================================================================
#ifndef _HITPOINT_H_
#define _HITPOINT_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_STAGE1_TITLE	("data/TEX/HP_flame.png")	// 読み込むテクスチャファイル名
#define	TEXTURE_STAGE0_TITLE	("data/TEX/gauge.png")	// 読み込むテクスチャファイル名


#define	STAGE1_TITLE_POS_X		(0)							// タイトルの表示位置
#define	STAGE1_TITLE_POS_Y		(-30)						// タイトルの表示位置
#define	STAGE1_TITLE_SIZE_X		(700)						// タイトルの幅
#define	STAGE1_TITLE_SIZE_Y		(200)						// タイトルの高さ
#define TEXTURE_PATTERN_DIVIDE_X	(10)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y	(1)		// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM			(TEXTURE_PATTERN_DIVIDE_X*TEXTURE_PATTERN_DIVIDE_Y)	// アニメーションパターン数
#define TIME_ANIMATION				(5)	// アニメーションの切り替わるカウント


//ゲージ
#define GAUGE00_SIZE_X			(250)											// テクスチャサイズ
#define GAUGE00_SIZE_Y			(25)											// 同上
#define GAUGE00_POS_X			(40)											// ポリゴンの初期位置X(左上)
#define GAUGE00_POS_Y			(30)											// 同上



typedef struct											// プレイヤー構造体
{
	D3DXVECTOR3				pos;						// ポリゴンの移動量
	D3DXVECTOR3				rot;						// ポリゴンの回転量
	LPDIRECT3DTEXTURE9		Texture;					// テクスチャ情報
	VERTEX_2D				vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク
	D3DXCOLOR				col;						// 色
	int						PatternAnim;				// アニメーションパターンナンバー
	int						CountAnim;					// アニメーションカウント
	float					Radius;						// プレイヤーの半径
	float					BaseAngle;					// プレイヤーの角度
	float					JumpCount;					//ジャンプ
	bool					use;
}	TITLEPLAYER;

#define TITLEPLAYER_MAX					(1)


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitUi(int type);
void UninitUi(void);
void UpdateUi(void);
void DrawUi(void);
//TITLEPLAYER *GetTitlePlayer(int no);

#endif

////=============================================================================
////
//// ゲージ処理 [HitPoint.h]
//// Author :増田　光汰
////
////=============================================================================
//#ifndef _HITPOINT_H_
//#define _HITPOINT_H_
//
//
//#include "main.h"
//#include "Framework\IStateScene.h"
//
////*****************************************************************************
//// マクロ定義
////*****************************************************************************
//#define	TEXTURE_HITPOINT		"data/TEX/HP_flame.png"
//#define	NUM_PLACE		(4)								
//#define HITPOINT_POS_X (10)
//#define HITPOINT_POS_Y (10)
//#define HITPOINT_SIZE_X (400)
//#define HITPOINT_SIZE_Y (400)
////*****************************************************************************
//// プロトタイプ宣言
////*****************************************************************************
//HRESULT InitHitPoint(int type);
//void UninitHitPoint(void);
//void UpdateHitPoint(void);
//void DrawHitPoint(void);
//#endif