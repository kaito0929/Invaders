#pragma once

#include "../Direct3D/Direct3D.h"
#include "../Direct3D/Texture.h"
#include "../Direct3D/Sprite.h"
#include "../Input/directInput.h"

#include "../Scene/SceneManager.h"
#include "../Scene/ISceneChanger.h"
#include "../Scene/BaseScene.h"

#include "Sound.h"
#include "SoundEffect.h"
#include "../Fade/Fade.h"
#include "GameState.h"
#include "NumDisplay.h"

#define Texture_Draw_Speed 30	//�e�N�X�`����_�ł�����X�s�[�h
#define Texture_Draw_Timing 0	//�e�N�X�`����`�悷��^�C�~���O

//���U���g��ʂ̃t���[
enum RESULT_STATE
{
	FADE_IN,
	PUSHSPACE,
};

class Result : public BaseScene
{
private:

	//���U���g��ʂɕ\������e�N�X�`��
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

	//���y�Đ��p
	Sound sound;
	SoundEffect se;

	//�t�F�[�h�C���A�t�F�[�h�A�E�g�p
	Fade fade;

	//���U���g��ʂ̃t���[
	RESULT_STATE resultState;
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