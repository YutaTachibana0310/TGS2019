//=============================================================================
//
// 切断後エフェクト表示 [SliceEffect.h]
// Author : さんみん
//
//=============================================================================
#ifndef _SLICEEFFECT_H_
#define _SLICEEFFECT_H_

#include "main.h"

struct SliceData
{
public:
	D3DXVECTOR3				pos;				// 位置
	D3DXVECTOR3				scl;				// スケール
	D3DXVECTOR3				rot;
	D3DXVECTOR3				move;				// 移動量
	D3DXVECTOR3				posVtx[10];			// 頂点座標
	D3DXVECTOR2				posUV[10];

	LPDIRECT3DTEXTURE9		D3DTexture = NULL;

	int						numVtx;
	int						numPolygon;

};

class SliceEffect
{
public:

	static SliceEffect*		root;
	static SliceEffect*		last;
	static int				cnt;

	SliceEffect*			next;
	SliceEffect*			prev;

	D3DXVECTOR3				pos;
	D3DXVECTOR3				scl;
	D3DXVECTOR3				rot;
	D3DXVECTOR3				move;
	
	LPDIRECT3DTEXTURE9		D3DTexture = NULL;
	LPDIRECT3DVERTEXBUFFER9 D3DVtxBuff = NULL;		// 頂点バッファインターフェースへのポインタ
	LPDIRECT3DINDEXBUFFER9	D3DIdxBuff = NULL;		// インデックスバッファインターフェースへのポインタ

	int						numVtx;
	int						numPolygon;
	int						time;

	bool					use;
	
	SliceEffect(SliceData initData);
	~SliceEffect();

	HRESULT MakeVertex(SliceData initData);
	void SliceEffect::AddList();

	void Update();
	void Draw();

};


#endif
