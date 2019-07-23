//=====================================
//
//テンプレートヘッダ[BloodParticle.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _BLOODPARTICLE_H_
#define _BLOODPARTICLE_H_

#include "main.h"

#include "Framework\AnimationParticle.h"
#include "Framework\BaseEmitter.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class BloodParticle : public AnimationParticle
{
public:
	void Init();
	void Update();
	void Uninit();
};

class BloodParticleEmitter : public BaseEmitter
{
public:
	void Init();
	void Update();

	D3DXVECTOR3 right;
	D3DXVECTOR3 left;
};

#endif