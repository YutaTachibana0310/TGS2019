//=============================================================================
//
// 切断処理 [Slice.cpp]
// Author : さんみん
//
//=============================================================================


#include "enemy.h"
#include "SliceEffect.h"
#include "Slice.h"

struct Surface
{
	D3DXVECTOR3 pos[4];
	D3DXVECTOR3 nor;
};

Surface		CalcSurface(D3DXVECTOR3 posE, D3DXVECTOR3 posA);
int			hitCheck(D3DXVECTOR3* cp, SliceData* p, D3DXVECTOR3 pos0, D3DXVECTOR3 pos1);
D3DXMATRIX	CalsWorldVtx(SliceData* data, Enemy* enemy);
void		CalsCrossPoint(SliceData* wk);
void		SplitData(SliceData* data, SliceData* up, SliceData* down, Surface surface);
void		SortData(SliceData* data, Surface surface);
void		CalsLocalVtx(SliceData* data, D3DXMATRIX mtxInv, Enemy* enemy, D3DXVECTOR3 move);

#include "GameParticleManager.h"

void SliceEnemy(Enemy* enemy, D3DXVECTOR3 posAtk)
{
	//D3DXMATRIX mtxInv;
	SliceData sliceData, upData, downData;

	//D3DXVECTOR3				pos;				// 位置
	//D3DXVECTOR3				scl;				// スケール
	//D3DXVECTOR3				rot;
	//D3DXVECTOR3				move;				// 移動量
	//D3DXVECTOR3				posVtx[64];			// 頂点座標
	//D3DXVECTOR2				posUV[64];

	//LPDIRECT3DTEXTURE9		D3DTexture = NULL;

	sliceData.pos = enemy->transform.pos;
	sliceData.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	sliceData.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	sliceData.D3DTexture = enemy->D3DTextureEnemy;
	sliceData.numPolygon = 2;
	sliceData.numVtx = 4;

	VERTEX_3D	*vtx;
	enemy->D3DVtxBuffEnemy->Lock(0, 0, (void**)&vtx, 0);
	for (int i = 0; i < 4; i++)
	{
		sliceData.posVtx[i] = vtx[i].vtx;
		sliceData.posUV[i] = vtx[i].tex;
	}
	// 頂点データをアンロックする
	enemy->D3DVtxBuffEnemy->Unlock();
	D3DXVECTOR3 tmp = sliceData.posVtx[2] - sliceData.posVtx[0];
	tmp /= 2.0f;
	float tex = sliceData.posUV[2].y - sliceData.posUV[0].y;
	tex /= 2.0f;

	upData = sliceData;
	downData = sliceData;

	upData.move = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	downData.move = D3DXVECTOR3(0.0f, -1.0f, 0.0f);


	upData.posVtx[2] -= tmp;
	upData.posUV[2].y -= tex;

	upData.posVtx[3] -= tmp;
	upData.posUV[3].y -= tex;


	downData.posVtx[0] += tmp;
	downData.posUV[0].y += tex;


	downData.posVtx[1] += tmp;
	downData.posUV[1].y += tex;



	// エフェクトをnew
	new SliceEffect(upData);
	new SliceEffect(downData);

	GameParticleManager::Instance()->SetBloodParticle(downData.posVtx[0] + enemy->transform.pos, downData.posVtx[1] + enemy->transform.pos);

	//// 切断面生成
	//Surface surface = CalcSurface(enemy->transform.pos, posAtk);

	//// ワールド変換
	//mtxInv = CalsWorldVtx(&sliceData, enemy);

	//sliceData.numVtx = 4;

	//// 交点計算, UV計算
	//CalsCrossPoint(&sliceData);

	//// 頂点分離
	//SplitData(&sliceData, &upData, &downData, surface);

	//// インデックスソート
	//SortData(&upData, surface);
	//SortData(&downData, surface);


	//// ローカル座標に戻す
	//CalsLocalVtx(&upData, mtxInv, enemy, surface.nor);
	//CalsLocalVtx(&downData, mtxInv, enemy, -surface.nor);



}

