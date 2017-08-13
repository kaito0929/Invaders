#pragma once

#include "../Direct3D/Texture.h"
#include "../Direct3D/Sprite.h"
#include "../Direct3D/Direct3D.h"
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


#define Screen_CenterX 650		//��ʂ�x���ł̒����̐��l
#define Screen_Out -120			//��ʊO

#define StartTex_Move 25		//�X�^�[�g�̕����𓮂������l
#define Start_Count_Max 10		//�v���C���[�̑��삪�\�ɂȂ�܂ł̃C���^�[�o��

#define ScorePulsNum 20			//�X�R�A�ɉ��Z���鐔�l
#define RedEnemy_ScorePulsNum 50

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
	BlueEnemy blueEnemy;
	RedEnemy redEnemy;
	GreenEnemy greenEnemy;

	//���Đ��p
	Sound sound;
	SoundEffect se;

	//�t�F�[�h�C���A�A�E�g�֌W
	Fade fade;
	//�w�i�`��p
	BackGround backGround;

	//�X�R�A�̕\���p
	NumDisplay numDisplay;

	//���C���Q�[���̃t���[
	MAINGAME_STATE mainState;

	//�Q�[���J�n�̍��}���s���e�N�X�`��
	Texture StartTex;
	Sprite StartSprite;

	//�X�^�[�g�̃e�N�X�`����x���W
	int StartTexPosX;
	//�X�^�[�g�̍��}�����Ă���̃C���^�[�o��
	int StartCount;

	//�c�莞��
	int Time;
	//�c�莞�ԊǗ��p�̃t���[��
	int TimeFrame;
	//�c�莞�ԕ\���p
	NumDisplay timeDisplay;

	int BulletCount;

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