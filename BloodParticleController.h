//=====================================
//
//�e���v���[�g�w�b�_[BloodParticleController.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _BLOODPARTICLECONTROLLER_H_
#define _BLOODPARTICLECONTROLLER_H_

#include "main.h"
#include "Framework\BaseParticleController.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class BloodParticleController :public BaseParticleController
{
public:
	void Init();
	void Emit();
	void SetEmitter(D3DXVECTOR3 right, D3DXVECTOR3 left);
};

#endif