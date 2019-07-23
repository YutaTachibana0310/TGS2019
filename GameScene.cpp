//=====================================
//
//ゲームシーン処理[GameScene.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "GameScene.h"
#include "Framework/ResourceManager.h"
#include "camera.h"
#include "light.h"

/**************************************
マクロ定義
***************************************/

/**************************************
グローバル変数
***************************************/
Enemy *enemy[16];

/**************************************
初期化処理
***************************************/
void GameScene::Init()
{
	ResourceManager::Instance()->LoadTexture("enemy01", "data/bullet001.png");
	for (int i = 0; i < 16; i++)
	{
		enemy[i] = new Enemy;
	}
}
/**************************************
終了処理
***************************************/
void GameScene::Uninit()
{
	for (int i = 0; i < 16; i++)
	{
		delete enemy[i];
	}
}

/**************************************
更新処理
***************************************/
void GameScene::Update(HWND hWnd)
{
	for (int i = 0; i < 16; i++)
	{
		enemy[i]->UpdateEnemy();
	}
}

/**************************************
描画処理
***************************************/
void GameScene::Draw()
{
	for (int i = 0; i < 16; i++)
	{
		enemy[i]->DrawEnemy();
	}
}
