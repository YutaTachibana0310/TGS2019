//=================================================
// エネミーヘッダー[enemy.h]
// 作成者：田中太陽
//=================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"

#define ENEMY_MAX				(128)	// エネミーの総数

class Enemy
{
public:
/* 変数 */
	D3DXVECTOR3		pos[ENEMY_MAX];
	D3DXVECTOR3		rot[ENEMY_MAX];
	D3DXVECTOR3		scl[ENEMY_MAX];
	bool			use[ENEMY_MAX];
	VERTEX_3D		*vtx;
	D3DXMATRIX		mtxWorld;						// ワールドマトリックス

	LPDIRECT3DVERTEXBUFFER9			D3DVtxBuffEnemy;
	static LPDIRECT3DTEXTURE9		D3DTextureEnemy[ENEMYTYPE_MAX];


/* 関数 */
	Enemy();
	~Enemy();
	void UpdateEnemy();
	void DrawEnemy();
	HRESULT MakeVertexEnemy(LPDIRECT3DDEVICE9 pDevice);

};

//=====================================================
// エネミータイプの列挙
//=====================================================
enum ENEMYTYPE
{
	ENEMYTYPE_MIN,
	ENEMYTYPE_01,
	ENEMYTYPE_02,
	ENEMYTYPE_03,
	ENEMYTYPE_MAX,
};

#endif