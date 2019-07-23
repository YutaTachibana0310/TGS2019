
//=============================================================================
//�쐬�ҁ@GP11A341_34_���c����
// HP�\�����邾���̏��� [Result.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "Result.h"
#include "input.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexResult(void);
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTextureResult = NULL;				// �e�N�X�`���ւ̃|�C���^
VERTEX_2D				vertexWkResult[NUM_VERTEX];				// ���_���i�[���[�N
RESULT					titleWk[TITLEPLAYER_MAX];			// �v���C���[�\����
LPDIRECT3DTEXTURE9		D3DTextureStart = NULL;		// �e�N�X�`���ւ̃|�C���^

bool					titlefg = true;
int						cunt = 0;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitResult(int type)
{
	RESULT *title = &titleWk[0];

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int i = 0; i < TITLEPLAYER_MAX; i++, title++)
	{
		title->use = true;											// �g�p
		title->pos = D3DXVECTOR3(i*200.0f + 200.0f, 330.0f, 0.0f);	// ���W�f�[�^��������
		title->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// ��]�f�[�^��������
		title->col = D3DXCOLOR(0.0, 0.0, 0.0, 0.5);				// �F
		title->PatternAnim = 0;
		title->PatternAnim = rand() % ANIM_PATTERN_NUM;				// �A�j���p�^�[���ԍ��������_���ŏ�����


																	// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,							// �f�o�C�X�ւ̃|�C���^
			TEXTURE_STAGE1_TITLE,									// �t�@�C���̖��O
			&D3DTextureResult);											// �ǂݍ��ރ������[
		D3DXCreateTextureFromFile(pDevice,							// �f�o�C�X�ւ̃|�C���^
			TEXTURE_STAGE2_TITLE,									// �t�@�C���̖��O
			&D3DTextureStart);											// �ǂݍ��ރ������[

		MakeVertexResult();
	}
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitResult(void)
{
	if (D3DTextureResult != NULL)
	{// �e�N�X�`���̊J��
		D3DTextureResult->Release();
		D3DTextureResult = NULL;
	}

	if (D3DTextureStart != NULL)
	{// �e�N�X�`���̊J��
		D3DTextureStart->Release();
		D3DTextureStart = NULL;
	}


}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateResult(void)
{
	cunt++;

	// �_�ŏ���
	if (cunt > 50)
	{
		titlefg = !titlefg;
		cunt = 0;
	}

	MakeVertexResult();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawResult(void)
{
	RESULT *title = &titleWk[0];

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, D3DTextureResult);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWkResult, sizeof(VERTEX_2D));

	if (titlefg == true)
	{

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, D3DTextureStart);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	}


}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexResult(void)
{

	// ���_���W�̐ݒ�
	vertexWkResult[0].vtx = D3DXVECTOR3(STAGE1_TITLE_POS_X, STAGE1_TITLE_POS_Y, 0.0f);
	vertexWkResult[1].vtx = D3DXVECTOR3(STAGE1_TITLE_POS_X + STAGE1_TITLE_SIZE_X, STAGE1_TITLE_POS_Y, 0.0f);
	vertexWkResult[2].vtx = D3DXVECTOR3(STAGE1_TITLE_POS_X, STAGE1_TITLE_POS_Y + STAGE1_TITLE_SIZE_Y, 0.0f);
	vertexWkResult[3].vtx = D3DXVECTOR3(STAGE1_TITLE_POS_X + STAGE1_TITLE_SIZE_X, STAGE1_TITLE_POS_Y + STAGE1_TITLE_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	vertexWkResult[0].rhw =
	vertexWkResult[1].rhw =
	vertexWkResult[2].rhw =
	vertexWkResult[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	vertexWkResult[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkResult[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkResult[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkResult[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);


	// �e�N�X�`�����W�̐ݒ�
	vertexWkResult[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWkResult[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertexWkResult[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWkResult[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	return S_OK;
}
//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureResultPlayer(int no, int cntPattern)
{
	RESULT *title = &titleWk[no];

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y;

	title->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	title->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	title->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	title->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexResultPlaier(int no)
{
	RESULT *title = &titleWk[no];

	// ���_���W�̐ݒ�

	title->vertexWk[0].vtx.x = title->pos.x - cosf(title->BaseAngle + title->rot.z) * title->Radius;
	title->vertexWk[0].vtx.y = title->pos.y - sinf(title->BaseAngle + title->rot.z) * title->Radius;
	title->vertexWk[0].vtx.z = 0.0f;

	title->vertexWk[1].vtx.x = title->pos.x + cosf(title->BaseAngle - title->rot.z) * title->Radius;
	title->vertexWk[1].vtx.y = title->pos.y - sinf(title->BaseAngle - title->rot.z) * title->Radius;
	title->vertexWk[1].vtx.z = 0.0f;

	title->vertexWk[2].vtx.x = title->pos.x - cosf(title->BaseAngle - title->rot.z) * title->Radius;
	title->vertexWk[2].vtx.y = title->pos.y + sinf(title->BaseAngle - title->rot.z) * title->Radius;
	title->vertexWk[2].vtx.z = 0.0f;

	title->vertexWk[3].vtx.x = title->pos.x + cosf(title->BaseAngle + title->rot.z) * title->Radius;
	title->vertexWk[3].vtx.y = title->pos.y + sinf(title->BaseAngle + title->rot.z) * title->Radius;
	title->vertexWk[3].vtx.z = 0.0f;
}