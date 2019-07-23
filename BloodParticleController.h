//=====================================
//
//テンプレートヘッダ[BloodParticleController.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _BLOODPARTICLECONTROLLER_H_
#define _BLOODPARTICLECONTROLLER_H_

#include "main.h"
#include "Framework\BaseParticleController.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class BloodParticleController :public BaseParticleController
{
public:
	void Init();
	void Emit();
	void SetEmitter(D3DXVECTOR3 right, D3DXVECTOR3 left);
};

#endif