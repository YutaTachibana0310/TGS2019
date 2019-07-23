//=====================================
//
//ゲームシーン処理[GameScene.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "GameScene.h"
#include "camera.h"

/**************************************
マクロ定義
***************************************/
#define SKYBOX_SIZE		(30000.0f)

/**************************************
グローバル変数
***************************************/

/**************************************
初期化処理
***************************************/
void GameScene::Init()
{
	player = new Player();
	skybox = new SkyBox(D3DXVECTOR3(SKYBOX_SIZE*2, SKYBOX_SIZE, SKYBOX_SIZE), D3DXVECTOR2(6.0f, 1.0f));

	skybox->LoadTexture("data/TEXTURE/skybox.png");
}

/**************************************
終了処理
***************************************/
void GameScene::Uninit()
{
	SAFE_DELETE(player);
	SAFE_DELETE(skybox);
}

/**************************************
更新処理
***************************************/
void GameScene::Update(HWND hWnd)
{
	player->Update();

	Camera *camera = GetCameraAdr();
	camera->target = camera->pos = player->transform.pos;
	camera->pos.z = CAMERA_TARGETLENGTH_Z;
}

/**************************************
描画処理
***************************************/
void GameScene::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	skybox->Draw();

	pDevice->SetRenderState(D3DRS_LIGHTING, false);

	player->Draw();

	pDevice->SetRenderState(D3DRS_LIGHTING, true);
}
