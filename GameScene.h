//=====================================
//
//�Q�[���V�[���w�b�_[GameScene.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

#include "main.h"
#include "Framework\IStateScene.h"

#include "Player.h"
#include "Framework\SkyBox.h"
#include "enemy.h"
#include "Ground.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class GameScene : public IStateScene
{
public:
	void Init() override;
	void Uninit() override;
	void Update(HWND hWnd) override;
	void Draw() override;

	Player *player;
	SkyBox *skybox;
	Ground *ground;
};

#endif