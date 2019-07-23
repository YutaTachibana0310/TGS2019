//=====================================
//
//グラウンドヘッダ[Ground.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _GROUND_H_
#define _GROUND_H_

#include "main.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
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