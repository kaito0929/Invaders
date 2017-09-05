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


//�e�N�X�`����_�ł�����֌W
#define Texture_Draw_Speed 30
#define Texture_Draw_Timing 0

//�^�C�g���̃t���[
enum TITLESTATE
{
	FADEIN,
	START,
	TUTORIAL,
};


class Title : public BaseScene
{
private:

	//�^�C�g���̃e�N�X�`��
	Texture TitleTex;
	Sprite TitleSprite;

	//�G���^�[�L�[�������Ă��炤�w���̃e�N�X�`��
	Texture EnterTex;
	Sprite EnterSprite;

	//�t�F�[�h�A�E�g�����s���邩�̃t���O
	//�X�y�[�X�L�[���������Ȃ�true�ɂ���
	bool FadeFlag;

	//����𑣂��t�H���g��_�ł����邽�߂̕ϐ�
	int DrawCount;
	bool DrawFlag;

	//�^�C�g����ʂł̃t���[
	TITLESTATE titleState;

	Sound sound;
	SoundEffect se;

	Texture TutorialTex[3];
	Sprite TutorialSprite;

	int TutorialNumber;

	Fade fade;

public:
	//�R���X�g���N�^
	Title::Title(ISceneChanger* changer);
	//�f�X�g���N�^
	~Title();

	//������
	void Initialize() override;
	//���ۂ̓���
	void Update() override;
	//�`��
	void Draw() override;

	void PushKeyDraw();

};