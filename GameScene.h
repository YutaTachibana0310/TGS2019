//=====================================
//
//ゲームシーンヘッダ[GameScene.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

#include "main.h"
#include "Framework\IStateScene.h"
#include "enemy.h"
/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class GameScene : public IStateScene
{
public:
	void Init() override;
	void Uninit() override;
	void Update(HWND hWnd) override;
	void Draw() override;

	Enemy *enemy;
};

#endif