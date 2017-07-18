#pragma once

#include "../Direct3D/Texture.h"
#include "../Direct3D/Sprite.h"
#include "../Direct3D/mesh.h"
#include "../Direct3D/Direct3D.h"
#include "../Direct3D/camera.h"
#include "../Input/directInput.h"
#include "../Input/Xinput.h"

#include "../Scene/SceneManager.h"
#include "../Scene/ISceneChanger.h"
#include "../Scene/BaseScene.h"

#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Sound.h"
#include "SoundEffect.h"
#include "NumDisplay.h"
#include "BackGround.h"
#include "../Fade/Fade.h"
#include "../Random/Random.h"


//��ʂ�x���ł̒����̐��l
#define Screen_CenterX 650
//��ʊO
#define Screen_Out -120

//�X�^�[�g�̕����𓮂������l
#define StartTex_Move 25
//�v���C���[�̑��삪�\�ɂȂ�܂ł̃C���^�[�o��
#define Start_Count_Max 10

extern int Score;

//���C���Q�[���̃t���[
enum MAINGAME_STATE
{
	FADE,	//�t�F�[�h�C��
	SIGNAL,	//�J�n�̍��}
	MAIN,	//���C���̊J�n
};

class GameState : public BaseScene
{
private:

	Player player;
	Enemy enemy;
	Bullet bullet;

	//���Đ��p
	Sound sound;
	SoundEffect se;

	//�X�R�A�̕\���p
	NumDisplay numDisplay;

	MAINGAME_STATE mainState;

	//�t�F�[�h�C���A�A�E�g�֌W
	Fade fade;
	//�w�i�`��p
	BackGround backGround;

	//�Q�[���J�n�̍��}���s���e�N�X�`��
	Texture StartTex;
	Sprite StartSprite;

	//�X�^�[�g�̃e�N�X�`����x���W
	int StartTexPosX;
	//�X�^�[�g�̍��}�����Ă���̃C���^�[�o��
	int StartCount;

public:
	//�R���X�g���N�^
	GameState::GameState(ISceneChanger* changer);
	//�f�X�g���N�^
	~GameState();			

	//������
	void Initialize() override;
	//���ۂ̓���
	void Update() override;
	//�`��
	void Draw() override;
};