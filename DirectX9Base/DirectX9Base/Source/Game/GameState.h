#pragma once

#include "../Direct3D/Texture.h"
#include "../Direct3D/Sprite.h"
#include "../Direct3D/Direct3D.h"
#include "../Input/directInput.h"
#include "../Input/Xinput.h"
#include "../BoundingBox/BoundingBox.h"

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


#define Screen_CenterX 650			//��ʂ�x���ł̒����̐��l
#define Screen_Out -120				//��ʊO
#define StartTex_Move 25			//�X�^�[�g�̕����𓮂������l
#define Start_Count_Max 10			//�v���C���[�̑��삪�\�ɂȂ�܂ł̃C���^�[�o��
#define ScoreAddNum 20				//�X�R�A�ɉ��Z���鐔�l
#define RedEnemy_ScoreAddNum 50		//�ԐF�̓G��|�����ꍇ�ɉ��Z����鐔�l
#define OneSecond 60				//��b�o�߂𔻒肷�鐔�l
#define Player_Draw_Speed 5			//�G�̒e�����������ۂ̓_�ł����鑬��
#define Player_Draw_Timing 0		//�_�ł��鎞�̕\������^�C�~���O
#define Enemy_Reset_Timing 15		//�G�̈ʒu�Ȃǂ�����������^�C�~���O
#define TimeAddNum 3				//�F�̓G��|�����ۂɎc�莞�Ԃɉ��Z���鐔�l
#define PlayerRigorTime 120			//�v���C���[�̍d������

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
	Bullet bullet;

	Enemy enemy;
	BlueEnemy blueEnemy;
	RedEnemy redEnemy;
	GreenEnemy greenEnemy;
	PurpleEnemy purpleEnemy;

	//���Đ��p
	Sound sound;
	SoundEffect se;

	//�t�F�[�h�C���A�A�E�g�֌W
	Fade fade;

	//�w�i�`��p
	BackGround backGround;

	//�X�R�A�̕\���p
	NumDisplay numDisplay;
	//�������X�R�A�ƕ�����悤�ɂ���e�N�X�`��
	Texture ScoreTex;
	Sprite ScoreSprite;

	//���C���Q�[���̃t���[
	MAINGAME_STATE mainState;

	//�Q�[���J�n�̍��}���s���e�N�X�`��
	Texture StartTex;
	Sprite StartSprite;

	//�X�^�[�g�̃e�N�X�`����x���W
	float StartTexPosX;
	//�X�^�[�g�̍��}�����Ă���̃C���^�[�o��
	int StartCount;

	//�c�莞��
	int Time;
	//�c�莞�ԊǗ��p�̃t���[��
	int TimeFrame;
	//�c�莞�ԕ\���p
	NumDisplay timeDisplay;

	//�c�莞�Ԃ����������̃e�N�X�`��
	Texture TimeTex;
	//�c�莞�Ԃ����������̈ʒu��傫��
	Sprite TimeSprite;

	//�X�R�A�Ǝc�莞�Ԃ��������̂�
	//������₷���Ȃ�e�N�X�`��
	Texture NumPlusTex[3];
	Sprite NumPlusSprite[3];

	//�G�̒e�ƏՓ˂������̃t���O
	bool PlayerCollisionFlag;
	//�G�̒e�ƏՓ˂��Ă���̃J�E���g
	int PlayerCollisionCount;

	//���@��_�ł����邽�߂̃t���O
	bool PlayerDrawFlag;

	//�����˂��Ă���e
	int BulletNum;

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

	void TimeCount();

	//�G���ړ��\�͈͂��甲�������̔�����s���֐�
	bool EnemyMoveMax();
};