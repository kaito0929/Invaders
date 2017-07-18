#pragma once

#include "../Direct3D/mesh.h"
#include "../Direct3D/Direct3D.h"
#include "../Direct3D/Texture.h"
#include "../Direct3D/Sprite.h"
#include "../Direct3D/camera.h"
#include "../BoundingBox/BoundingBox.h"
#include "../Input/directInput.h"

#include "../Scene/SceneManager.h"
#include "../Scene/ISceneChanger.h"
#include "../Scene/BaseScene.h"

#include "Sound.h"
#include "SoundEffect.h"
#include "../Fade/Fade.h"
#include "GameState.h"
#include "NumDisplay.h"

//�e�N�X�`����_�ł�����֌W
#define TEXTURE_DARW_SPEED 30
#define TEXTURE_DARW_TIMING 0

enum RESULTSTATE
{
	Fade_IN,
	PUSHSPACE,
};

class Result : public BaseScene
{
private:

	//1P�����������ꍇ�ɕ\������e�N�X�`��
	Texture ResultTex;
	Sprite ResultSprite;

	//�G���^�[�L�[�������Ă��炤�w���̃e�N�X�`��
	Texture EnterTex;
	Sprite EnterSprite;

	//�t�F�[�h�A�E�g�����s���邩�̃t���O
	//�G���^�[�L�[���������Ȃ�true�ɂ���
	bool FadeFlag;

	//�G���^�[�L�[�̑���𑣂��t�H���g��_�ł����邽�߂̕ϐ�
	int DrawCount;
	bool DrawFlag;

	Sound sound;
	SoundEffect se;

	Fade fade;
	RESULTSTATE resultState;
	NumDisplay numDisplay;

public:
	//�R���X�g���N�^
	Result::Result(ISceneChanger* changer);
	//�f�X�g���N�^
	~Result();

	//������
	void Initialize() override;
	//���ۂ̓���
	void Update() override;
	//�`��
	void Draw() override;

	void TextureFlashing();
};