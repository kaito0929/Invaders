#pragma once

#include "../Direct3D/mesh.h"
#include "../Direct3D/Direct3D.h"
#include "../Direct3D/Texture.h"
#include "../Direct3D/Sprite.h"
#include "../Direct3D/camera.h"
#include "../BoundingBox/BoundingBox.h"
#include "../Input/directInput.h"

//�t�F�[�h�A�E�g�p�̐��l
#define Fade_Out_ChangeNum 1	//�t�F�[�h�A�E�g���Ƀ��l�ɉ��Z���鐔�l
#define Fade_Out_End 1			//�e�N�X�`���̃��l���ׂď������I�������鐔�l

//�t�F�[�h�C���p�̐��l
#define Fade_In_ChangeNum -1	//�t�F�[�h�C�����Ƀ��l�ɉ��Z���鐔�l
#define Fade_In_End 0			//�e�N�X�`���̃��l���ׂď������I�������鐔�l

#define FadeSpeed 0.01f			//�t�F�[�h�C���A�t�F�[�h�A�E�g�̑���


class Fade
{
private:

	//�t�F�[�h�C���p�̃e�N�X�`��
	Texture FadeTex;
	Sprite FadeSprite;

public:
	
	//�R���X�g���N�^
	Fade();
	//�f�X�g���N�^
	~Fade();

	//������
	void Initialize();
	//�`��
	void Draw();

	//�t�F�[�h�C���̏������s���֐�
	bool FadeIn();
	//�t�F�[�h�A�E�g�̏������s���֐�
	bool FadeOut();


};