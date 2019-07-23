//=============================================================================
//
// �ؒf��G�t�F�N�g�\�� [SliceEffect.h]
// Author : ����݂�
//
//=============================================================================
#ifndef _SLICEEFFECT_H_
#define _SLICEEFFECT_H_

#include "main.h"

struct SliceData
{
public:
	D3DXVECTOR3				pos;				// �ʒu
	D3DXVECTOR3				scl;				// �X�P�[��
	D3DXVECTOR3				rot;
	D3DXVECTOR3				move;				// �ړ���
	D3DXVECTOR3				posVtx[10];			// ���_���W
	D3DXVECTOR2				posUV[10];

	LPDIRECT3DTEXTURE9		D3DTexture = NULL;

	int						numVtx;
	int						numPolygon;

};

class SliceEffect
{
public:

	static SliceEffect*		root;
	static SliceEffect*		last;
	static int				cnt;

	SliceEffect*			next;
	SliceEffect*			prev;

	D3DXVECTOR3				pos;
	D3DXVECTOR3				scl;
	D3DXVECTOR3				rot;
	D3DXVECTOR3				move;
	
	LPDIRECT3DTEXTURE9		D3DTexture = NULL;
	LPDIRECT3DVERTEXBUFFER9 D3DVtxBuff = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9	D3DIdxBuff = NULL;		// �C���f�b�N�X�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

	int						numVtx;
	int						numPolygon;
	int						time;

	bool					use;
	
	SliceEffect(SliceData initData);
	~SliceEffect();

	HRESULT MakeVertex(SliceData initData);
	void SliceEffect::AddList();

	void Update();
	void Draw();

};


#endif
