//=================================================
// �G�l�~�[�w�b�_�[[enemy.h]
// �쐬�ҁF�c�����z
//=================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#include "Framework/Transform.h"

//=====================================================
// �}�N����`
//=====================================================
#define ENEMY_MAX				(20)	// �G�l�~�[�̑���

//=====================================================
// �G�l�~�[�^�C�v�̗�
//=====================================================
enum ENEMYTYPE
{
	ENEMYTYPE_01,
	ENEMYTYPE_02,
	ENEMYTYPE_03,
	ENEMYTYPE_MAX,
};

enum ENEMYMOVE
{
	MOVE_01,
	MOVE_02,
};

//=====================================================
// �N���X��`
//=====================================================
class Enemy
{
public:
/* �ϐ� */
	LPDIRECT3DVERTEXBUFFER9	D3DVtxBuffEnemy;
	LPDIRECT3DTEXTURE9		D3DTextureEnemy;
	Transform				transform;
	VERTEX_3D				*vtx;
	D3DXMATRIX				mtxWorld;
	int						texNum;
	int						cntFrame;
	float					move;
	bool					use;
	const char *fileName[ENEMYTYPE_MAX]
	{
		"data/TEXTURE/bullet001.png",
	};


/* �֐� */
	Enemy();
	~Enemy();
	void UpdateEnemy();
	void DrawEnemy();
	HRESULT MakeVertexEnemy(LPDIRECT3DDEVICE9 pDevice);
	//===============================================================================
	// ���_���W�̐ݒ�
	// ��P�����Fint index(�o�b�t�@�[�̃A�h���X�ԍ�)
	// �߂�l�F�Ȃ�
	//===============================================================================
	void SetVertexEnemy(void);

	//===============================================================================
	// �G�l�~�[�̐ݒu
	// ��P�����Fint type(�G�l�~�[�^�C�v)
	// ��Q�����FD3DXVECTOR3 pos(�ݒu����ʒu)
	// �߂�l�F�Ȃ�
	//===============================================================================
	void SetEnemy(int type, D3DXVECTOR3 pos);
	void MoveTypeEnemy(int type);

	void MoveEnemy(D3DXVECTOR3 pos);

};


#endif