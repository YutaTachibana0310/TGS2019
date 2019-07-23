//=====================================
//
//�v���C���[�A�C�h������[PlayerIdle.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "PlayerIdle.h"
#include "Player.h"
#include "input.h"

/**************************************
�}�N����`
***************************************/

/**************************************
���ꏈ��
***************************************/
void PlayerIdle::OnStart(Player* entity)
{
	entity->textureID = PlayerTexture::IdleTexture;
}

/**************************************
�X�V����
***************************************/
int PlayerIdle::OnUpdate(Player* entity)
{
	if (GetVerticalInput() == 1.0f)
	{
		entity->ChangeState(JumpState);
	}

	return 0;
}