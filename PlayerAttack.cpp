//=====================================
//
//プレイヤーアタック処理[PlayerAttack.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "PlayerAttack.h"

/**************************************
マクロ定義
***************************************/
#define PLAYERATTACK_EFFECTIVE_DURATION		(30)

/**************************************
コンストラクタ
***************************************/
PlayerAttack::PlayerAttack()
{
	collider = new BoxCollider3D(BoxCollider3DTag::PlayerAttack, &transform.pos);
	collider->active = false;
}

/**************************************
デストラクタ
***************************************/
PlayerAttack::~PlayerAttack()
{
	SAFE_DELETE(collider);
}

/**************************************
初期化
***************************************/
void PlayerAttack::Init()
{
	cntFrame = 0;
	collider->active = true;
	active = true;
}

/**************************************
終了
***************************************/
void PlayerAttack::Uninit()
{
	collider->active = false;
	active = false;
}

/**************************************
更新
***************************************/
void PlayerAttack::Update()
{
	if (!active)
		return;

	cntFrame++;

	if (cntFrame == PLAYERATTACK_EFFECTIVE_DURATION)
		Uninit();
}

/**************************************
描画
***************************************/
void PlayerAttack::Draw()
{
	if (!active)
		return;


#ifdef _DEBUG
	BoxCollider3D::DrawCollider(collider);
#endif
}
