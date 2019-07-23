//=====================================
//
//プレイヤージャンプヘッダ[PlayerJump.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _PLAYERJUMP_H_
#define _PLAYERJUMP_H_

#include "main.h"
#include "Framework\IStateMachine.h"

/**************************************
マクロ定義
***************************************/
class Player;

/**************************************
クラス定義
***************************************/
class PlayerJump : public IStateMachine<Player>
{
	void OnStart(Player* entity);
	int OnUpdate(Player* entity);
};

#endif