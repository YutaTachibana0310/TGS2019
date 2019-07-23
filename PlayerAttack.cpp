//=====================================
//
//�v���C���[�A�^�b�N����[PlayerAttack.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "PlayerAttack.h"

/**************************************
�}�N����`
***************************************/
#define PLAYERATTACK_EFFECTIVE_DURATION		(30)

/**************************************
�R���X�g���N�^
***************************************/
PlayerAttack::PlayerAttack()
{
	collider = new BoxCollider3D(BoxCollider3DTag::PlayerAttack, &transform.pos);
	collider->active = false;
}

/**************************************
�f�X�g���N�^
***************************************/
PlayerAttack::~PlayerAttack()
{
	SAFE_DELETE(collider);
}

/**************************************
������
***************************************/
void PlayerAttack::Init()
{
	cntFrame = 0;
	collider->active = true;
	active = true;
}

/**************************************
�I��
***************************************/
void PlayerAttack::Uninit()
{
	collider->active = false;
	active = false;
}

/**************************************
�X�V
***************************************/
void PlayerAttack::Update()
{
	if (!active)
		return;

	cntFrame++;

	if (cntFrame == PLAYERATTACK_EFFECTIVE_DURATION)
		Uninit();
}

/**************************************
�`��
***************************************/
void PlayerAttack::Draw()
{
	if (!active)
		return;


#ifdef _DEBUG
	BoxCollider3D::DrawCollider(collider);
#endif
}
