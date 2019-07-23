//=============================================================================
//
// �G�l�~�[���� [enemy.cpp]
// Author : GP11A341_22_�c�����z
//
//=============================================================================
#include "main.h"
#include "enemy.h"
#include "camera.h"
#include "Framework/ResourceManager.h"
#include "input.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define ENEMY_INIT_POS_X		(0.0f)	// �G�l�~�[�̏����ʒu
#define ENEMY_INIT_POS_Y		(0.0f)	// 
#define ENEMY_SIZE_X			(100)	// �G�l�~�[�̕�
#define ENEMY_SIZE_Y			(100)	// �G�l�~�[�̍���

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
Enemy::Enemy()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�N�X�`���̐ݒ�
	D3DTextureEnemy[ENEMYTYPE_MIN] = NULL;
	ResourceManager::Instance()->GetTexture("enemy01", &D3DTextureEnemy[ENEMYTYPE_01]);
	ResourceManager::Instance()->GetTexture("enemy02", &D3DTextureEnemy[ENEMYTYPE_02]);
	ResourceManager::Instance()->GetTexture("enemy03", &D3DTextureEnemy[ENEMYTYPE_03]);

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		transform[i].pos = D3DXVECTOR3(ENEMY_INIT_POS_X, ENEMY_INIT_POS_Y, 0.0f);	// �ʒu��������
		transform[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		transform[i].scale= D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		use[i] = false;
		texNum[i] = ENEMYTYPE_01;
		D3DVtxBuffEnemy[i] = NULL;
	
		// ���_���̍쐬
		MakeVertexEnemy(i, pDevice);
	}
}

//=============================================================================
// �f�X�X�g���N�^
//=============================================================================
Enemy::~Enemy()
{

}

//=============================================================================
// �X�V����
//=============================================================================
void Enemy::UpdateEnemy(void)
{
	if (GetKeyboardTrigger(DIK_A))
	{
		SetEnemy(1, transform->pos + D3DXVECTOR3(50.0f, 0.0f, 0.0f));
	}

	if (GetKeyboardPress(DIK_LEFT))
	{
		transform[0].pos.x -= 1.0f;
	}

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (use[i])
		{
			SetVertexEnemy(i);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void Enemy :: DrawEnemy()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView, mtxScale, mtxTranslate;

	// ���C���e�B���O�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if(use[i])
		{
			// �r���[�}�g���b�N�X���擾
			mtxView = GetMtxView();

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&mtxWorld);

			// �|���S���𐳖ʂɌ�����
			//mtxWorld._11 = mtxView._11;
			//mtxWorld._12 = mtxView._21;
			//mtxWorld._13 = mtxView._31;
			//mtxWorld._21 = mtxView._12;
			//mtxWorld._22 = mtxView._22;
			//mtxWorld._23 = mtxView._32;
			//mtxWorld._31 = mtxView._13;
			//mtxWorld._32 = mtxView._23;
			//mtxWorld._33 = mtxView._33;

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxScale, transform[i].scale.x, transform[i].scale.y, transform[i].scale.z);
			D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScale);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, transform[i].pos.x, transform[i].pos.y, transform[i].pos.z);
			D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
			pDevice->SetStreamSource(0, D3DVtxBuffEnemy[i], 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, D3DTextureEnemy[texNum[i]]);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (i * NUM_VERTEX), NUM_POLYGON);
		}
	}
}

//===============================================================================
// ���_���̍쐬
//===============================================================================
HRESULT Enemy::MakeVertexEnemy(int eno, LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_3D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&D3DVtxBuffEnemy[eno],			// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		D3DVtxBuffEnemy[eno]->Lock(0, 0, (void**)&vtx, 0);
		{
			// ���_���W�̐ݒ�
			vtx[0].vtx = D3DXVECTOR3(-ENEMY_SIZE_X, ENEMY_SIZE_Y, 0.0f);
			vtx[1].vtx = D3DXVECTOR3(ENEMY_SIZE_X, ENEMY_SIZE_Y, 0.0f);
			vtx[2].vtx = D3DXVECTOR3(-ENEMY_SIZE_X, -ENEMY_SIZE_Y, 0.0f);
			vtx[3].vtx = D3DXVECTOR3(ENEMY_SIZE_X, -ENEMY_SIZE_Y, 0.0f);

			// �@���̐ݒ�
			vtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			vtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			vtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			vtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

			// ���ˌ��̐ݒ�
			vtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			vtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			vtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			vtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// �e�N�X�`�����W�̐ݒ�
			vtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
			vtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
			vtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
			vtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
		}

		// ���_�f�[�^���A�����b�N����
		D3DVtxBuffEnemy[eno]->Unlock();
	}

	return S_OK;
}

//=================================================================================
// ���_���W�̐ݒ�
//=================================================================================
void Enemy::SetVertexEnemy(int index)
{
	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	D3DVtxBuffEnemy[index]->Lock(0, 0, (void**)&vtx, 0);

	// ���_���W�̐ݒ�
	vtx[0].vtx = D3DXVECTOR3(-ENEMY_SIZE_X, ENEMY_SIZE_Y, 0.0f);
	vtx[1].vtx = D3DXVECTOR3(ENEMY_SIZE_X, ENEMY_SIZE_Y, 0.0f);
	vtx[2].vtx = D3DXVECTOR3(-ENEMY_SIZE_X, -ENEMY_SIZE_Y, 0.0f);
	vtx[3].vtx = D3DXVECTOR3(ENEMY_SIZE_X, -ENEMY_SIZE_Y, 0.0f);

	// ���_�f�[�^���A�����b�N����
	D3DVtxBuffEnemy[index]->Unlock();
}


//===============================================================================
// �G�l�~�[�̐ݒu
//===============================================================================
void Enemy::SetEnemy(int type, D3DXVECTOR3 setPos)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (!use[i])
		{
			use[i] = true;
			transform[i].pos = setPos;
			texNum[i] = type;
			SetVertexEnemy(i);

			return;
		}
	}
}
