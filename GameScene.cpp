//=====================================
//
//�Q�[���V�[������[GameScene.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "GameScene.h"
#include "camera.h"

/**************************************
�}�N����`
***************************************/
#define SKYBOX_SIZE		(30000.0f)

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
����������
***************************************/
void GameScene::Init()
{
	player = new Player();
	skybox = new SkyBox(D3DXVECTOR3(SKYBOX_SIZE*2, SKYBOX_SIZE, SKYBOX_SIZE), D3DXVECTOR2(6.0f, 1.0f));

	skybox->LoadTexture("data/TEXTURE/skybox.png");
}

/**************************************
�I������
***************************************/
void GameScene::Uninit()
{
	SAFE_DELETE(player);
	SAFE_DELETE(skybox);
}

/**************************************
�X�V����
***************************************/
void GameScene::Update(HWND hWnd)
{
	player->Update();

	Camera *camera = GetCameraAdr();
	camera->target = camera->pos = player->transform.pos;
	camera->pos.z = CAMERA_TARGETLENGTH_Z;
}

/**************************************
�`�揈��
***************************************/
void GameScene::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	skybox->Draw();

	pDevice->SetRenderState(D3DRS_LIGHTING, false);

	player->Draw();

	pDevice->SetRenderState(D3DRS_LIGHTING, true);
}
