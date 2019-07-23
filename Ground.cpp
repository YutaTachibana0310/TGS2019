//=====================================
//
//グラウンド処理[Ground.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "Ground.h"

/**************************************
マクロ定義
***************************************/
#define GROUND_SIZE_X		(40000.0f)
#define GROUND_SIZE_Y		(100.0f)

/**************************************
コンストラクタ
***************************************/
Ground::Ground()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->CreateVertexBuffer(sizeof(VERTEX_BILLBOARD) * NUM_POLYGON,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_BILLBOARD,
		D3DPOOL_MANAGED,
		&vtxBuff,
		0);

	VERTEX_BILLBOARD *pVtx;
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].vtx = D3DXVECTOR3(-GROUND_SIZE_X, GROUND_SIZE_Y, 0.0f);
	pVtx[1].vtx = D3DXVECTOR3( GROUND_SIZE_X, GROUND_SIZE_Y, 0.0f);
	pVtx[2].vtx = D3DXVECTOR3(-GROUND_SIZE_X, -GROUND_SIZE_Y, 0.0f);
	pVtx[3].vtx = D3DXVECTOR3( GROUND_SIZE_X, -GROUND_SIZE_Y, 0.0f);
	
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx[0].diffuse =
		pVtx[1].diffuse =
		pVtx[2].diffuse =
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	vtxBuff->Unlock();

	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/ground.cpp", &texture);

	transform.pos.y = -GROUND_SIZE_Y / 2.0f;
}

/**************************************
デストラクタ
***************************************/
Ground::~Ground()
{
	SAFE_RELEASE(vtxBuff);
	SAFE_RELEASE(texture);
}

/**************************************
描画処理
***************************************/
void Ground::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxWorld;
	transform.CalcWorldMtx(&mtxWorld);
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
	pDevice->SetFVF(FVF_VERTEX_BILLBOARD);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}