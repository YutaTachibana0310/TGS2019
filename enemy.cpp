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
#define ENEMY_INIT_POS_X		(200.0f)	// �G�l�~�[�̏����ʒu
#define ENEMY_INIT_POS_Y		(0.0f)	// 
#define ENEMY_SIZE_X			(100)	// �G�l�~�[�̕�
#define ENEMY_SIZE_Y			(100)	// �G�l�~�[�̍���
#define ENEMY_MOVE_TIME			(180)	// �G�l�~�[�̓����t���[����

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
	//ResourceManager::Instance()->GetTexture("enemy01", &D3DTextureEnemy);
	//ResourceManager::Instance()->GetTexture("enemy02", &D3DTextureEnemy[ENEMYTYPE_02]);
	//ResourceManager::Instance()->GetTexture("enemy03", &D3DTextureEnemy[ENEMYTYPE_03]);
	
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
		fileName[ENEMYTYPE_01],					// �t�@�C���̖��O
		&D3DTextureEnemy);			// �ǂݍ��ރ������[

	collider = new BoxCollider3D(BoxCollider3DTag::Enemy, &transform.pos);
	collider->active = true;

	transform.pos = D3DXVECTOR3(ENEMY_INIT_POS_X, ENEMY_INIT_POS_Y, 0.0f);	// �ʒu��������
	transform.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	transform.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	use = true;
	cntFrame = 0;
	texNum = ENEMYTYPE_01;
	D3DVtxBuffEnemy = NULL;

	// ���_���̍쐬
	MakeVertexEnemy(pDevice);
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

	// ���C���e�B���O�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	if (use)
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
		D3DXMatrixScaling(&mtxScale, transform.scale.x, transform.scale.y, transform.scale.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScale);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTranslate, transform.pos.x, transform.pos.y, transform.pos.z);
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
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	}
}


//===============================================================================
// ���_���̍쐬
//===============================================================================
HRESULT Enemy::MakeVertexEnemy(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_3D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&D3DVtxBuffEnemy,			// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		D3DVtxBuffEnemy->Lock(0, 0, (void**)&vtx, 0);
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
		D3DVtxBuffEnemy->Unlock();
	}

	return S_OK;
}

//=================================================================================
// ���_���W�̐ݒ�
//=================================================================================
void Enemy::SetVertexEnemy()
{
	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	D3DVtxBuffEnemy->Lock(0, 0, (void**)&vtx, 0);

	// ���_���W�̐ݒ�
	vtx[0].vtx = D3DXVECTOR3(-ENEMY_SIZE_X, ENEMY_SIZE_Y, 0.0f);
	vtx[1].vtx = D3DXVECTOR3(ENEMY_SIZE_X, ENEMY_SIZE_Y, 0.0f);
	vtx[2].vtx = D3DXVECTOR3(-ENEMY_SIZE_X, -ENEMY_SIZE_Y, 0.0f);
	vtx[3].vtx = D3DXVECTOR3(ENEMY_SIZE_X, -ENEMY_SIZE_Y, 0.0f);

	// ���_�f�[�^���A�����b�N����
	D3DVtxBuffEnemy->Unlock();
}


//===============================================================================
// �G�l�~�[�̐ݒu
//===============================================================================
void Enemy::SetEnemy(int type, D3DXVECTOR3 setPos)
{
 	if (!use)
	{
		use = true;
		transform.pos = setPos;
		texNum = type;
		cntFrame = 0;
		SetVertexEnemy();

		return;
	}
}

//===============================================================================
// �G�l�~�[�^�C�v�ʂ̓���
//===============================================================================
void Enemy::MoveTypeEnemy(int type)
{
	switch (type)
	{
	case ENEMYTYPE_01:
			
		//MoveEnemy();

		break;
	case ENEMYTYPE_02:
		break;
	case ENEMYTYPE_03:
		break;
	}
}

//===============================================================================
// �G�l�~�[�̓���
//===============================================================================
void Enemy::MoveEnemy(D3DXVECTOR3 pos)
{
	D3DXVECTOR3 vec;
	float len;

	vec = pos - transform.pos;
	D3DXVec3Normalize(&vec, &vec);

	transform.pos += vec * 1.5f;

	//if (cntFrame < ENEMY_MOVE_TIME)
	//{
	//	transform.pos.x += 2.0f;
	//}
	//else if (cntFrame < (ENEMY_MOVE_TIME * 2))
	//{
	//	transform.pos.x -= 2.0f;
	//}
	//else
	//{
	//	cntFrame = 0;
	//}
}
