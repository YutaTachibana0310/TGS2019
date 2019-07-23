//=====================================
//
//プレイヤーアイドルヘッダ[PlayerIdle.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _PLAYERIDLE_H_
#define _PLAYERIDLE_H_

#include "main.h"
#include "Framework\IStateMachine.h"

/**************************************
マクロ定義
***************************************/
class Player;

/**************************************
クラス定義
***************************************/
class PlayerIdle : public IStateMachine<Player>
{
	void OnStart(Player* entity);
	int OnUpdate(Player* entity);
};

#endif