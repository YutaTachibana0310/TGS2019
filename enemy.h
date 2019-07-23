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
#define ENEMY_MAX				(50)	// �G�l�~�[�̑���

//=====================================================
// �G�l�~�[�^�C�v�̗�
//=====================================================
enum ENEMYTYPE
{
	ENEMYTYPE_MIN,
	ENEMYTYPE_01,
	ENEMYTYPE_02,
	ENEMYTYPE_03,
	ENEMYTYPE_MAX,
};

//=====================================================
// �N���X��`
//=====================================================
class Enemy
{
public:
/* �ϐ� */
	Transform		transform[ENEMY_MAX];
	bool			use[ENEMY_MAX];
	VERTEX_3D		*vtx;
	D3DXMATRIX		mtxWorld;

	LPDIRECT3DVERTEXBUFFER9	D3DVtxBuffEnemy[ENEMY_MAX];
	LPDIRECT3DTEXTURE9		D3DTextureEnemy[ENEMYTYPE_MAX];
	int						texNum[ENEMY_MAX];

/* �֐� */
	Enemy();
	~Enemy();
	void UpdateEnemy();
	void DrawEnemy();
	HRESULT MakeVertexEnemy(int eno, LPDIRECT3DDEVICE9 pDevice);
	//===============================================================================
	// ���_���W�̐ݒ�
	// ��P�����Fint index(�o�b�t�@�[�̃A�h���X�ԍ�)
	// �߂�l�F�Ȃ�
	//===============================================================================
	void SetVertexEnemy(int index);

	//===============================================================================
	// �G�l�~�[�̐ݒu
	// ��P�����Fint type(�G�l�~�[�^�C�v)
	// ��Q�����FD3DXVECTOR3 pos(�ݒu����ʒu)
	// �߂�l�F�Ȃ�
	//===============================================================================
	void SetEnemy(int type, D3DXVECTOR3 pos);
};


#endif