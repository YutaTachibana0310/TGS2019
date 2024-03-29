//=====================================
//
//ゲームパーティクルマネージャヘッダ[GameParticleManager.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _GameParticleManager_H_
#define _GameParticleManager_H_

#include "main.h"
#include "Framework\SceneParticleManager.h"
#include "Framework\BaseSingleton.h"

/**************************************
マクロ定義
***************************************/
#define GAMEPARTICLE_USE_DEBUG

/**************************************
クラス定義
***************************************/
class GameParticleManager :
	public SceneParticleManager, 
	public BaseSingleton<GameParticleManager>
{
public:
	friend class BaseSingleton<GameParticleManager>;

	void Init() override;
	void Update() override;

	void SetBloodParticle(D3DXVECTOR3 right, D3DXVECTOR3 left);

private:
	GameParticleManager() {}
	~GameParticleManager() {}

#ifdef GAMEPARTICLE_USE_DEBUG
	void DrawDebugWindow();
#endif

};

#endif