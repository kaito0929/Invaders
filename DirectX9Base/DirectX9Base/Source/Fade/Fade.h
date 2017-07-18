#pragma once

#include "../Direct3D/mesh.h"
#include "../Direct3D/Direct3D.h"
#include "../Direct3D/Texture.h"
#include "../Direct3D/Sprite.h"
#include "../Direct3D/camera.h"
#include "../BoundingBox/BoundingBox.h"
#include "../Input/directInput.h"

//�t�F�[�h�A�E�g�p�̐��l
#define FADE_OUT_CHANGENUM 1 
#define FADE_OUT_END 1
//�t�F�[�h�C���p�̐��l
#define FADE_IN_CHANGENUM -1 
#define FADE_IN_END 0

#define FADE_SPEED 0.01f


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
	//���ۂ̓���
	void Update();
	//�`��
	void Draw();

	bool FadeIn();
	bool FadeOut();


};