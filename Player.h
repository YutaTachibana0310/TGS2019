//=====================================
//
//�v���C���[�w�b�_[Player.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include <vector>

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
#include "Framework\MeshContainer.h"
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

	Transform transform;

	std::vector<LPDIRECT3DTEXTURE9> textures;
	LPDIRECT3DVERTEXBUFFER9 vtxBuff;


	int currentState;
	int textureIndex;

	int animCount;
	int animIndex;
};

#endif