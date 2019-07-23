
//=============================================================================
//GP11A341_34_増田光汰
// タイトル１画面処理 [stage1_title.h]
// Author : 
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_
#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_STAGE1_TITLE	("data/TEX/Thank you for playing.png")	// 読み込むテクスチャファイル名
#define	TEXTURE_STAGE2_TITLE	("data/TEX/coollogo_com - 3677941.png")	// 読み込むテクスチャファイル名

#define	STAGE1_TITLE_POS_X			(0)									// タイトルの表示位置
#define	STAGE1_TITLE_POS_Y			(0)									// タイトルの表示位置
#define	STAGE1_TITLE_SIZE_X		(SCREEN_WIDTH)									// タイトルの幅
#define	STAGE1_TITLE_SIZE_Y		(SCREEN_HEIGHT)									// タイトルの高さ
#define TEXTURE_PATTERN_DIVIDE_X	(10)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y	(1)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM			(TEXTURE_PATTERN_DIVIDE_X*TEXTURE_PATTERN_DIVIDE_Y)	// アニメーションパターン数
#define TIME_ANIMATION				(5)	// アニメーションの切り替わるカウント

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
}	RESULT;

#define TITLEPLAYER_MAX					(1)


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitResult(int type);
void UninitResult(void);
void UpdateResult(void);
void DrawResult(void);

#endif
