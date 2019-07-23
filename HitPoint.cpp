
//=============================================================================
//作成者　GP11A341_34_増田光汰
// HP表示するだけの処理 [Ui.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "Hitpoint.h"
#include "input.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexUi(void);
//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTextureUi = NULL;				// テクスチャへのポインタ
VERTEX_2D				vertexWkUi[NUM_VERTEX];				// 頂点情報格納ワーク
TITLEPLAYER				titleWk[TITLEPLAYER_MAX];			// プレイヤー構造体


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitUi(int type)
{
	TITLEPLAYER *title = &titleWk[0];

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int i = 0; i < TITLEPLAYER_MAX; i++, title++)
	{
		title->use = true;											// 使用
		title->pos = D3DXVECTOR3(10.0f + 10.0f, 0.0f, 0.0f);	// 座標データを初期化
		title->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// 回転データを初期化
		title->col = D3DXCOLOR(0.0, 0.0, 0.0, 0.5);				// 色
		title->PatternAnim = 0;
		title->PatternAnim = rand() % ANIM_PATTERN_NUM;				// アニメパターン番号をランダムで初期化


																	// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,							// デバイスへのポインタ
			TEXTURE_STAGE1_TITLE,									// ファイルの名前
			&D3DTextureUi);											// 読み込むメモリー

		MakeVertexUi();
	}
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitUi(void)
{
	if (D3DTextureUi != NULL)
	{// テクスチャの開放
		D3DTextureUi->Release();
		D3DTextureUi = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateUi(void)
{

	MakeVertexUi();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawUi(void)
{
	TITLEPLAYER *title = &titleWk[0];

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, D3DTextureUi);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWkUi, sizeof(VERTEX_2D));


}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexUi(void)
{

	// 頂点座標の設定
	vertexWkUi[0].vtx = D3DXVECTOR3(STAGE1_TITLE_POS_X, STAGE1_TITLE_POS_Y, 0.0f);
	vertexWkUi[1].vtx = D3DXVECTOR3(STAGE1_TITLE_POS_X + STAGE1_TITLE_SIZE_X, STAGE1_TITLE_POS_Y, 0.0f);
	vertexWkUi[2].vtx = D3DXVECTOR3(STAGE1_TITLE_POS_X, STAGE1_TITLE_POS_Y + STAGE1_TITLE_SIZE_Y, 0.0f);
	vertexWkUi[3].vtx = D3DXVECTOR3(STAGE1_TITLE_POS_X + STAGE1_TITLE_SIZE_X, STAGE1_TITLE_POS_Y + STAGE1_TITLE_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	vertexWkUi[0].rhw =
	vertexWkUi[1].rhw =
	vertexWkUi[2].rhw =
	vertexWkUi[3].rhw = 1.0f;

	// 反射光の設定
	vertexWkUi[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkUi[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkUi[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkUi[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);


	// テクスチャ座標の設定
	vertexWkUi[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWkUi[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertexWkUi[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWkUi[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	return S_OK;
}
//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureUiPlayer(int no, int cntPattern)
{
	TITLEPLAYER *title = &titleWk[no];

	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y;

	title->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	title->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	title->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	title->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexUiPlaier(int no)
{
	TITLEPLAYER *title = &titleWk[no];

	// 頂点座標の設定

	title->vertexWk[0].vtx.x = title->pos.x - cosf(title->BaseAngle + title->rot.z) * title->Radius;
	title->vertexWk[0].vtx.y = title->pos.y - sinf(title->BaseAngle + title->rot.z) * title->Radius;
	title->vertexWk[0].vtx.z = 0.0f;

	title->vertexWk[1].vtx.x = title->pos.x + cosf(title->BaseAngle - title->rot.z) * title->Radius;
	title->vertexWk[1].vtx.y = title->pos.y - sinf(title->BaseAngle - title->rot.z) * title->Radius;
	title->vertexWk[1].vtx.z = 0.0f;

	title->vertexWk[2].vtx.x = title->pos.x - cosf(title->BaseAngle - title->rot.z) * title->Radius;
	title->vertexWk[2].vtx.y = title->pos.y + sinf(title->BaseAngle - title->rot.z) * title->Radius;
	title->vertexWk[2].vtx.z = 0.0f;

	title->vertexWk[3].vtx.x = title->pos.x + cosf(title->BaseAngle + title->rot.z) * title->Radius;
	title->vertexWk[3].vtx.y = title->pos.y + sinf(title->BaseAngle + title->rot.z) * title->Radius;
	title->vertexWk[3].vtx.z = 0.0f;
}



////=============================================================================
////
//// 背景処理 [HitPoint.cpp]
//// Author : 増田　光汰 
////
////=============================================================================
//#include "HitPoint.h"
//
////*****************************************************************************
//// マクロ定義
////*****************************************************************************
//
////*****************************************************************************
//// プロトタイプ宣言
////*****************************************************************************
//HRESULT MakeVertexHitPoint(LPDIRECT3DDEVICE9 pDevice);
//void SetTextureHitPoint(float val);
//
////*****************************************************************************
//// グローバル変数
////*****************************************************************************
//LPDIRECT3DTEXTURE9		D3DTextureHitPoint[2] = {};		// テクスチャへのポインタ
//LPDIRECT3DVERTEXBUFFER9 D3DVtxBuffHitPoint = NULL;		// 頂点バッファインターフェースへのポインタ
//
//D3DXVECTOR3				posHitPoint;						// 位置
//D3DXVECTOR3				rotHitPoint;						// 向き
//
////=============================================================================
//// 初期化処理
////=============================================================================
//HRESULT InitHitPoint(int type)
//{
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();
//
//	// テクスチャーの初期化を行う？
//	if (type == 0)
//	{
//		// テクスチャの読み込み
//		D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
//		TEXTURE_HITPOINT,									// ファイルの名前
//		&D3DTextureHitPoint[0]);								// 読み込むメモリー
//	}
//
//	posHitPoint = D3DXVECTOR3(-5.0f, 5.0f, 0.0f);
//
//
//	// 頂点情報の作成
//	MakeVertexHitPoint(pDevice);
//
//
//
//	SetTextureHitPoint(100.0f);
//
//	return S_OK;
//
//}
//
////=============================================================================
//// 終了処理
////=============================================================================
//void UninitHitPoint(void)
//{
//	if (D3DTextureHitPoint[0] != NULL)
//	{// テクスチャの開放
//		D3DTextureHitPoint[0]->Release();
//		D3DTextureHitPoint[0] = NULL;
//	}
//
//}
//
////=============================================================================
//// 更新処理
////=============================================================================
//void UpdateHitPoint(void)
//{
//}
//
////=============================================================================
//// 描画処理
////=============================================================================
//void DrawHitPoint(void)
//{
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();
//
//	// 頂点バッファをデバイスのデータストリームにバインド
//	pDevice->SetStreamSource(0, D3DVtxBuffHitPoint, 0, sizeof(VERTEX_2D));
//
//	// 頂点フォーマットの設定
//	pDevice->SetFVF(FVF_VERTEX_2D);
//
//	// テクスチャの設定
//	pDevice->SetTexture(0, D3DTextureHitPoint[0]);
//
//	// ポリゴンの描画
//	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (NUM_PLACE * 4), NUM_POLYGON);
//
//
//}
//
////=============================================================================
//// 頂点の作成
////=============================================================================
//HRESULT MakeVertexHitPoint(LPDIRECT3DDEVICE9 pDevice)
//{
//
//	//頂点バッファの中身を埋める
//	VERTEX_2D *pVtx;
//
//	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
//	D3DVtxBuffHitPoint->Lock(0, 0, (void**)&pVtx, 0);
//
//	// 頂点座標の設定
//	pVtx[0].vtx = D3DXVECTOR3(HITPOINT_POS_X,HITPOINT_POS_Y, 0.0f);
//	pVtx[1].vtx = D3DXVECTOR3(HITPOINT_POS_X + HITPOINT_SIZE_X, HITPOINT_POS_Y, 0.0f);
//	pVtx[2].vtx = D3DXVECTOR3(HITPOINT_POS_X,HITPOINT_POS_Y + HITPOINT_SIZE_Y, 0.0f);
//	pVtx[3].vtx = D3DXVECTOR3(HITPOINT_POS_X + HITPOINT_SIZE_X, HITPOINT_POS_Y + HITPOINT_SIZE_Y, 0.0f);
//
//	// rhwの設定
//	pVtx[0].rhw =
//	pVtx[1].rhw =
//	pVtx[2].rhw =
//	pVtx[3].rhw = 1.0f;
//
//	// 反射光の設定
//	pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//	pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//	pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//	pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//
//	// テクスチャ座標の設定
//	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
//	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
//	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
//	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
//
//	return S_OK;
//
//}
//
////=============================================================================
//// テクスチャ座標の設定
////=============================================================================
//void SetTextureHitPoint(float val)
//{
//	VERTEX_2D *pVtx;
//
//	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
//	D3DVtxBuffHitPoint->Lock(0, 0, (void**)&pVtx, 0);
//
//	//pVtx += (nIdx * 4);
//
//	// テクスチャ座標の設定
//	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
//	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
//	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
//	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
//
//	// 頂点データをアンロックする
//	D3DVtxBuffHitPoint->Unlock();
//
//
//}
//
//