void CalsLocalVtx(SliceData* data, D3DXMATRIX mtxInv, Enemy* enemy, D3DXVECTOR3 move)
{
	for (int i = 0; i < data->numVtx; i++)
	{
		D3DXVec3TransformCoord(&data->posVtx[i], &data->posVtx[i], &mtxInv);
	}

	//LPDIRECT3DDEVICE9 device = GetDevice();

	//D3DXCreateTextureFromFile(device,							// デバイスへのポインタ
	//	FileName,			// ファイルの名前
	//	&wk.D3DTexture);	// 読み込むメモリー
	
	data->D3DTexture = enemy->D3DTextureEnemy;
	data->pos = enemy->transform.pos;
	data->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	data->rot = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	data->move = move;
	data->numPolygon = data->numVtx - 2;

}

void	SortData(SliceData* data, Surface surface)
{
	SliceData wk;
	D3DXVECTOR3 cpVec, wkVec;
	float dot[10];
	cpVec = data->posVtx[data->numVtx - 1] - data->posVtx[data->numVtx - 2];
	D3DXVec3Normalize(&cpVec, &cpVec);

	for (int i = 0; i < data->numVtx - 2; i++)
	{
		wkVec = data->posVtx[i] - data->posVtx[data->numVtx - 2];
		D3DXVec3Normalize(&wkVec, &wkVec);

		dot[i] = D3DXVec3Dot(&wkVec, &cpVec);
	}

	wk = *data;
	D3DXVECTOR3				wkVtx;			// 頂点座標
	D3DXVECTOR2				wkUV;
	float					wkDot;

	wkVtx = data->posVtx[0];
	wkUV = data->posUV[0];
	wkDot = dot[0];

	data->posVtx[0] = data->posVtx[data->numVtx - 2];
	data->posUV[0] = data->posUV[data->numVtx - 2];
	//dot[0] = dot[j];

	data->posVtx[data->numVtx - 2] = wkVtx;
	data->posUV[data->numVtx - 2] = wkUV;
	dot[data->numVtx - 2] = wkDot;

	wkVtx = data->posVtx[1];
	wkUV = data->posUV[1];
	wkDot = dot[1];

	data->posVtx[1] = data->posVtx[data->numVtx - 1];
	data->posUV[1] = data->posUV[data->numVtx - 1];
	//dot[1] = dot[j];

	data->posVtx[data->numVtx - 1] = wkVtx;
	data->posUV[data->numVtx - 1] = wkUV;
	dot[data->numVtx - 1] = wkDot;



	for (int i = 2; i < data->numVtx - 1; i++)
	{
		for (int j = 3; j < data->numVtx; j++)
		{
			if (dot[i] > dot[j])
			{
				wkVtx = data->posVtx[i];
				wkUV = data->posUV[i];
				wkDot = dot[i];

				data->posVtx[i] = data->posVtx[j];
				data->posUV[i] = data->posUV[j];
				dot[i] = dot[j];

				data->posVtx[j] = wkVtx;
				data->posUV[j] = wkUV;
				dot[j] = wkDot;


			}
		}
	}

}

void	SplitData(SliceData* data, SliceData* up, SliceData* down, Surface surface)
{
	int upNumV = 0;
	int doNumV = 0;

	D3DXVECTOR3 vec;
	float dot;

	for (int i = 0; i < data->numVtx; i++)
	{
		vec = data->posVtx[i] - surface.pos[0];

		dot = D3DXVec3Dot(&surface.nor, &vec);

		if (dot < 0)
		{
			up->posVtx[upNumV] = data->posVtx[i];
			upNumV++;
		}
		else if (dot > 0)
		{
			down->posVtx[doNumV] = data->posVtx[i];
			doNumV++;

		}
		else
		{
			up->posVtx[upNumV] = data->posVtx[i];
			upNumV++;
			down->posVtx[doNumV] = data->posVtx[i];
			doNumV++;

		}
	}

	up->numVtx = upNumV;
	down->numVtx = doNumV;

}



