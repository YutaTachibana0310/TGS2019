//=====================================
//
//タイトルシーン処理[TitleScene.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "TitleScene.h"
#include "Framework\SkyBox.h"

#include "Game.h"

#define	TITLE_POS_X			(640-480)							// タイトルの表示位置
#define	TITLE_POS_Y			(105)								// タイトルの表示位置
#define	TITLE_SIZE_X		(1500)								// タイトルの幅
#define	TITLE_SIZE_Y		(600)								// タイトルの高さ



/**************************************
マクロ定義
***************************************/

/**************************************
グローバル変数
***************************************/
static SkyBox *skybox;
LPDIRECT3DTEXTURE9		D3DTextureTitle = NULL;			// テクスチャへのポインタ
VERTEX_2D				vertexWkTitle[NUM_VERTEX];		// 頂点情報格納ワーク


/**************************************
初期化処理
***************************************/
void TitleScene::Init()
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	skybox = new SkyBox(D3DXVECTOR3(30000.0f * 2, 30000.0f, 30000.0f), D3DXVECTOR2(6.0f, 1.0f));
	skybox->LoadTexture("data/TEXTURE/skybox.png");

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(Device,						// デバイスへのポインタ
		"data/TEXTURE/TITLEL_TGS.png",		// ファイルの名前
		&D3DTextureTitle);			// 読み込むメモリー

	// 頂点座標の設定
	vertexWkTitle[0].vtx = D3DXVECTOR3(TITLE_POS_X, TITLE_POS_Y, 0.0f);
	vertexWkTitle[1].vtx = D3DXVECTOR3(TITLE_POS_X + TITLE_SIZE_X, TITLE_POS_Y, 0.0f);
	vertexWkTitle[2].vtx = D3DXVECTOR3(TITLE_POS_X, TITLE_POS_Y + TITLE_SIZE_Y, 0.0f);
	vertexWkTitle[3].vtx = D3DXVECTOR3(TITLE_POS_X + TITLE_SIZE_X, TITLE_POS_Y + TITLE_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	vertexWkTitle[0].rhw =
		vertexWkTitle[1].rhw =
		vertexWkTitle[2].rhw =
		vertexWkTitle[3].rhw = 1.0f;

	// 反射光の設定
	vertexWkTitle[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkTitle[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkTitle[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkTitle[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	vertexWkTitle[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWkTitle[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertexWkTitle[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWkTitle[3].tex = D3DXVECTOR2(1.0f, 1.0f);


}

/**************************************
終了処理
***************************************/
void TitleScene::Uninit()
{
	SAFE_DELETE(skybox);

	if (D3DTextureTitle != NULL)
	{// テクスチャの開放
		D3DTextureTitle->Release();
		D3DTextureTitle = NULL;
	}

}

#include "input.h"
/**************************************
更新処理
***************************************/
void TitleScene::Update(HWND hWnd)
{
	if (GetAttackButtonTrigger())
	{
		ChangeScene(SceneGame);
	}
	

}

/**************************************
描画処理
***************************************/
void TitleScene::Draw()
{
	skybox->Draw();

	LPDIRECT3DDEVICE9 Device = GetDevice();

	// 頂点フォーマットの設定
	Device->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	Device->SetTexture(0, D3DTextureTitle);

	// ポリゴンの描画
	Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWkTitle, sizeof(VERTEX_2D));

}
