//=====================================
//
//プレイヤージャンプ処理[PlayerJump.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "PlayerJump.h"
#include "Player.h"
#include "Framework\Easing.h"

/**************************************
マクロ定義
***************************************/

static float initVelocity = 10.0f;
static float lastVelocity = -20.0f;

/**************************************
入場処理
***************************************/
void PlayerJump::OnStart(Player* entity)
{
	entity->animIndex = 0;
	entity->animCount = 0;
	entity->cntFrame = 0;

	entity->textureID = PlayerTexture::RunTexture;
}

/**************************************
更新処理
***************************************/
int PlayerJump::OnUpdate(Player* entity)
{
	entity->cntFrame++;

	entity->transform.pos += entity->velocity;

	float t = entity->cntFrame / 60.0f;
	entity->velocity.y = Easing<float>::GetEasingValue(t, &initVelocity, &lastVelocity, EasingType::InOutCubic);

	if(entity->IsCheckHitGround())
	{
		entity->ChangeState(PlayerState::IdleState);
	}

	return 0;
}