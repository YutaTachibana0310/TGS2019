//=================================================
// エネミーヘッダー[enemy.h]
// 作成者：田中太陽
//=================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#include "Framework/Transform.h"

//=====================================================
// マクロ定義
//=====================================================
#define ENEMY_MAX				(50)	// エネミーの総数

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

//=====================================================
// クラス定義
//=====================================================
class Enemy
{
public:
/* 変数 */
	Transform		transform;
	bool			use;
	VERTEX_3D		*vtx;
	D3DXMATRIX		mtxWorld;

	LPDIRECT3DVERTEXBUFFER9	D3DVtxBuffEnemy;
	LPDIRECT3DTEXTURE9		D3DTextureEnemy;
	int						texNum;

/* 関数 */
	Enemy();
	~Enemy();
	void UpdateEnemy();
	void DrawEnemy();
	HRESULT MakeVertexEnemy(LPDIRECT3DDEVICE9 pDevice);
	//===============================================================================
	// 頂点座標の設定
	// 第１引数：int index(バッファーのアドレス番号)
	// 戻り値：なし
	//===============================================================================
	void SetVertexEnemy(void);

	//===============================================================================
	// エネミーの設置
	// 第１引数：int type(エネミータイプ)
	// 第２引数：D3DXVECTOR3 pos(設置する位置)
	// 戻り値：なし
	//===============================================================================
	void SetEnemy(int type, D3DXVECTOR3 pos);
};


#endif