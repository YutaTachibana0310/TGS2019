//=====================================
//
//�v���C���[�W�����v����[PlayerJump.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "PlayerJump.h"
#include "Player.h"
#include "Framework\Easing.h"

/**************************************
�}�N����`
***************************************/

static float initVelocity = 500.0f;
static float lastVelocity = -700.0f;

/**************************************
���ꏈ��
***************************************/
void PlayerJump::OnStart(Player* entity)
{
	entity->animIndex = 0;
	entity->animCount = 0;
	entity->cntFrame = 0;

	entity->textureID = PlayerTexture::RunTexture;
}

/**************************************
�X�V����
***************************************/
int PlayerJump::OnUpdate(Player* entity)
{
	entity->cntFrame++;

	entity->transform.pos += entity->velocity;

	float t = entity->cntFrame / 30.0f;
	entity->velocity.y = Easing<float>::GetEasingValue(t, &initVelocity, &lastVelocity, EasingType::InOutCubic);

	if(entity->IsCheckHitGround())
	{
		entity->ChangeState(PlayerState::IdleState);
	}

	return 0;
}