//=============================================================================
//
// �G�l�~�[���� [enemy.cpp]
// Author : GP11A341_22_�c�����z
//
//=============================================================================
#include "main.h"
#include "enemy.h"
#include "camera.h"

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
HRESULT MakeVertexEnemy(int eno);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************


//=============================================================================
// �R���X�g���N�^
//=============================================================================
Enemy::Enemy()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		pos[i] = D3DXVECTOR3(ENEMY_INIT_POS_X, ENEMY_INIT_POS_Y, 0.0f);	// �ʒu��������
		rot[i] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ��]��������
		use[i] = false;					// ���C�t��������

		// ���_���̍쐬
		MakeVertexEnemy(pDevice);
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
}

//=============================================================================
// �`�揈��
//=============================================================================
void Enemy :: DrawEnemy()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView, mtxScale, mtxTranslate;

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if(use[i])
		{
			// �r���[�}�g���b�N�X���擾
			mtxView = GetMtxView();

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&mtxWorld);

			// �|���S���𐳖ʂɌ�����
			mtxWorld._11 = mtxView._11;
			mtxWorld._12 = mtxView._21;
			mtxWorld._13 = mtxView._31;
			mtxWorld._21 = mtxView._12;
			mtxWorld._22 = mtxView._22;
			mtxWorld._23 = mtxView._32;
			mtxWorld._31 = mtxView._13;
			mtxWorld._32 = mtxView._23;
			mtxWorld._33 = mtxView._33;

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxScale, scl[i].x, scl[i].y, scl[i].z);
			D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScale);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, pos[i].x, pos[i].y, pos[i].z);
			D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
			pDevice->SetStreamSource(0, D3DVtxBuffEnemy, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, D3DTextureEnemy);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (i * NUM_VERTEX), NUM_POLYGON);
		}
	}
}

//===============================================================================
// ���_���̍쐬
//===============================================================================
HRESULT Enemy::MakeVertexEnemy(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * ENEMY_MAX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_3D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&D3DVtxBuffEnemy,	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		D3DVtxBuffEnemy->Lock(0, 0, (void**)&vtx, 0);

		for (int i = 0; i < ENEMY_MAX; i++, vtx += 4)
		{
			// ���_���W�̐ݒ�
			vtx[0].vtx = D3DXVECTOR3(-ENEMY_SIZE_X / 2, -ENEMY_SIZE_Y / 2, 0.0f);
			vtx[1].vtx = D3DXVECTOR3(-ENEMY_SIZE_X / 2, ENEMY_SIZE_Y / 2, 0.0f);
			vtx[2].vtx = D3DXVECTOR3(ENEMY_SIZE_X / 2, -ENEMY_SIZE_Y / 2, 0.0f);
			vtx[3].vtx = D3DXVECTOR3(ENEMY_SIZE_X / 2, ENEMY_SIZE_Y / 2, 0.0f);

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
		D3DVtxBuffEnemy->Unlock();
	}

	return S_OK;
}

