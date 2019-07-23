//=====================================
//
//�Q�[���V�[������[GameScene.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#ifdef _DEBUG

#include "input.h"

#endif

#include "SliceEffect.h"
#include "GameScene.h"
#include "camera.h"
#include "Framework/ResourceManager.h"
#include "camera.h"
#include "light.h"

/**************************************
�v���g�^�C�v�錾
***************************************/
#ifdef _DEBUG
void InitSliceData();

#endif
void UpdateSliceEffect();
void DrawSliceEffect();

/**************************************
�}�N����`
***************************************/
#define SKYBOX_SIZE		(30000.0f)

/**************************************
�O���[�o���ϐ�
***************************************/
#ifdef _DEBUG

const char *FileName =
{
	"data/TEXTURE/dummyeffect.png"
};
SliceData wk;

#endif

/**************************************
����������
***************************************/
void GameScene::Init()
{
	ResourceManager::Instance()->LoadTexture("enemy01", "data/bullet001.png");

	player = new Player();
	skybox = new SkyBox(D3DXVECTOR3(SKYBOX_SIZE*2, SKYBOX_SIZE, SKYBOX_SIZE), D3DXVECTOR2(6.0f, 1.0f));
	enemy = new Enemy;

	skybox->LoadTexture("data/TEXTURE/skybox.png");


#ifdef _DEBUG
	InitSliceData();
#endif
}

/**************************************
�I������
***************************************/
void GameScene::Uninit()
{
	SAFE_DELETE(player);
	SAFE_DELETE(skybox);
	delete enemy;
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
	camera->target.y = camera->pos.y = 0.0f;

	enemy->UpdateEnemy();

	UpdateSliceEffect();
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

	enemy->DrawEnemy();

	DrawSliceEffect();
}


#ifdef _DEBUG
void InitSliceData()
{
	LPDIRECT3DDEVICE9 device = GetDevice();

	D3DXCreateTextureFromFile(device,							// �f�o�C�X�ւ̃|�C���^
		FileName,			// �t�@�C���̖��O
		&wk.D3DTexture);	// �ǂݍ��ރ������[

	wk.pos = GetCameraAdr()->target;
	wk.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	wk.rot = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	wk.move = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	wk.posVtx[0] = D3DXVECTOR3(-10.0f, 5.0f, 0.0f);
	wk.posVtx[1] = D3DXVECTOR3(10.0f, 5.0f, 0.0f);
	wk.posVtx[2] = D3DXVECTOR3(-10.0f, -5.0f, 0.0f);
	wk.posVtx[3] = D3DXVECTOR3(10.0f, -5.0f, 0.0f);

	wk.numVtx = 4;
	wk.numPolygon = 2;

}
#endif

void UpdateSliceEffect()
{
#ifdef _DEBUG
	if (GetKeyboardPress(DIK_SPACE))
	{
		const int devideX = 6;
		const int devideY = 3;

		// �e�N�X�`�����W�̐ݒ�
		int x = SliceEffect::cnt % devideX;
		int y = SliceEffect::cnt / devideX;
		float sizeX = 1.0f / devideX;
		float sizeY = 1.0f / devideY;

		wk.posUV[0] = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
		wk.posUV[1] = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
		wk.posUV[2] = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
		wk.posUV[3] = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);

		//float noX = (float)(SliceEffect::cnt % devideX);
		//float noY = (float)(SliceEffect::cnt / devideX);

		//float x = (1.0f / (float)devideX);
		//float y = (1.0f / (float)devideY);


		//wk.posUV[0] = D3DXVECTOR2(x * noX, y * noY);
		//wk.posUV[1] = D3DXVECTOR2(x * noX + x, y * noY);
		//wk.posUV[2] = D3DXVECTOR2(x * noX, y * noY + y);
		//wk.posUV[3] = D3DXVECTOR2(x * noX + x, y * noY + y);

		new SliceEffect(wk);


	}
	if (GetKeyboardPress(DIK_RIGHT))
	{
		GetCameraAdr()->pos.x += 10.0f;
		GetCameraAdr()->pos.z += 10.0f;

	}

	//if (GetKeyboardTrigger(DIK_Z))
	//{
	//	int a = 0;
	//}


#endif
	if (SliceEffect::root != NULL)
	{
		SliceEffect* wk = SliceEffect::root;
		SliceEffect* next = NULL;
		int cntEffect = SliceEffect::cnt;

		while (1)
		{
			next = wk->next;
			wk->Update();
			wk = next;

			if (wk == NULL)
			{
				break;
			}
		}
	}
}

void DrawSliceEffect()
{
	if (SliceEffect::root != NULL)
	{
		SliceEffect* wk = SliceEffect::root;
		for (int i = 0; i < SliceEffect::cnt; i++)
		{
			wk->Draw();
			wk = wk->next;
		}
	}

}