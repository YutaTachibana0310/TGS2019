//=====================================
//
//�O���E���h�w�b�_[Ground.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _GROUND_H_
#define _GROUND_H_

#include "main.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class Ground
{
public:
	Ground();
	~Ground();

	void Draw();

	LPDIRECT3DVERTEXBUFFER9 vtxBuff;
	LPDIRECT3DTEXTURE9 texture;
	Transform transform;
};

#endif