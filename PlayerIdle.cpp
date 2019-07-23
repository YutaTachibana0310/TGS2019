//=====================================
//
//プレイヤーアイドル処理[PlayerIdle.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "PlayerIdle.h"
#include "Player.h"
#include "input.h"

/**************************************
マクロ定義
***************************************/

/**************************************
入場処理
***************************************/
void PlayerIdle::OnStart(Player* entity)
{
	entity->textureID = PlayerTexture::IdleTexture;
}

/**************************************
更新処理
***************************************/
int PlayerIdle::OnUpdate(Player* entity)
{
	if (GetVerticalInput() == 1.0f)
	{
		entity->ChangeState(JumpState);
	}

	return 0;
}