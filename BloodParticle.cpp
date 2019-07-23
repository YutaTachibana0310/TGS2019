//=====================================
//
//�e���v���[�g����[BloodParticle.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "BloodParticle.h"

/**************************************
�}�N����`
***************************************/
#define BLOODPARTICLE_LIFE_MAX		(50)
#define BLOODPARTICLE_LIFE_MIN		(20)

#define BLOODPARTICLE_EMITTER_DURATION	(5)

/**************************************
������
***************************************/
void BloodParticle::Init()
{
	cntFrame = 0;
	active = true;

	lifeFrame = RandomRange(BLOODPARTICLE_LIFE_MIN, BLOODPARTICLE_LIFE_MAX);

	transform.Rotate(0.0f, 0.0f, RandomRangef(0.0f, 360.0f));
}

/**************************************
�X�V
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
�I��
***************************************/
void BloodParticle::Uninit()
{
	active = false;
}

/**************************************
������
***************************************/
void BloodParticleEmitter::Init()
{
	active = true;
	cntFrame = 0;
	duration = BLOODPARTICLE_EMITTER_DURATION;
}

/**************************************
�X�V
***************************************/
void BloodParticleEmitter::Update()
{
	cntFrame++;
	if (cntFrame == duration)
		active = false;
}