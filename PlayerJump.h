//=====================================
//
//�v���C���[�W�����v�w�b�_[PlayerJump.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _PLAYERJUMP_H_
#define _PLAYERJUMP_H_

#include "main.h"
#include "Framework\IStateMachine.h"

/**************************************
�}�N����`
***************************************/
class Player;

/**************************************
�N���X��`
***************************************/
class PlayerJump : public IStateMachine<Player>
{
	void OnStart(Player* entity);
	int OnUpdate(Player* entity);
};

#endif