//=============================================================================
//GP11A341_34_���c����
// HP [HitPoint.h]
// Author : 
//
//=============================================================================
#ifndef _HITPOINT_H_
#define _HITPOINT_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_STAGE1_TITLE	("data/TEX/HP_flame.png")	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_STAGE0_TITLE	("data/TEX/gauge.png")	// �ǂݍ��ރe�N�X�`���t�@�C����


#define	STAGE1_TITLE_POS_X		(0)							// �^�C�g���̕\���ʒu
#define	STAGE1_TITLE_POS_Y		(-30)						// �^�C�g���̕\���ʒu
#define	STAGE1_TITLE_SIZE_X		(700)						// �^�C�g���̕�
#define	STAGE1_TITLE_SIZE_Y		(200)						// �^�C�g���̍���
#define TEXTURE_PATTERN_DIVIDE_X	(10)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y	(1)		// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM			(TEXTURE_PATTERN_DIVIDE_X*TEXTURE_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION				(5)	// �A�j���[�V�����̐؂�ւ��J�E���g


//�Q�[�W
#define GAUGE00_SIZE_X			(250)											// �e�N�X�`���T�C�Y
#define GAUGE00_SIZE_Y			(25)											// ����
#define GAUGE00_POS_X			(40)											// �|���S���̏����ʒuX(����)
#define GAUGE00_POS_Y			(30)											// ����



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
}	TITLEPLAYER;

#define TITLEPLAYER_MAX					(1)


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitUi(int type);
void UninitUi(void);
void UpdateUi(void);
void DrawUi(void);
//TITLEPLAYER *GetTitlePlayer(int no);

#endif

////=============================================================================
////
//// �Q�[�W���� [HitPoint.h]
//// Author :���c�@����
////
////=============================================================================
//#ifndef _HITPOINT_H_
//#define _HITPOINT_H_
//
//
//#include "main.h"
//#include "Framework\IStateScene.h"
//
////*****************************************************************************
//// �}�N����`
////*****************************************************************************
//#define	TEXTURE_HITPOINT		"data/TEX/HP_flame.png"
//#define	NUM_PLACE		(4)								
//#define HITPOINT_POS_X (10)
//#define HITPOINT_POS_Y (10)
//#define HITPOINT_SIZE_X (400)
//#define HITPOINT_SIZE_Y (400)
////*****************************************************************************
//// �v���g�^�C�v�錾
////*****************************************************************************
//HRESULT InitHitPoint(int type);
//void UninitHitPoint(void);
//void UpdateHitPoint(void);
//void DrawHitPoint(void);
//#endif