//=============================================================================
//
// 切断後エフェクト表示 [SliceEffect.cpp]
// Author : さんみん
//
//=============================================================================

#include "camera.h"
#include "sliceEffect.h"



SliceEffect*	SliceEffect::root = NULL;
SliceEffect*	SliceEffect::last = NULL;
int				SliceEffect::cnt = NULL;


SliceEffect::SliceEffect(SliceData initData)
{

	pos = initData.pos;
	scl = initData.scl;
	rot = initData.rot;
	move = initData.move;

	D3DTexture = initData.D3DTexture;
	
	numVtx = initData.numVtx;
	numPolygon = initData.numPolygon;

	time = 0;

	use = true;

	MakeVertex(initData);
	
	AddList();
	
}

// リスト登録
void SliceEffect::AddList()
{
	if (root == NULL)
	{
		root = this;
		last = this;
		prev = NULL;
	}
	else
	{
		last->next = this;
		prev = last;
		last = this;
	}

	next = NULL;

	cnt++;
}


SliceEffect::~SliceEffect()
{
	//リスト削除
	if (this == root && last == this)
	{
		root = NULL;
		last = NULL;
	}
	else if (this == root)
	{
		root = next;
		next->prev = NULL;
	}
	else if (this == last)
	{
		last = prev;
		prev->next = NULL;
	}
	else
	{
		prev->next = next;
		next->prev = prev;
	}

	cnt--;

	if (D3DTexture != NULL)
	{// テクスチャの開放
		D3DTexture = NULL;
	}

	if (D3DVtxBuff != NULL)
	{// 頂点バッファの開放
		D3DVtxBuff->Release();
		D3DVtxBuff = NULL;
	}

	if (D3DIdxBuff)
	{// インデックスバッファの開放
		D3DIdxBuff->Release();
		D3DIdxBuff = NULL;
	}

}

void SliceEffect::Update()
{
	pos += move;
	time++;

	if (time > 100)
	{
		delete this;// .use = false;
	}

}

void SliceEffect::Draw()
{
	LPDIRECT3DDEVICE9 device = GetDevice();
	D3DXMATRIX mtxView, mtxScale, mtxTranslate, mtxWorld, mtxRotation, mtxViewInv;
	D3DXMATRIX a, b, c;
	   
	// ラインティングを無効にする
	device->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorld);

	// ビューマトリックスを取得
	mtxView = GetMtxView();

	// 逆行列をもとめる
	D3DXMatrixInverse(&mtxWorld, NULL, &mtxView);
	mtxWorld._41 = 0.0f;
	mtxWorld._42 = 0.0f;
	mtxWorld._43 = 0.0f;
	   
	// スケールを反映
	D3DXMatrixScaling(&mtxScale, scl.x, scl.y, scl.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScale);

	// 回転を反映
	//D3DXMatrixRotationYawPitchRoll(&mtxRotation, rot.y, rot.x, rot.z);
	//D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRotation);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, pos.x,	pos.y, pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

	// ワールドマトリックスの設定
	device->SetTransform(D3DTS_WORLD, &mtxWorld);

	// 頂点バッファをデバイスのデータストリームにバインド
	device->SetStreamSource(0, D3DVtxBuff, 0, sizeof(VERTEX_3D));

	// インデックスバッファをレンダリングパイプラインに設定
	device->SetIndices(D3DIdxBuff);

	// 頂点フォーマットの設定
	device->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	device->SetTexture(0, D3DTexture);

	// ポリゴンの描画
	device->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, numVtx, 0, numPolygon);

	// ラインティングを有効にする
	device->SetRenderState(D3DRS_LIGHTING, TRUE);

}


//=============================================================================
// 頂点情報の作成
//=============================================================================
HRESULT SliceEffect::MakeVertex(SliceData initData)
{
	LPDIRECT3DDEVICE9 device = GetDevice();


	D3DTexture = initData.D3DTexture;

	// オブジェクトの頂点バッファを生成
	if (FAILED(device->CreateVertexBuffer(sizeof(VERTEX_3D) * numVtx,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,						// 頂点バッファの使用法　
		FVF_VERTEX_3D,							// 使用する頂点フォーマット
		D3DPOOL_MANAGED,						// リソースのバッファを保持するメモリクラスを指定
		&D3DVtxBuff,						// 頂点バッファインターフェースへのポインタ
		NULL)))									// NULLに設定
	{
		return E_FAIL;
	}

	// オブジェクトのインデックスバッファを生成
	if (FAILED(device->CreateIndexBuffer(sizeof(WORD) * numVtx,			// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,					// 頂点バッファの使用法　
		D3DFMT_INDEX16,						// 使用するインデックスフォーマット
		D3DPOOL_MANAGED,					// リソースのバッファを保持するメモリクラスを指定
		&D3DIdxBuff,					// インデックスバッファインターフェースへのポインタ
		NULL)))								// NULLに設定
	{
		return E_FAIL;
	}


	{//頂点バッファの中身を埋める
		VERTEX_3D	*vtx;
		WORD		*idx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		D3DVtxBuff->Lock(0, 0, (void**)&vtx, 0);
		D3DIdxBuff->Lock(0, 0, (void**)&idx, 0);

		for (int i = 0; i < numVtx; i++)
		{
			// 頂点座標の設定
			vtx[i].vtx = initData.posVtx[i];
			// 反射光の設定
			vtx[i].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			// テクスチャ座標の設定
			vtx[i].tex = initData.posUV[i];

			idx[i] = i;
		}

		// 頂点データをアンロックする
		D3DVtxBuff->Unlock();
		D3DIdxBuff->Unlock();

	}

	return S_OK;
}
