//=====================================
//
//�v���C���[�w�b�_[Player.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "Framework\IStateMachine.h"

#include <vector>
#include <map>

#define PLAYER_ANIM_LOOPMAX		(10)
#define PLAYER_JUMP_ENABLEFRAME	(5)
/**************************************
�}�N����`
***************************************/
enum PlayerState
{
	IdleState,
	JumpState,
	MoveState,
	PlayerStateMax
};

enum PlayerTexture
{
	WalkTexture,
	RunTexture,
	IdleTexture,
	AttackTexture,
	PlayerTextureMax
};

/**************************************
�N���X��`
***************************************/
class Player
{
public:
	Player();
	~Player();

	void Update();
	void Draw();

	void ChangeState(PlayerState next);
	bool IsCheckHitGround();
	void CheckAnimationFinish();

	Transform transform;

	std::vector<LPDIRECT3DTEXTURE9> textures;
	LPDIRECT3DVERTEXBUFFER9 vtxBuff;


	PlayerState currentState;
	int textureID;

	int animCount;
	int animIndex;

	std::map<PlayerState, IStateMachine<Player>*> stateMachine;

	D3DXVECTOR3 velocity;
	int cntFrame;

	int atkInterval;
	int jumpInterval;
};

#endif