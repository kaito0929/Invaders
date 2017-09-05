#pragma once

#include "../Direct3D/mesh.h"
#include "../Direct3D/Direct3D.h"
#include "../Direct3D/Texture.h"
#include "../Direct3D/Sprite.h"
#include "../Direct3D/camera.h"
#include "../BoundingBox/BoundingBox.h"
#include "../Input/directInput.h"

#include "../Random/Random.h"

#include "../Game/SoundEffect.h"

#define EnemyType 4					//�G�̎��
#define EnemyMoveSpeed 0.1f			//�G�̈ړ����x
#define RedEnemyMoveSpeed 0.3f		//�ԐF�̓G�̈ړ����x

#define DestroyEffectNum 20	//�G��|�������̃G�t�F�N�g�̐�

#define PI 3.141592653589793f

#define BlueEnemyNum 6		//�F�̓G�̑���
#define RedEnemyNum 6		//�ԐF�̓G�̑���
#define GreenEnemyNum 24	//�ΐF�̓G�̑���
#define PurpleEnemyNum 12	//���F�̓G�̑���

#define BulletShotTiming 2	//�G���e�𔭎˂���^�C�~���O
#define BulletEndTiming 3	//�G�̒e��������^�C�~���O


//�G�����ꂽ�ۂ̃G�t�F�N�g�p�̍\����
struct DestroyEffect
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 angle;		//����
	float speed;			//����
	int count;				//�`�悷�鎞��
	bool used;				//�g�p����
};


//================================================================
//�N���X��  �FEnemy�N���X
//���N���X�F
//
//���e�F���̃N���X�����j�b�g�̊��N���X�Ƃ��Ĕh�������Ă���
//================================================================

class Enemy
{
public:

	//�R���X�g���N�^
	Enemy();
	//�f�X�g���N�^
	~Enemy();

	//�G�̃��f��
	Mesh EnemyModel[EnemyType];
	//���b�V���ɓn���s����쐬
	D3DXMATRIXA16 mat_transform, mat_scale, mat_rotate;

	//�e�����̃x�N�g��
	//�����蔻��Ɏg��
	D3DXVECTOR3 forward;
	D3DXVECTOR3 right;
	D3DXVECTOR3 up;

	Texture *DestroyTex;
	Random random;

	//�S�Ă̓G��|�������̔���
	bool EnemyOllDestroy;

	//�p�x
	float degree;
	//���W�A��
	float radian;

	float EnemyRadius[3];

	SoundEffect se;
};


//================================================================
//�N���X��  �FBlueEnemy�N���X
//���N���X�FEnemy�N���X
//
//���e�FEnemy�N���X����h���������N���X�B�F�̓G�̃N���X
//================================================================

class BlueEnemy : public Enemy
{
private:


	//�G�̈ʒu
	D3DXVECTOR3 BlueEnemyPos[BlueEnemyNum];

	//�G�̐����t���O
	//true�Ȃ�Ε`�悵�āAfalse�Ȃ�Ώ�����悤�ɂ���
	bool BlueEnemyAliveFlag[BlueEnemyNum];

	//�F�̓G�̌����i���ʁj
	D3DXVECTOR3 BlueEnemyYaw[BlueEnemyNum];

	DestroyEffect destroyEffect[DestroyEffectNum][BlueEnemyNum];

	VERTEX *vertex;

	//�F�̓G��S���|�������̃t���O
	bool BlueEnemyOllDown;

	float EnemyRadian[BlueEnemyNum];


public:

	//�R���X�g���N�^
	BlueEnemy();
	//�f�X�g���N�^
	~BlueEnemy();

	//������
	void Initialize();
	//���ۂ̓���
	void Update();
	//�`��
	void Draw();

	void BlueEnemyReset();

	bool BlueEnemyCollision(OrientedBoundingBox obb);

	//�G�����ł���ۂ̃G�t�F�N�g��`��
	void DestroyEffectDraw();
	//�G�����ꂽ���̃G�t�F�N�g�̈ʒu�Ȃǂ�ݒ肷��֐�
	void DestroyEffectSet();

	bool GetBlueEnemyOllDown() { return BlueEnemyOllDown; }

	//�G�̓����蔻��
	OrientedBoundingBox enemyObb[BlueEnemyNum];


};


//================================================================
//�N���X��  �FRedEnemy�N���X
//���N���X�FEnemy�N���X
//
//���e�FEnemy�N���X����h���������N���X�B�ԐF�̓G�̃N���X
//================================================================

class RedEnemy : public Enemy
{
private:


	//�G�̈ʒu
	D3DXVECTOR3 RedEnemyPos[RedEnemyNum];

	//�G�̐����t���O
	//true�Ȃ�Ε`�悵�āAfalse�Ȃ�Ώ�����悤�ɂ���
	bool RedEnemyAliveFlag[RedEnemyNum];

	//�ԐF�̓G�̌����i���ʁj
	D3DXVECTOR3 RedEnemyYaw[RedEnemyNum];

	DestroyEffect destroyEffect[DestroyEffectNum][RedEnemyNum];

	VERTEX *vertex;

	//�ԐF�̓G��S���|�������̃t���O
	bool RedEnemyOllDown;


public:

	//�R���X�g���N�^
	RedEnemy();
	//�f�X�g���N�^
	~RedEnemy();

	//������
	void Initialize();
	//���ۂ̓���
	void Update();
	//�`��
	void Draw();

	void RedEnemyReset();

	bool RedEnemyCollision(OrientedBoundingBox obb);

