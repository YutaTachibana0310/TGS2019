//=====================================
//
//ゲームパーティクルマネージャ処理[GameParticleManager.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "GameParticleManager.h"
#include "BloodParticleController.h"

using namespace std;

/**************************************
マクロ定義
***************************************/
#define GAMEPARTICLE_USE_DEBUG

#ifdef GAMEPARTICLE_USE_DEBUG
#include "debugWindow.h"
#endif

typedef SceneParticleManager Base;

/**************************************
構造体定義
***************************************/
enum ParticleController
{
	BloodParticle,
	ControllerMax
};

/**************************************
初期化処理
***************************************/
void GameParticleManager::Init()
{
	Base::Init();

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//各コントローラを生成
	controllers.resize(ControllerMax);
	controllers[BloodParticle] = new BloodParticleController();

	//各パーティクル初期化
	for (auto& controller : controllers)
	{
		controller->Init();
	}
}

/**************************************
更新処理
***************************************/
void GameParticleManager::Update(void)
{
#ifdef GAMEPARTICLE_USE_DEBUG
	DrawDebugWindow();
#endif

	Base::Update();
}

#ifdef GAMEPARTICLE_USE_DEBUG
/**************************************
デバッグウィンドウ
***************************************/
void GameParticleManager::DrawDebugWindow(void)
{
	BeginDebugWindow("GameParticle");


	EndDebugWindow("GameParticle");
}
#endif