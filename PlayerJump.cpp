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

static D3DXVECTOR3 initVelocity = D3DXVECTOR3(0.0f, 500.0f, 0.0f);
static D3DXVECTOR3 lastVelocity = D3DXVECTOR3(0.0f, -700.0f, 0.0f);

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

	float t = entity->cntFrame / 30.0f;
	entity->velocity = Easing<D3DXVECTOR3>::GetEasingValue(t, &initVelocity, &lastVelocity, EasingType::InOutCubic);
	entity->transform.pos += entity->velocity;

	//ここの後ろの条件をマップとにする
	if (entity->velocity.y < 0.0f && entity->transform.pos.y < 0.0f)
	{
		entity->ChangeState(PlayerState::IdleState);
	}

	return 0;
}