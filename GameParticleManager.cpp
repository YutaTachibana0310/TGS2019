//=====================================
//
//�Q�[���p�[�e�B�N���}�l�[�W������[GameParticleManager.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "GameParticleManager.h"
#include "BloodParticleController.h"

using namespace std;

/**************************************
�}�N����`
***************************************/
#define GAMEPARTICLE_USE_DEBUG

#ifdef GAMEPARTICLE_USE_DEBUG
#include "debugWindow.h"
#endif

typedef SceneParticleManager Base;

/**************************************
�\���̒�`
***************************************/
enum ParticleController
{
	BloodParticle,
	ControllerMax
};

/**************************************
����������
***************************************/
void GameParticleManager::Init()
{
	Base::Init();

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�R���g���[���𐶐�
	controllers.resize(ControllerMax);
	controllers[BloodParticle] = new BloodParticleController();

	//�e�p�[�e�B�N��������
	for (auto& controller : controllers)
	{
		controller->Init();
	}
}

/**************************************
�X�V����
***************************************/
void GameParticleManager::Update(void)
{
#ifdef GAMEPARTICLE_USE_DEBUG
	DrawDebugWindow();
#endif

	Base::Update();
}

/**************************************
�G�t�F�N�g�Z�b�g����
***************************************/
void GameParticleManager::SetBloodParticle(D3DXVECTOR3 right, D3DXVECTOR3 left)
{
	BloodParticleController *entity = static_cast<BloodParticleController*>(controllers[BloodParticle]);
	entity->SetEmitter(right, left);
}

#ifdef GAMEPARTICLE_USE_DEBUG
/**************************************
�f�o�b�O�E�B���h�E
***************************************/
void GameParticleManager::DrawDebugWindow(void)
{
	BeginDebugWindow("GameParticle");

	if (DebugButton("Blood"))
	{
		SetBloodParticle(D3DXVECTOR3(50.0f, 0.0f, 0.0f), D3DXVECTOR3(-50.0f, 0.0f, 0.0f));
	}

	EndDebugWindow("GameParticle");
}
#endif