//=====================================
//
//�v���C���[�A�^�b�N����[PlayerAttack.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "PlayerAttack.h"

/**************************************
�}�N����`
***************************************/
#define PLAYERATTACK_EFFECTIVE_DURATION		(30)
#define PLAYERATTACK_SIZE			(100.0f)

/**************************************
�R���X�g���N�^
***************************************/
PlayerAttack::PlayerAttack()
{
	collider = new BoxCollider3D(BoxCollider3DTag::PlayerAttack, &transform.pos);
	collider->active = false;

	mesh = new MeshContainer();
	mesh->Load("data/MODEL/airplane000.x");
	
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->CreateVertexBuffer(sizeof(VERTEX_BILLBOARD) * NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_BILLBOARD,
		D3DPOOL_MANAGED,
		&vtxBuff,
		0);

	VERTEX_BILLBOARD *pVtx;
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].vtx = D3DXVECTOR3(-PLAYERATTACK_SIZE, PLAYERATTACK_SIZE, 0.0f);
	pVtx[1].vtx = D3DXVECTOR3(PLAYERATTACK_SIZE, PLAYERATTACK_SIZE, 0.0f);
	pVtx[2].vtx = D3DXVECTOR3(-PLAYERATTACK_SIZE, -PLAYERATTACK_SIZE, 0.0f);
	pVtx[3].vtx = D3DXVECTOR3(PLAYERATTACK_SIZE, -PLAYERATTACK_SIZE, 0.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx[0].diffuse =
		pVtx[1].diffuse =
		pVtx[2].diffuse =
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	vtxBuff->Unlock();

	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/slash.png", &texture);
}

/**************************************
�f�X�g���N�^
***************************************/
PlayerAttack::~PlayerAttack()
{
	SAFE_DELETE(collider);
	SAFE_DELETE(mesh);
}

/**************************************
������
***************************************/
void PlayerAttack::Init()
{
	cntFrame = 0;
	collider->active = true;
	active = true;
}

/**************************************
�I��
***************************************/
void PlayerAttack::Uninit()
{
	collider->active = false;
	active = false;
}

/**************************************
�X�V
***************************************/
void PlayerAttack::Update()
{
	if (!active)
		return;

	cntFrame++;

	if (cntFrame == PLAYERATTACK_EFFECTIVE_DURATION)
		Uninit();
}

/**************************************
�`��
***************************************/
void PlayerAttack::Draw()
{
	if (!active)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetTexture(0, texture);
	pDevice->SetStreamSource(0, vtxBuff, 0, sizeof(VERTEX_BILLBOARD));

	D3DXMATRIX mtxWorld;
	transform.CalcWorldMtx(&mtxWorld);
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	//�e�X�g
	//transform.scale = D3DXVECTOR3(20.0f, 20.0f, 20.0f);
	//D3DXMATRIX mtxWorld;
	//transform.CalcWorldMtx(&mtxWorld);
	//pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
	//mesh->Draw();
	//transform.scale = D3DXVECTOR3(.0f, .0f, .0f);

#ifdef _DEBUG
	BoxCollider3D::DrawCollider(collider);
#endif
}
