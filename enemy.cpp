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
#define ENEMY_INIT_POS_X		(200.0f)	// エネミーの初期位置
#define ENEMY_INIT_POS_Y		(0.0f)	// 
#define ENEMY_SIZE_X			(100)	// エネミーの幅
#define ENEMY_SIZE_Y			(100)	// エネミーの高さ
#define ENEMY_MOVE_TIME			(180)	// エネミーの動くフレーム数

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
	//ResourceManager::Instance()->GetTexture("enemy01", &D3DTextureEnemy);
	//ResourceManager::Instance()->GetTexture("enemy02", &D3DTextureEnemy[ENEMYTYPE_02]);
	//ResourceManager::Instance()->GetTexture("enemy03", &D3DTextureEnemy[ENEMYTYPE_03]);
	
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
		fileName[ENEMYTYPE_01],					// ファイルの名前
		&D3DTextureEnemy);			// 読み込むメモリー

	collider = new BoxCollider3D(BoxCollider3DTag::Enemy, &transform.pos);
	collider->active = true;

	transform.pos = D3DXVECTOR3(ENEMY_INIT_POS_X, ENEMY_INIT_POS_Y, 0.0f);	// 位置を初期化
	transform.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	transform.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	use = true;
	cntFrame = 0;
	texNum = ENEMYTYPE_01;
	D3DVtxBuffEnemy = NULL;

	// 頂点情報の作成
	MakeVertexEnemy(pDevice);
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

	if (use)
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
		D3DXMatrixScaling(&mtxScale, transform.scale.x, transform.scale.y, transform.scale.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScale);

		// 移動を反映
		D3DXMatrixTranslation(&mtxTranslate, transform.pos.x, transform.pos.y, transform.pos.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

		// 頂点バッファをデバイスのデータストリームにバインド
		pDevice->SetStreamSource(0, D3DVtxBuffEnemy, 0, sizeof(VERTEX_3D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		// テクスチャの設定
		pDevice->SetTexture(0, D3DTextureEnemy);

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	}
}


//===============================================================================
// 頂点情報の作成
//===============================================================================
HRESULT Enemy::MakeVertexEnemy(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_3D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&D3DVtxBuffEnemy,			// 頂点バッファインターフェースへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		D3DVtxBuffEnemy->Lock(0, 0, (void**)&vtx, 0);
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
		D3DVtxBuffEnemy->Unlock();
	}

	return S_OK;
}

//=================================================================================
// 頂点座標の設定
//=================================================================================
void Enemy::SetVertexEnemy()
{
	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	D3DVtxBuffEnemy->Lock(0, 0, (void**)&vtx, 0);

	// 頂点座標の設定
	vtx[0].vtx = D3DXVECTOR3(-ENEMY_SIZE_X, ENEMY_SIZE_Y, 0.0f);
	vtx[1].vtx = D3DXVECTOR3(ENEMY_SIZE_X, ENEMY_SIZE_Y, 0.0f);
	vtx[2].vtx = D3DXVECTOR3(-ENEMY_SIZE_X, -ENEMY_SIZE_Y, 0.0f);
	vtx[3].vtx = D3DXVECTOR3(ENEMY_SIZE_X, -ENEMY_SIZE_Y, 0.0f);

	// 頂点データをアンロックする
	D3DVtxBuffEnemy->Unlock();
}


//===============================================================================
// エネミーの設置
//===============================================================================
void Enemy::SetEnemy(int type, D3DXVECTOR3 setPos)
{
 	if (!use)
	{
		use = true;
		transform.pos = setPos;
		texNum = type;
		cntFrame = 0;
		SetVertexEnemy();

		return;
	}
}

//===============================================================================
// エネミータイプ別の動作
//===============================================================================
void Enemy::MoveTypeEnemy(int type)
{
	switch (type)
	{
	case ENEMYTYPE_01:
			
		//MoveEnemy();

		break;
	case ENEMYTYPE_02:
		break;
	case ENEMYTYPE_03:
		break;
	}
}

//===============================================================================
// エネミーの動作
//===============================================================================
void Enemy::MoveEnemy(D3DXVECTOR3 pos)
{
	D3DXVECTOR3 vec;
	float len;

	vec = pos - transform.pos;
	D3DXVec3Normalize(&vec, &vec);

	transform.pos += vec * 1.5f;

	//if (cntFrame < ENEMY_MOVE_TIME)
	//{
	//	transform.pos.x += 2.0f;
	//}
	//else if (cntFrame < (ENEMY_MOVE_TIME * 2))
	//{
	//	transform.pos.x -= 2.0f;
	//}
	//else
	//{
	//	cntFrame = 0;
	//}
}
