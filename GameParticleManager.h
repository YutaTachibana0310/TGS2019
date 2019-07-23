//=====================================
//
//�Q�[���p�[�e�B�N���}�l�[�W���w�b�_[GameParticleManager.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _GameParticleManager_H_
#define _GameParticleManager_H_

#include "main.h"
#include "Framework\SceneParticleManager.h"
#include "Framework\BaseSingleton.h"

/**************************************
�}�N����`
***************************************/
#define GAMEPARTICLE_USE_DEBUG

/**************************************
�N���X��`
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