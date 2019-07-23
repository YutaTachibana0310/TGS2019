//=====================================
//
//�Q�[���V�[������[GameScene.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "GameScene.h"
#include "Framework/ResourceManager.h"
#include "camera.h"
#include "light.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
Enemy *enemy[16];

/**************************************
����������
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
�I������
***************************************/
void GameScene::Uninit()
{
	for (int i = 0; i < 16; i++)
	{
		delete enemy[i];
	}
}

/**************************************
�X�V����
***************************************/
void GameScene::Update(HWND hWnd)
{
	for (int i = 0; i < 16; i++)
	{
		enemy[i]->UpdateEnemy();
	}
}

/**************************************
�`�揈��
***************************************/
void GameScene::Draw()
{
	for (int i = 0; i < 16; i++)
	{
		enemy[i]->DrawEnemy();
	}
}
