
//=============================================================================
//作成者　GP11A341_34_増田光汰
// HP表示するだけの処理 [Result.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "Result.h"
#include "input.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexResult(void);
//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTextureResult = NULL;				// テクスチャへのポインタ
VERTEX_2D				vertexWkResult[NUM_VERTEX];				// 頂点情報格納ワーク
RESULT					titleWk[TITLEPLAYER_MAX];			// プレイヤー構造体
LPDIRECT3DTEXTURE9		D3DTextureStart = NULL;		// テクスチャへのポインタ

bool					titlefg = true;
int						cunt = 0;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitResult(int type)
{
	RESULT *title = &titleWk[0];

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int i = 0; i < TITLEPLAYER_MAX; i++, title++)
	{
		title->use = true;											// 使用
		title->pos = D3DXVECTOR3(i*200.0f + 200.0f, 330.0f, 0.0f);	// 座標データを初期化
		title->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// 回転データを初期化
		title->col = D3DXCOLOR(0.0, 0.0, 0.0, 0.5);				// 色
		title->PatternAnim = 0;
		title->PatternAnim = rand() % ANIM_PATTERN_NUM;				// アニメパターン番号をランダムで初期化


																	// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,							// デバイスへのポインタ
			TEXTURE_STAGE1_TITLE,									// ファイルの名前
			&D3DTextureResult);											// 読み込むメモリー
		D3DXCreateTextureFromFile(pDevice,							// デバイスへのポインタ
			TEXTURE_STAGE2_TITLE,									// ファイルの名前
			&D3DTextureStart);											// 読み込むメモリー

		MakeVertexResult();
	}
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitResult(void)
{
	if (D3DTextureResult != NULL)
	{// テクスチャの開放
		D3DTextureResult->Release();
		D3DTextureResult = NULL;
	}

	if (D3DTextureStart != NULL)
	{// テクスチャの開放
		D3DTextureStart->Release();
		D3DTextureStart = NULL;
	}


}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateResult(void)
{
	cunt++;

	// 点滅処理
	if (cunt > 50)
	{
		titlefg = !titlefg;
		cunt = 0;
	}

	MakeVertexResult();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawResult(void)
{
	RESULT *title = &titleWk[0];

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, D3DTextureResult);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWkResult, sizeof(VERTEX_2D));

	if (titlefg == true)
	{

		// テクスチャの設定
		pDevice->SetTexture(0, D3DTextureStart);

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	}


}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexResult(void)
{

	// 頂点座標の設定
	vertexWkResult[0].vtx = D3DXVECTOR3(STAGE1_TITLE_POS_X, STAGE1_TITLE_POS_Y, 0.0f);
	vertexWkResult[1].vtx = D3DXVECTOR3(STAGE1_TITLE_POS_X + STAGE1_TITLE_SIZE_X, STAGE1_TITLE_POS_Y, 0.0f);
	vertexWkResult[2].vtx = D3DXVECTOR3(STAGE1_TITLE_POS_X, STAGE1_TITLE_POS_Y + STAGE1_TITLE_SIZE_Y, 0.0f);
	vertexWkResult[3].vtx = D3DXVECTOR3(STAGE1_TITLE_POS_X + STAGE1_TITLE_SIZE_X, STAGE1_TITLE_POS_Y + STAGE1_TITLE_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	vertexWkResult[0].rhw =
	vertexWkResult[1].rhw =
	vertexWkResult[2].rhw =
	vertexWkResult[3].rhw = 1.0f;

	// 反射光の設定
	vertexWkResult[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkResult[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkResult[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkResult[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);


	// テクスチャ座標の設定
	vertexWkResult[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWkResult[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertexWkResult[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWkResult[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	return S_OK;
}
//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureResultPlayer(int no, int cntPattern)
{
	RESULT *title = &titleWk[no];

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
void SetVertexResultPlaier(int no)
{
	RESULT *title = &titleWk[no];

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