void	CalsCrossPoint(SliceData* wk)
{
	D3DXVECTOR3 cp;
	int sp, ep;
	for (int i = 0; i < 4; i++)
	{
		switch (i)
		{
		case 0:
			sp = 0;
			ep = 1;
			break;
		case 1:
			sp = 1;
			ep = 3;
			break;
		case 2:
			sp = 3;
			ep = 2;
			break;
		case 3:
			sp = 2;
			ep = 0;
			break;
		default:
			break;
		}

		if (hitCheck(&cp, wk, wk->posVtx[sp], wk->posVtx[ep]))
		{
			wk->posVtx[wk->numVtx] = cp;

			float length = wk->posVtx[1].x - wk->posVtx[0].x;

			length = cp.x - wk->posVtx[0].x / length;

			wk->posUV[wk->numVtx].x = (wk->posUV[1].x - wk->posUV[0].x) * length;


			length = wk->posVtx[2].y - wk->posVtx[0].y;

			length = cp.y - wk->posVtx[0].y / length;

			wk->posUV[wk->numVtx].y = (wk->posUV[2].y - wk->posUV[0].y) * length;




			wk->numVtx++;
		}
	}


}


//=============================================================================
// ポリゴンと線分との当たり判定
// cp	:交点の座標を収納する変数のポインター
// p	:当たり判定を行う４頂点
// pos0	:始点（移動前）
// pos1	:終点（移動後）
//=============================================================================
int hitCheck(D3DXVECTOR3* cp, SliceData* p, D3DXVECTOR3 pos0, D3DXVECTOR3 pos1)
{
	D3DXVECTOR3		nor;		// ポリゴンの法線

	{	// ポリゴンの外積をとって法線を求める。そして正規化しておく。
		D3DXVECTOR3		vec01;
		D3DXVECTOR3		vec02;

		vec01 = p->posVtx[1] - p->posVtx[0];
		vec02 = p->posVtx[2] - p->posVtx[0];

		//vec01 = p1 - p0;
		//vec02 = p2 - p0;

		D3DXVec3Cross(&nor, &vec01, &vec02);

		D3DXVec3Normalize(&nor, &nor);
	}

	{	// 平面と線分の内積とって衝突している可能性を調べる
		// 求めた法線とベクトル２つ（線分の両端とポリゴン上の任意の点）の内積とって衝突している可能性を調べる
		D3DXVECTOR3		vec1;
		D3DXVECTOR3		vec2;
		float a;
		float b;

		vec1 = pos0 - p->posVtx[0];
		vec2 = pos1 - p->posVtx[0];

		a = D3DXVec3Dot(&vec1, &nor);
		b = D3DXVec3Dot(&vec2, &nor);


		if ((a * b) > 0)
		{
			// 当たっている可能性は無い
			return(0);
		}
	}


	{	// ポリゴンと線分の交点を求める
		D3DXVECTOR3		vec1 = pos0 - p->posVtx[0];
		D3DXVECTOR3		vec2 = pos1 - p->posVtx[0];
		float			d1 = fabsf(D3DXVec3Dot(&nor, &vec1));					// 内分比を求める為の点とポリゴンとの距離
		float			d2 = fabsf(D3DXVec3Dot(&nor, &vec2));					// 内分比を求める為の点とポリゴンとの距離
		float			a = d1 / (d1 + d2);					// 内分比
		D3DXVECTOR3		vec3 = (1 - a) * vec1 + a * vec2;
		D3DXVECTOR3		p3 = p->posVtx[0] + vec3;					// 交点




		{	// 求めた交点がポリゴンの中にあるか調べる

			// ポリゴンの各辺のベクトル
			D3DXVECTOR3		v1 = p->posVtx[1] - p->posVtx[0];
			D3DXVECTOR3		v2 = p->posVtx[3] - p->posVtx[1];
			D3DXVECTOR3		v3 = p->posVtx[0] - p->posVtx[3];

			// 各頂点と交点とのベクトル
			D3DXVECTOR3		v4 = p3 - p->posVtx[0];
			D3DXVECTOR3		v5 = p3 - p->posVtx[1];
			D3DXVECTOR3		v6 = p3 - p->posVtx[3];

			// 各辺との外積で法線を求める
			D3DXVECTOR3		n1, n2, n3;

			D3DXVec3Cross(&n1, &v1, &v4);
			D3DXVec3Cross(&n2, &v2, &v5);
			D3DXVec3Cross(&n3, &v3, &v6);

			// それぞれのベクトルの向きを内積でチェック


			if (D3DXVec3Dot(&n1, &n3) < 0 || D3DXVec3Dot(&n2, &n3) < 0)
			{
				// ポリゴンの各辺のベクトル
				v1 = p->posVtx[3] - p->posVtx[0];
				v2 = p->posVtx[2] - p->posVtx[3];
				v3 = p->posVtx[0] - p->posVtx[2];

				// 各頂点と交点とのベクトル
				v4 = p3 - p->posVtx[0];
				v5 = p3 - p->posVtx[3];
				v6 = p3 - p->posVtx[2];

				D3DXVec3Cross(&n1, &v1, &v4);
				D3DXVec3Cross(&n2, &v2, &v5);
				D3DXVec3Cross(&n3, &v3, &v6);

				if (D3DXVec3Dot(&n1, &n3) < 0 || D3DXVec3Dot(&n2, &n3) < 0)
				{
					return (0);
				}
			}

			*cp = p3;
		}
	}

	return(1);
}

