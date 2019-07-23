//=====================================
//
//�v���C���[�A�^�b�N�w�b�_[PlayerAttack.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _PLAYERATTACK_H_
#define _PLAYERATTACK_H_

#include "main.h"
#include "Framework\BoxCollider3D.h"

/**************************************
�}�N����`
***************************************/
#include "Framework\MeshContainer.h"
/**************************************
�N���X��`
***************************************/
class PlayerAttack
{
public:
	PlayerAttack();
	~PlayerAttack();

	void Init();
	void Uninit();
	void Update();
	void Draw();

	bool active = false;
	int cntFrame;
	Transform transform;
	BoxCollider3D *collider;

	MeshContainer *mesh;

	LPDIRECT3DTEXTURE9 texture;
	LPDIRECT3DVERTEXBUFFER9 vtxBuff;
};

#endif