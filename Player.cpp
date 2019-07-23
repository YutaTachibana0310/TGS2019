//=====================================
//
//プレイヤー処理[Player.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "Player.h"

/**************************************
マクロ定義
***************************************/
#define PLAYER_SIZE				(100.0f)
#define PLAYER_ANIM_TIMING		(5)
#define PLAYER_ANIM_LOOPMAX		(10)
#define PLAYER_TEX_SIZE_X		(1.0f / PLAYER_ANIM_LOOPMAX)
#define PLAYER_TEX_SIZE_Y		(1.0f)

static const char* TextureName[PlayerTextureMax] = {
	"data/TEXTURE/PLAYER_ARUKI.png",
	"data/TEXTURE/PLAYER_RUN.png",
	"data/TEXTURE/PLAYER_DF.png",
	"data/TEXTURE/PLAYER_ATTACK.png",
};

/**************************************
コンストラクタ
***************************************/
Player::Player()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファ作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_BILLBOARD) * NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_BILLBOARD,
		D3DPOOL_MANAGED,
		&vtxBuff,
		0);

	//頂点バッファ初期化
	VERTEX_BILLBOARD *pVtx;
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].vtx = D3DXVECTOR3(-PLAYER_SIZE, PLAYER_SIZE, 0.0f);
	pVtx[1].vtx = D3DXVECTOR3( PLAYER_SIZE, PLAYER_SIZE, 0.0f);
	pVtx[2].vtx = D3DXVECTOR3(-PLAYER_SIZE, -PLAYER_SIZE, 0.0f);
	pVtx[3].vtx = D3DXVECTOR3( PLAYER_SIZE, -PLAYER_SIZE, 0.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx[0].diffuse =
		pVtx[1].diffuse =
		pVtx[2].diffuse =
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	vtxBuff->Unlock();

	//テクスチャ読み込み
	textures.resize(PlayerTextureMax);
	for (int i = 0; i < PlayerTextureMax; i++)
	{
		D3DXCreateTextureFromFile(pDevice, TextureName[i], &textures[i]);
	}

}

/**************************************
デストラクタ
***************************************/
Player::~Player()
{
	for (auto& texture : textures)
	{
		SAFE_RELEASE(texture);
	}
	textures.clear();

	SAFE_RELEASE(vtxBuff);
}

/**************************************
更新処理
***************************************/
void Player::Update()
{
	animCount++;
	if (animCount % PLAYER_ANIM_TIMING == 0)
	{
		animIndex = WrapAround(0, PLAYER_ANIM_LOOPMAX, animIndex + 1);

		VERTEX_BILLBOARD *pVtx;
		vtxBuff->Lock(0, 0, (void**)&pVtx, 0);
		pVtx[0].tex = D3DXVECTOR2(animIndex * PLAYER_TEX_SIZE_X, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((animIndex + 1) * PLAYER_TEX_SIZE_X, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(animIndex * PLAYER_TEX_SIZE_X, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((animIndex + 1) * PLAYER_TEX_SIZE_X, 1.0f);
		vtxBuff->Unlock();
	}
}

/**************************************
描画処理
***************************************/
void Player::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetFVF(FVF_VERTEX_BILLBOARD);
	pDevice->SetTexture(0, textures[textureIndex]);
	pDevice->SetStreamSource(0, vtxBuff, 0, sizeof(VERTEX_BILLBOARD));

	D3DXMATRIX mtxWorld;
	transform.CalcWorldMtx(&mtxWorld);

	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}