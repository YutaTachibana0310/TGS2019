//=============================================================================
//
// �ؒf��G�t�F�N�g�\�� [SliceEffect.cpp]
// Author : ����݂�
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

// ���X�g�o�^
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
	//���X�g�폜
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
	{// �e�N�X�`���̊J��
		D3DTexture = NULL;
	}

	if (D3DVtxBuff != NULL)
	{// ���_�o�b�t�@�̊J��
		D3DVtxBuff->Release();
		D3DVtxBuff = NULL;
	}

	if (D3DIdxBuff)
	{// �C���f�b�N�X�o�b�t�@�̊J��
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
	   
	// ���C���e�B���O�𖳌��ɂ���
	device->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	// �r���[�}�g���b�N�X���擾
	mtxView = GetMtxView();

	// �t�s������Ƃ߂�
	D3DXMatrixInverse(&mtxWorld, NULL, &mtxView);
	mtxWorld._41 = 0.0f;
	mtxWorld._42 = 0.0f;
	mtxWorld._43 = 0.0f;
	   
	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScale, scl.x, scl.y, scl.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScale);

	// ��]�𔽉f
	//D3DXMatrixRotationYawPitchRoll(&mtxRotation, rot.y, rot.x, rot.z);
	//D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRotation);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, pos.x,	pos.y, pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	device->SetTransform(D3DTS_WORLD, &mtxWorld);

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	device->SetStreamSource(0, D3DVtxBuff, 0, sizeof(VERTEX_3D));

	// �C���f�b�N�X�o�b�t�@�������_�����O�p�C�v���C���ɐݒ�
	device->SetIndices(D3DIdxBuff);

	// ���_�t�H�[�}�b�g�̐ݒ�
	device->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	device->SetTexture(0, D3DTexture);

	// �|���S���̕`��
	device->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, numVtx, 0, numPolygon);

	// ���C���e�B���O��L���ɂ���
	device->SetRenderState(D3DRS_LIGHTING, TRUE);

}


//=============================================================================
// ���_���̍쐬
//=============================================================================
HRESULT SliceEffect::MakeVertex(SliceData initData)
{
	LPDIRECT3DDEVICE9 device = GetDevice();


	D3DTexture = initData.D3DTexture;

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(device->CreateVertexBuffer(sizeof(VERTEX_3D) * numVtx,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,						// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_3D,							// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,						// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&D3DVtxBuff,						// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))									// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	// �I�u�W�F�N�g�̃C���f�b�N�X�o�b�t�@�𐶐�
	if (FAILED(device->CreateIndexBuffer(sizeof(WORD) * numVtx,			// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,					// ���_�o�b�t�@�̎g�p�@�@
		D3DFMT_INDEX16,						// �g�p����C���f�b�N�X�t�H�[�}�b�g
		D3DPOOL_MANAGED,					// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&D3DIdxBuff,					// �C���f�b�N�X�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))								// NULL�ɐݒ�
	{
		return E_FAIL;
	}


	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D	*vtx;
		WORD		*idx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		D3DVtxBuff->Lock(0, 0, (void**)&vtx, 0);
		D3DIdxBuff->Lock(0, 0, (void**)&idx, 0);

		for (int i = 0; i < numVtx; i++)
		{
			// ���_���W�̐ݒ�
			vtx[i].vtx = initData.posVtx[i];
			// ���ˌ��̐ݒ�
			vtx[i].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			// �e�N�X�`�����W�̐ݒ�
			vtx[i].tex = initData.posUV[i];

			idx[i] = i;
		}

		// ���_�f�[�^���A�����b�N����
		D3DVtxBuff->Unlock();
		D3DIdxBuff->Unlock();

	}

	return S_OK;
}
