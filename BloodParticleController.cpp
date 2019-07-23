//=====================================
//
//テンプレート処理[BloodParticleController.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "BloodParticleController.h"
#include "BloodParticle.h"

/**************************************
マクロ定義
***************************************/
typedef BaseParticleController Base;

/**************************************
初期化
***************************************/
void BloodParticleController::Init()
{
	Base::MakeUnitBuffer(&D3DXVECTOR2(100.0f, 100.0f), &D3DXVECTOR2(8.0f, 8.0f));
	Base::LoadTexture("data/TEXTURE/particle00.png");

	particleContainer.resize(1024);
	for (auto& particle : particleContainer)
	{
		particle = new BloodParticle();
		static_cast<BloodParticle*>(particle)->SetAnimParameter(&D3DXVECTOR2(8.0f, 8.0f));
	}

	emitterContainer.resize(64);
	for (auto& emitter : emitterContainer)
	{
		emitter = new BloodParticleEmitter();
	}
}

#include "Framework\Easing.h"
/**************************************
方y出
***************************************/
void BloodParticleController::Emit()
{
Base:ForEachEmitter(10,
	[](BaseEmitter *emitter, BaseParticle *particle)
	{
		BloodParticleEmitter *entity = static_cast<BloodParticleEmitter*>(emitter);

		float t = RandomRangef(0.0f, 1.0f);
		D3DXVECTOR3 pos = Easing<D3DXVECTOR3>::GetEasingValue(t, &entity->right, &entity->left, EasingType::Linear);

		particle->transform.pos = pos;

		particle->Init();
	});
}

#include <algorithm>
using namespace std;
/**************************************
エミッタセット
***************************************/
void BloodParticleController::SetEmitter(D3DXVECTOR3 right, D3DXVECTOR3 left)
{
	auto emitter = find_if(emitterContainer.begin(), emitterContainer.end(), [](BaseEmitter* emitter)
	{
		return !emitter->active;
	});

	if (emitter != emitterContainer.end())
	{
		BloodParticleEmitter *entity = static_cast<BloodParticleEmitter*>(*emitter);
		entity->right = right;
		entity->left = left;
		entity->Init();
	}
}