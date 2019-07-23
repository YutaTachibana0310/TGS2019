//=============================================================================
//
// エネミー処理 [enemy.cpp]
// Author : GP11A341_22_田中太陽
//
//=============================================================================
#include "main.h"
#include "enemy.h"
#include "camera.h"
#include "Framework/ResourceManager.h"
#include "input.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define ENEMY_INIT_POS_X		(0.0f)	// エネミーの初期位置
#define ENEMY_INIT_POS_Y		(0.0f)	// 
#define ENEMY_SIZE_X			(100)	// エネミーの幅
#define ENEMY_SIZE_Y			(100)	// エネミーの高さ

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
Enemy::Enemy()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャの設定
	D3DTextureEnemy[ENEMYTYPE_MIN] = NULL;
	ResourceManager::Instance()->GetTexture("enemy01", &D3DTextureEnemy[ENEMYTYPE_01]);
	ResourceManager::Instance()->GetTexture("enemy02", &D3DTextureEnemy[ENEMYTYPE_02]);
	ResourceManager::Instance()->GetTexture("enemy03", &D3DTextureEnemy[ENEMYTYPE_03]);

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		transform[i].pos = D3DXVECTOR3(ENEMY_INIT_POS_X, ENEMY_INIT_POS_Y, 0.0f);	// 位置を初期化
		transform[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		transform[i].scale= D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		use[i] = false;
		texNum[i] = ENEMYTYPE_01;
		D3DVtxBuffEnemy[i] = NULL;
	
		// 頂点情報の作成
		MakeVertexEnemy(i, pDevice);
	}
}

//=============================================================================
// デスストラクタ
//=============================================================================
Enemy::~Enemy()
{

}

//=============================================================================
// 更新処理
//=============================================================================
void Enemy::UpdateEnemy(void)
{
	if (GetKeyboardTrigger(DIK_A))
	{
		SetEnemy(1, transform->pos + D3DXVECTOR3(50.0f, 0.0f, 0.0f));
	}

	if (GetKeyboardPress(DIK_LEFT))
	{
		transform[0].pos.x -= 1.0f;
	}

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (use[i])
		{
			SetVertexEnemy(i);
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void Enemy :: DrawEnemy()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView, mtxScale, mtxTranslate;

	// ラインティングを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if(use[i])
		{
			// ビューマトリックスを取得
			mtxView = GetMtxView();

			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&mtxWorld);

			// ポリゴンを正面に向ける
			//mtxWorld._11 = mtxView._11;
			//mtxWorld._12 = mtxView._21;
			//mtxWorld._13 = mtxView._31;
			//mtxWorld._21 = mtxView._12;
			//mtxWorld._22 = mtxView._22;
			//mtxWorld._23 = mtxView._32;
			//mtxWorld._31 = mtxView._13;
			//mtxWorld._32 = mtxView._23;
			//mtxWorld._33 = mtxView._33;

			// スケールを反映
			D3DXMatrixScaling(&mtxScale, transform[i].scale.x, transform[i].scale.y, transform[i].scale.z);
			D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScale);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, transform[i].pos.x, transform[i].pos.y, transform[i].pos.z);
			D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

			// 頂点バッファをデバイスのデータストリームにバインド
			pDevice->SetStreamSource(0, D3DVtxBuffEnemy[i], 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, D3DTextureEnemy[texNum[i]]);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (i * NUM_VERTEX), NUM_POLYGON);
		}
	}
}

//===============================================================================
// 頂点情報の作成
//===============================================================================
HRESULT Enemy::MakeVertexEnemy(int eno, LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_3D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&D3DVtxBuffEnemy[eno],			// 頂点バッファインターフェースへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		D3DVtxBuffEnemy[eno]->Lock(0, 0, (void**)&vtx, 0);
		{
			// 頂点座標の設定
			vtx[0].vtx = D3DXVECTOR3(-ENEMY_SIZE_X, ENEMY_SIZE_Y, 0.0f);
			vtx[1].vtx = D3DXVECTOR3(ENEMY_SIZE_X, ENEMY_SIZE_Y, 0.0f);
			vtx[2].vtx = D3DXVECTOR3(-ENEMY_SIZE_X, -ENEMY_SIZE_Y, 0.0f);
			vtx[3].vtx = D3DXVECTOR3(ENEMY_SIZE_X, -ENEMY_SIZE_Y, 0.0f);

			// 法線の設定
			vtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			vtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			vtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			vtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

			// 反射光の設定
			vtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			vtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			vtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			vtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// テクスチャ座標の設定
			vtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
			vtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
			vtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
			vtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
		}

		// 頂点データをアンロックする
		D3DVtxBuffEnemy[eno]->Unlock();
	}

	return S_OK;
}

//=================================================================================
// 頂点座標の設定
//=================================================================================
void Enemy::SetVertexEnemy(int index)
{
	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	D3DVtxBuffEnemy[index]->Lock(0, 0, (void**)&vtx, 0);

	// 頂点座標の設定
	vtx[0].vtx = D3DXVECTOR3(-ENEMY_SIZE_X, ENEMY_SIZE_Y, 0.0f);
	vtx[1].vtx = D3DXVECTOR3(ENEMY_SIZE_X, ENEMY_SIZE_Y, 0.0f);
	vtx[2].vtx = D3DXVECTOR3(-ENEMY_SIZE_X, -ENEMY_SIZE_Y, 0.0f);
	vtx[3].vtx = D3DXVECTOR3(ENEMY_SIZE_X, -ENEMY_SIZE_Y, 0.0f);

	// 頂点データをアンロックする
	D3DVtxBuffEnemy[index]->Unlock();
}


//===============================================================================
// エネミーの設置
//===============================================================================
void Enemy::SetEnemy(int type, D3DXVECTOR3 setPos)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (!use[i])
		{
			use[i] = true;
			transform[i].pos = setPos;
			texNum[i] = type;
			SetVertexEnemy(i);

			return;
		}
	}
}