	//�G�����ł���ۂ̃G�t�F�N�g��`��
	void DestroyEffectDraw();
	//�G�����ꂽ���̃G�t�F�N�g�̈ʒu�Ȃǂ�ݒ肷��֐�
	void DestroyEffectSet();

	bool GetRedEnemyOllDown() { return RedEnemyOllDown; }

	//�G�̓����蔻��
	OrientedBoundingBox enemyObb[RedEnemyNum];


};


//================================================================
//�N���X��  �FGreenEnemy�N���X
//���N���X�FEnemy�N���X
//
//���e�FEnemy�N���X����h���������N���X�B�ΐF�̓G�̃N���X
//================================================================

class GreenEnemy : public Enemy
{
private:

	//�G�̈ʒu
	D3DXVECTOR3 GreenEnemyPos[GreenEnemyNum];

	//�G�̐����t���O
	//true�Ȃ�Ε`�悵�āAfalse�Ȃ�Ώ�����悤�ɂ���
	bool GreenEnemyAliveFlag[GreenEnemyNum];

	//�ΐF�̓G�̌����i���ʁj
	D3DXVECTOR3 GreenEnemyYaw[GreenEnemyNum];

	DestroyEffect destroyEffect[DestroyEffectNum][GreenEnemyNum];

	VERTEX *vertex;

	//�ΐF�̓G��S���|�������̃t���O
	bool GreenEnemyOllDown;

	//�΂̓G�����˂���e
	Mesh EnemyBullet;
	//���b�V���ɓn���s����쐬
	D3DXMATRIXA16 mat_bulletTransform, mat_bulletScale, mat_bulletRotate;

	//�e�𔭎˂��Ă��邩�̃t���O
	bool GreenEnemyShotFlag[GreenEnemyNum];

	//�e���˗p�̃J�E���g
	int ShotCount;
	//�e���˂��Ǘ�����t���[��
	int ShotFrame;

	//�e�����ˍς݂��̃t���O
	bool BulletFiredFlag;

	// �G��g�ł����邽�߂̐��l
	float Wave;

	D3DXVECTOR3 BulletPos[GreenEnemyNum];
	D3DXVECTOR3 BulletAngle[GreenEnemyNum];

	//�e�̓����蔻��
	OrientedBoundingBox bulletObb[GreenEnemyNum];

	//�e�����̃x�N�g��
	//�����蔻��Ɏg��
	D3DXVECTOR3 forward_bullet;
	D3DXVECTOR3 right_bullet;
	D3DXVECTOR3 up_bullet;

	float EnemyRadian[GreenEnemyNum];


public:

	//�R���X�g���N�^
	GreenEnemy();
	//�f�X�g���N�^
	~GreenEnemy();

	//������
	void Initialize();
	//���ۂ̓���
	void Update();
	//�`��
	void Draw();

	void GreenEnemyReset();

	bool GreenEnemyCollision(OrientedBoundingBox obb);


	//�G�����ł���ۂ̃G�t�F�N�g��`��
	void DestroyEffectDraw();
	//�G�����ꂽ���̃G�t�F�N�g�̈ʒu�Ȃǂ�ݒ肷��֐�
	void DestroyEffectSet();

	//�G�̒e�𔭎˂�����֐�
	void EnemyBulletShot();
	void EnemyBulletSet();

	bool EnemyBulletCollision(OrientedBoundingBox obb);

	bool GetGreenEnemyOllDown() { return GreenEnemyOllDown; }

	//�G�̓����蔻��
	OrientedBoundingBox enemyObb[GreenEnemyNum];


};


//================================================================
//�N���X��  �FPurpleEnemy�N���X
//���N���X�FEnemy�N���X
//
//���e�FEnemy�N���X����h���������N���X�B���F�̓G�̃N���X
//================================================================

class PurpleEnemy : public Enemy
{
private:

	//�G�̈ʒu
	D3DXVECTOR3 PurpleEnemyPos[PurpleEnemyNum];

	//�G�̐����t���O
	//true�Ȃ�Ε`�悵�āAfalse�Ȃ�Ώ�����悤�ɂ���
	bool PurpleEnemyAliveFlag[PurpleEnemyNum];

	//�ΐF�̓G�̌����i���ʁj
	D3DXVECTOR3 PurpleEnemyYaw[PurpleEnemyNum];

	DestroyEffect destroyEffect[DestroyEffectNum][PurpleEnemyNum];

	VERTEX *vertex;

	//���F�̓G��S���|�������̃t���O
	bool PurpleEnemyOllDown;

	int HitPoint[PurpleEnemyNum];

	float EnemyRadian[PurpleEnemyNum];


public:

	//�R���X�g���N�^
	PurpleEnemy();
	//�f�X�g���N�^
	~PurpleEnemy();

	//������
	void Initialize();
	//���ۂ̓���
	void Update();
	//�`��
	void Draw();

	//���F�̓G�̈ʒu�␶���t���O�Ȃǂ̏�����
	void PurpleEnemyReset();

	//���F�̓G�̏Փ˔���
	bool PurpleEnemyCollision(OrientedBoundingBox obb, bool* flag);

	//�G�����ł���ۂ̃G�t�F�N�g��`��
	void DestroyEffectDraw();
	//�G�����ꂽ���̃G�t�F�N�g�̈ʒu�Ȃǂ�ݒ肷��֐�
	void DestroyEffectSet();

	//���F�̓G���S�ē|���ꂽ���̃t���O��n���֐�
	bool GetPurpleEnemyOllDown() { return PurpleEnemyOllDown; }

	//�G�̓����蔻��
	OrientedBoundingBox enemyObb[PurpleEnemyNum];



};
