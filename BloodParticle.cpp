//=====================================
//
//テンプレート処理[BloodParticle.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "BloodParticle.h"

/**************************************
マクロ定義
***************************************/
#define BLOODPARTICLE_LIFE_MAX		(50)
#define BLOODPARTICLE_LIFE_MIN		(20)

#define BLOODPARTICLE_EMITTER_DURATION	(5)

/**************************************
初期化
***************************************/
void BloodParticle::Init()
{
	cntFrame = 0;
	active = true;

	lifeFrame = RandomRange(BLOODPARTICLE_LIFE_MIN, BLOODPARTICLE_LIFE_MAX);

	transform.Rotate(0.0f, 0.0f, RandomRangef(0.0f, 360.0f));
}

/**************************************
更新
***************************************/
void BloodParticle::Update()
{
	cntFrame = 0;

	float t = (float)cntFrame / lifeFrame;
	Animation(t);

	if (cntFrame == lifeFrame)
		Uninit();
}

/**************************************
終了
***************************************/
void BloodParticle::Uninit()
{
	active = false;
}

/**************************************
初期化
***************************************/
void BloodParticleEmitter::Init()
{
	active = true;
	cntFrame = 0;
	duration = BLOODPARTICLE_EMITTER_DURATION;
}

/**************************************
更新
***************************************/
void BloodParticleEmitter::Update()
{
	cntFrame++;
	if (cntFrame == duration)
		active = false;
}