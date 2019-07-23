
//=============================================================================
//�쐬�ҁ@GP11A341_34_���c����
// HP�\�����邾���̏��� [Ui.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "Hitpoint.h"
#include "input.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexUi(void);
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTextureUi = NULL;				// �e�N�X�`���ւ̃|�C���^
VERTEX_2D				vertexWkUi[NUM_VERTEX];				// ���_���i�[���[�N
TITLEPLAYER				titleWk[TITLEPLAYER_MAX];			// �v���C���[�\����


//=============================================================================
// ����������
//=============================================================================
HRESULT InitUi(int type)
{
	TITLEPLAYER *title = &titleWk[0];

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int i = 0; i < TITLEPLAYER_MAX; i++, title++)
	{
		title->use = true;											// �g�p
		title->pos = D3DXVECTOR3(10.0f + 10.0f, 0.0f, 0.0f);	// ���W�f�[�^��������
		title->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// ��]�f�[�^��������
		title->col = D3DXCOLOR(0.0, 0.0, 0.0, 0.5);				// �F
		title->PatternAnim = 0;
		title->PatternAnim = rand() % ANIM_PATTERN_NUM;				// �A�j���p�^�[���ԍ��������_���ŏ�����


																	// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,							// �f�o�C�X�ւ̃|�C���^
			TEXTURE_STAGE1_TITLE,									// �t�@�C���̖��O
			&D3DTextureUi);											// �ǂݍ��ރ������[

		MakeVertexUi();
	}
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitUi(void)
{
	if (D3DTextureUi != NULL)
	{// �e�N�X�`���̊J��
		D3DTextureUi->Release();
		D3DTextureUi = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateUi(void)
{

	MakeVertexUi();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawUi(void)
{
	TITLEPLAYER *title = &titleWk[0];

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, D3DTextureUi);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWkUi, sizeof(VERTEX_2D));


}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexUi(void)
{

	// ���_���W�̐ݒ�
	vertexWkUi[0].vtx = D3DXVECTOR3(STAGE1_TITLE_POS_X, STAGE1_TITLE_POS_Y, 0.0f);
	vertexWkUi[1].vtx = D3DXVECTOR3(STAGE1_TITLE_POS_X + STAGE1_TITLE_SIZE_X, STAGE1_TITLE_POS_Y, 0.0f);
	vertexWkUi[2].vtx = D3DXVECTOR3(STAGE1_TITLE_POS_X, STAGE1_TITLE_POS_Y + STAGE1_TITLE_SIZE_Y, 0.0f);
	vertexWkUi[3].vtx = D3DXVECTOR3(STAGE1_TITLE_POS_X + STAGE1_TITLE_SIZE_X, STAGE1_TITLE_POS_Y + STAGE1_TITLE_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	vertexWkUi[0].rhw =
	vertexWkUi[1].rhw =
	vertexWkUi[2].rhw =
	vertexWkUi[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	vertexWkUi[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkUi[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkUi[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkUi[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);


	// �e�N�X�`�����W�̐ݒ�
	vertexWkUi[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWkUi[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertexWkUi[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWkUi[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	return S_OK;
}
//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureUiPlayer(int no, int cntPattern)
{
	TITLEPLAYER *title = &titleWk[no];

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
void SetVertexUiPlaier(int no)
{
	TITLEPLAYER *title = &titleWk[no];

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



////=============================================================================
////
//// �w�i���� [HitPoint.cpp]
//// Author : ���c�@���� 
////
////=============================================================================
//#include "HitPoint.h"
//
////*****************************************************************************
//// �}�N����`
////*****************************************************************************
//
////*****************************************************************************
//// �v���g�^�C�v�錾
////*****************************************************************************
//HRESULT MakeVertexHitPoint(LPDIRECT3DDEVICE9 pDevice);
//void SetTextureHitPoint(float val);
//
////*****************************************************************************
//// �O���[�o���ϐ�
////*****************************************************************************
//LPDIRECT3DTEXTURE9		D3DTextureHitPoint[2] = {};		// �e�N�X�`���ւ̃|�C���^
//LPDIRECT3DVERTEXBUFFER9 D3DVtxBuffHitPoint = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
//
//D3DXVECTOR3				posHitPoint;						// �ʒu
//D3DXVECTOR3				rotHitPoint;						// ����
//
////=============================================================================
//// ����������
////=============================================================================
//HRESULT InitHitPoint(int type)
//{
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();
//
//	// �e�N�X�`���[�̏��������s���H
//	if (type == 0)
//	{
//		// �e�N�X�`���̓ǂݍ���
//		D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
//		TEXTURE_HITPOINT,									// �t�@�C���̖��O
//		&D3DTextureHitPoint[0]);								// �ǂݍ��ރ������[
//	}
//
//	posHitPoint = D3DXVECTOR3(-5.0f, 5.0f, 0.0f);
//
//
//	// ���_���̍쐬
//	MakeVertexHitPoint(pDevice);
//
//
//
//	SetTextureHitPoint(100.0f);
//
//	return S_OK;
//
//}
//
////=============================================================================
//// �I������
////=============================================================================
//void UninitHitPoint(void)
//{
//	if (D3DTextureHitPoint[0] != NULL)
//	{// �e�N�X�`���̊J��
//		D3DTextureHitPoint[0]->Release();
//		D3DTextureHitPoint[0] = NULL;
//	}
//
//}
//
////=============================================================================
//// �X�V����
////=============================================================================
//void UpdateHitPoint(void)
//{
//}
//
////=============================================================================
//// �`�揈��
////=============================================================================
//void DrawHitPoint(void)
//{
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();
//
//	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
//	pDevice->SetStreamSource(0, D3DVtxBuffHitPoint, 0, sizeof(VERTEX_2D));
//
//	// ���_�t�H�[�}�b�g�̐ݒ�
//	pDevice->SetFVF(FVF_VERTEX_2D);
//
//	// �e�N�X�`���̐ݒ�
//	pDevice->SetTexture(0, D3DTextureHitPoint[0]);
//
//	// �|���S���̕`��
//	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (NUM_PLACE * 4), NUM_POLYGON);
//
//
//}
//
////=============================================================================
//// ���_�̍쐬
////=============================================================================
//HRESULT MakeVertexHitPoint(LPDIRECT3DDEVICE9 pDevice)
//{
//
//	//���_�o�b�t�@�̒��g�𖄂߂�
//	VERTEX_2D *pVtx;
//
//	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
//	D3DVtxBuffHitPoint->Lock(0, 0, (void**)&pVtx, 0);
//
//	// ���_���W�̐ݒ�
//	pVtx[0].vtx = D3DXVECTOR3(HITPOINT_POS_X,HITPOINT_POS_Y, 0.0f);
//	pVtx[1].vtx = D3DXVECTOR3(HITPOINT_POS_X + HITPOINT_SIZE_X, HITPOINT_POS_Y, 0.0f);
//	pVtx[2].vtx = D3DXVECTOR3(HITPOINT_POS_X,HITPOINT_POS_Y + HITPOINT_SIZE_Y, 0.0f);
//	pVtx[3].vtx = D3DXVECTOR3(HITPOINT_POS_X + HITPOINT_SIZE_X, HITPOINT_POS_Y + HITPOINT_SIZE_Y, 0.0f);
//
//	// rhw�̐ݒ�
//	pVtx[0].rhw =
//	pVtx[1].rhw =
//	pVtx[2].rhw =
//	pVtx[3].rhw = 1.0f;
//
//	// ���ˌ��̐ݒ�
//	pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//	pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//	pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//	pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//
//	// �e�N�X�`�����W�̐ݒ�
//	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
//	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
//	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
//	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
//
//	return S_OK;
//
//}
//
////=============================================================================
//// �e�N�X�`�����W�̐ݒ�
////=============================================================================
//void SetTextureHitPoint(float val)
//{
//	VERTEX_2D *pVtx;
//
//	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
//	D3DVtxBuffHitPoint->Lock(0, 0, (void**)&pVtx, 0);
//
//	//pVtx += (nIdx * 4);
//
//	// �e�N�X�`�����W�̐ݒ�
//	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
//	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
//	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
//	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
//
//	// ���_�f�[�^���A�����b�N����
//	D3DVtxBuffHitPoint->Unlock();
//
//
//}
//
//