D3DXMATRIX CalsWorldVtx(SliceData* data, Enemy* enemy)
{
	D3DXMATRIX mtxView, mtxScale, mtxTranslate, mtxWorld, mtxinv;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorld);

	// スケールを反映
	D3DXMatrixScaling(&mtxScale, enemy->transform.scale.x, enemy->transform.scale.y, enemy->transform.scale.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScale);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, enemy->transform.pos.x, enemy->transform.pos.y, enemy->transform.pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

	D3DXMatrixInverse(&mtxinv, NULL, &mtxWorld);

	VERTEX_3D	*vtx;
	enemy->D3DVtxBuffEnemy->Lock(0, 0, (void**)&vtx, 0);
	for (int i = 0; i < 4; i++)
	{
		D3DXVec3TransformCoord(&data->posVtx[i], &vtx[i].vtx, &mtxWorld);
		data->posUV[i] = vtx[i].tex;
	}
	// 頂点データをアンロックする
	enemy->D3DVtxBuffEnemy->Unlock();

	return mtxinv;
}


Surface CalcSurface(D3DXVECTOR3 posE, D3DXVECTOR3 posA)
{
	Surface wk;

	D3DXVECTOR3 vec = posE - posA;
	vec *= 2.0f;

	wk.pos[0] = posA - vec;
	wk.pos[1] = posA - vec;
	wk.pos[2] = posE + vec;
	wk.pos[3] = posE + vec;

	wk.pos[0].z -= 50.0f;
	wk.pos[1].z += 50.0f;
	wk.pos[2].z -= 50.0f;
	wk.pos[3].z += 50.0f;

	D3DXVECTOR3 vec01, vec02;

	vec01 = wk.pos[1] - wk.pos[0];
	vec02 = wk.pos[2] - wk.pos[0];

	D3DXVec3Cross(&wk.nor, &vec01, &vec02);

	D3DXVec3Normalize(&wk.nor, &wk.nor);

	return wk;
}