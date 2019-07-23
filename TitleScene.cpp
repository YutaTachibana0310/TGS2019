//=====================================
//
//�^�C�g���V�[������[TitleScene.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "TitleScene.h"
#include "Framework\SkyBox.h"

#include "Game.h"

#define	TITLE_POS_X			(640-480)							// �^�C�g���̕\���ʒu
#define	TITLE_POS_Y			(105)								// �^�C�g���̕\���ʒu
#define	TITLE_SIZE_X		(1500)								// �^�C�g���̕�
#define	TITLE_SIZE_Y		(600)								// �^�C�g���̍���



/**************************************
�}�N����`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static SkyBox *skybox;
LPDIRECT3DTEXTURE9		D3DTextureTitle = NULL;			// �e�N�X�`���ւ̃|�C���^
VERTEX_2D				vertexWkTitle[NUM_VERTEX];		// ���_���i�[���[�N


/**************************************
����������
***************************************/
void TitleScene::Init()
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	skybox = new SkyBox(D3DXVECTOR3(30000.0f * 2, 30000.0f, 30000.0f), D3DXVECTOR2(6.0f, 1.0f));
	skybox->LoadTexture("data/TEXTURE/skybox.png");

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(Device,						// �f�o�C�X�ւ̃|�C���^
		"data/TEXTURE/TITLEL_TGS.png",		// �t�@�C���̖��O
		&D3DTextureTitle);			// �ǂݍ��ރ������[

	// ���_���W�̐ݒ�
	vertexWkTitle[0].vtx = D3DXVECTOR3(TITLE_POS_X, TITLE_POS_Y, 0.0f);
	vertexWkTitle[1].vtx = D3DXVECTOR3(TITLE_POS_X + TITLE_SIZE_X, TITLE_POS_Y, 0.0f);
	vertexWkTitle[2].vtx = D3DXVECTOR3(TITLE_POS_X, TITLE_POS_Y + TITLE_SIZE_Y, 0.0f);
	vertexWkTitle[3].vtx = D3DXVECTOR3(TITLE_POS_X + TITLE_SIZE_X, TITLE_POS_Y + TITLE_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	vertexWkTitle[0].rhw =
		vertexWkTitle[1].rhw =
		vertexWkTitle[2].rhw =
		vertexWkTitle[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	vertexWkTitle[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkTitle[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkTitle[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWkTitle[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	vertexWkTitle[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWkTitle[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertexWkTitle[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWkTitle[3].tex = D3DXVECTOR2(1.0f, 1.0f);


}

/**************************************
�I������
***************************************/
void TitleScene::Uninit()
{
	SAFE_DELETE(skybox);

	if (D3DTextureTitle != NULL)
	{// �e�N�X�`���̊J��
		D3DTextureTitle->Release();
		D3DTextureTitle = NULL;
	}

}

#include "input.h"
/**************************************
�X�V����
***************************************/
void TitleScene::Update(HWND hWnd)
{
	if (GetAttackButtonTrigger())
	{
		ChangeScene(SceneGame);
	}
	

}

/**************************************
�`�揈��
***************************************/
void TitleScene::Draw()
{
	skybox->Draw();

	LPDIRECT3DDEVICE9 Device = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	Device->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	Device->SetTexture(0, D3DTextureTitle);

	// �|���S���̕`��
	Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWkTitle, sizeof(VERTEX_2D));

}
