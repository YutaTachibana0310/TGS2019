//=====================================
//
//スパイクノイズ処理[SpikeNoise.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "SpikeNoise.h"

/**************************************
マクロ定義
***************************************/
#define EFFECTFILE_SPIKENOISE_PATH		"PostEffect/SpikeNoise.fx"
#define PRECOMPILE_SPIKENOISE_PATH		"data/EFFECT/SpikeNoise.cfx"

/**************************************
構造体定義
***************************************/

/**************************************
グローバル変数
***************************************/

/**************************************
コンストラクタ
***************************************/
SpikeNoise::SpikeNoise()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	HRESULT res = D3DXCreateEffectFromFile(pDevice, (LPSTR)PRECOMPILE_SPIKENOISE_PATH, 0, 0, D3DXSHADER_SKIPVALIDATION, 0, &effect, 0);

	if(res != S_OK)
		D3DXCreateEffectFromFile(pDevice, (LPSTR)EFFECTFILE_SPIKENOISE_PATH, 0, 0, 0, 0, &effect, 0);

	hndlLength = effect->GetParameterByName(0, "length");
}

/**************************************
デストラクタ
***************************************/
SpikeNoise::~SpikeNoise()
{
	SAFE_RELEASE(effect);
}

/**************************************
描画処理
***************************************/
void SpikeNoise::DrawEffect()
{
	effect->Begin(0, 0);
	effect->BeginPass(0);

	ScreenObject::Draw();

	effect->EndPass();
	effect->End();
}

/**************************************
歪み長さセット処理
***************************************/
void SpikeNoise::SetLength(float length)
{
	effect->SetFloat(hndlLength, length);
	effect->CommitChanges();
}