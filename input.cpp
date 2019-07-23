//=============================================================================
//
// 入力処理 [input.cpp]
// Author : 
//
//=============================================================================
#include "input.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECTINPUT8			g_pDInput = NULL;					// IDirectInput8インターフェースへのポインタ

//=============================================================================
// 入力処理の初期化
//=============================================================================
HRESULT InitInput(HINSTANCE hInst, HWND hWnd)
{
	HRESULT hr;

	if(!g_pDInput)
	{
		// DirectInputオブジェクトの作成
		hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION,
									IID_IDirectInput8, (void**)&g_pDInput, NULL);
	}

	// キーボードの初期化
	InitKeyboard(hInst, hWnd, g_pDInput);

	//マウス初期化
	InitializeMouse(hInst, hWnd, g_pDInput);

	//パッド初期化処理
	InitializePad(g_pDInput);

	return S_OK;
}

//=============================================================================
// 入力処理の終了処理
//=============================================================================
void UninitInput(void)
{
	// キーボードの終了処理
	UninitKeyboard();

	//マウス終了処理
	UninitMouse();

	//パッド終了処理
	UninitPad();

	if(g_pDInput)
	{// DirectInputオブジェクトの開放
		g_pDInput->Release();
		g_pDInput = NULL;
	}
}

//=============================================================================
// 入力処理の更新処理
//=============================================================================
void UpdateInput(void)
{
	// キーボードの更新
	UpdateKeyboard();

	//マウス更新処理
	UpdateMouse();

	//ゲームパッド更新処理
	UpdatePad();
}

//=============================================================================
// 水平方向の入力
//=============================================================================
float GetHorizontalInput()
{
	//キーボード優先
	if (GetKeyboardPress(DIK_LEFT))
		return -1.0f;
	else if (GetKeyboardPress(DIK_RIGHT))
		return 1.0f;

	//ゲームパッド
	if (IsButtonPressed(0, BUTTON_LEFT))
		return -1.0f;
	else if (IsButtonPressed(0, BUTTON_RIGHT))
		return 1.0f;

	return 0.0f;

}

//=============================================================================
// 垂直方向の入力
//=============================================================================
float GetVerticalInput()
{
	//キーボード優先
	if (GetKeyboardPress(DIK_DOWN))
		return -1.0f;
	else if (GetKeyboardPress(DIK_UP))
		return 1.0f;

	//ゲームパッド
	if (IsButtonPressed(0, BUTTON_DOWN))
		return -1.0f;
	else if (IsButtonPressed(0, BUTTON_UP))
		return 1.0f;

	return 0.0f;
}