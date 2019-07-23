
//=============================================================================
//GP11A341_34_���c����
// �^�C�g���P��ʏ��� [stage1_title.h]
// Author : 
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_
#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_STAGE1_TITLE	("data/TEX/Thank you for playing.png")	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_STAGE2_TITLE	("data/TEX/coollogo_com - 3677941.png")	// �ǂݍ��ރe�N�X�`���t�@�C����

#define	STAGE1_TITLE_POS_X			(0)									// �^�C�g���̕\���ʒu
#define	STAGE1_TITLE_POS_Y			(0)									// �^�C�g���̕\���ʒu
#define	STAGE1_TITLE_SIZE_X		(SCREEN_WIDTH)									// �^�C�g���̕�
#define	STAGE1_TITLE_SIZE_Y		(SCREEN_HEIGHT)									// �^�C�g���̍���
#define TEXTURE_PATTERN_DIVIDE_X	(10)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM			(TEXTURE_PATTERN_DIVIDE_X*TEXTURE_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION				(5)	// �A�j���[�V�����̐؂�ւ��J�E���g

typedef struct											// �v���C���[�\����
{
	D3DXVECTOR3				pos;						// �|���S���̈ړ���
	D3DXVECTOR3				rot;						// �|���S���̉�]��
	LPDIRECT3DTEXTURE9		Texture;					// �e�N�X�`�����
	VERTEX_2D				vertexWk[NUM_VERTEX];		// ���_���i�[���[�N
	D3DXCOLOR				col;						// �F
	int						PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int						CountAnim;					// �A�j���[�V�����J�E���g
	float					Radius;						// �v���C���[�̔��a
	float					BaseAngle;					// �v���C���[�̊p�x
	float					JumpCount;					//�W�����v
	bool					use;
}	RESULT;

#define TITLEPLAYER_MAX					(1)


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitResult(int type);
void UninitResult(void);
void UpdateResult(void);
void DrawResult(void);

#endif
