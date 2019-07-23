//=================================================
// �G�l�~�[�w�b�_�[[enemy.h]
// �쐬�ҁF�c�����z
//=================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"

#define ENEMY_MAX				(128)	// �G�l�~�[�̑���

class Enemy
{
public:
/* �ϐ� */
	D3DXVECTOR3		pos[ENEMY_MAX];
	D3DXVECTOR3		rot[ENEMY_MAX];
	D3DXVECTOR3		scl[ENEMY_MAX];
	bool			use[ENEMY_MAX];
	VERTEX_3D		*vtx;
	D3DXMATRIX		mtxWorld;						// ���[���h�}�g���b�N�X

	LPDIRECT3DVERTEXBUFFER9			D3DVtxBuffEnemy;
	static LPDIRECT3DTEXTURE9		D3DTextureEnemy[ENEMYTYPE_MAX];


/* �֐� */
	Enemy();
	~Enemy();
	void UpdateEnemy();
	void DrawEnemy();
	HRESULT MakeVertexEnemy(LPDIRECT3DDEVICE9 pDevice);

};

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

#endif