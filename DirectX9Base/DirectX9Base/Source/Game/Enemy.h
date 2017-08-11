#pragma once

#include "../Direct3D/mesh.h"
#include "../Direct3D/Direct3D.h"
#include "../Direct3D/Texture.h"
#include "../Direct3D/Sprite.h"
#include "../Direct3D/camera.h"
#include "../BoundingBox/BoundingBox.h"
#include "../Input/directInput.h"

#include "../Random/Random.h"

#define EnemyType 3					//�G�̎��
#define EnemyNum 8					//�G�̑���
#define EnemyMoveSpeed 0.1f			//�G�̈ړ����x
#define EnemyBorderlinePosZ 10.0f	//�G�����B���Ă͂����Ȃ�z���W

#define EnemyColumnNum 3			//�G�̏c��̒���
#define EnemyRowNum 10				//�G�̉���̒���

#define DestroyEffectNum 20			//�G��|�������̃G�t�F�N�g�̐�

#define PI 3.141592653589793

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
private:

	//�G�̃��f��
	Mesh EnemyModel[EnemyType];
	//���b�V���ɓn���s����쐬
	D3DXMATRIXA16 mat_transform, mat_scale, mat_rotate;

	//�G�̈ʒu
	D3DXVECTOR3 EnemyPos[EnemyNum];

	//�G�̓����蔻��
	OrientedBoundingBox enemyObb[EnemyNum];
	//�e�����̃x�N�g��
	//�����蔻��Ɏg��
	D3DXVECTOR3 forward;
	D3DXVECTOR3 right;
	D3DXVECTOR3 up;

	//�G�̐����t���O
	//true�Ȃ�Ε`�悵�āAfalse�Ȃ�Ώ�����悤�ɂ���
	bool EnemyAliveFlag[EnemyNum];
	//�S�Ă̓G��|�������̔���
	bool EnemyOllDestroy;

	DestroyEffect destroyEffect[DestroyEffectNum][EnemyNum];
	Texture *DestroyTex;

	VERTEX *vertex;
	Random random;

	D3DXVECTOR3 angle[EnemyNum];

public:

	//�R���X�g���N�^
	Enemy();
	//�f�X�g���N�^
	~Enemy();

	//������
	void Initialize();
	//���ۂ̓���
	void Update();
	//�`��
	void Draw();

	//�G�Ƃ̓����蔻����s���֐�
	bool EnemyCollision(OrientedBoundingBox obb);

	//�G����x�S�ł������ɍēx�o�������邽�߂̊֐�
	void EnemyReset();

	//�G�����ł���ۂ̃G�t�F�N�g��`��
	void DestroyEffectDraw();
	//�G�����ꂽ���̃G�t�F�N�g�̈ʒu�Ȃǂ�ݒ肷��֐�
	void DestroyEffectSet();

	//�G���w�肵���ʒu�܂œ��B�����ꍇ��true��Ԃ�
	//��ʑJ�ڂ��J�n������֐�
	bool EnemyBorderlineReaching();
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
	//�G�̃��f��
	Mesh BlueEnemyModel;
	//���b�V���ɓn���s����쐬
	D3DXMATRIXA16 mat_transform, mat_scale, mat_rotate;

	//�G�̓����蔻��
	OrientedBoundingBox enemyObb[EnemyNum];
	//�e�����̃x�N�g��
	//�����蔻��Ɏg��
	D3DXVECTOR3 forward;
	D3DXVECTOR3 right;
	D3DXVECTOR3 up;

	//�G�̈ʒu
	D3DXVECTOR3 BlueEnemyPos[EnemyNum];

	//�G�̐����t���O
	//true�Ȃ�Ε`�悵�āAfalse�Ȃ�Ώ�����悤�ɂ���
	bool BlueEnemyAliveFlag[EnemyNum];

	//�F�̓G�̌����i���ʁj
	D3DXVECTOR3 BlueEnemyYaw[EnemyNum];

	//�p�x
	float degree;
	//���W�A��
	float radian;

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

	//�G�̃��f��
	Mesh RedEnemyModel;
	//���b�V���ɓn���s����쐬
	D3DXMATRIXA16 mat_transform, mat_scale, mat_rotate;

	//�G�̓����蔻��
	OrientedBoundingBox enemyObb[EnemyNum];
	//�e�����̃x�N�g��
	//�����蔻��Ɏg��
	D3DXVECTOR3 forward;
	D3DXVECTOR3 right;
	D3DXVECTOR3 up;

	//�G�̈ʒu
	D3DXVECTOR3 RedEnemyPos[EnemyNum];

	//�G�̐����t���O
	//true�Ȃ�Ε`�悵�āAfalse�Ȃ�Ώ�����悤�ɂ���
	bool RedEnemyAliveFlag[EnemyNum];

	//�ԐF�̓G�̌����i���ʁj
	D3DXVECTOR3 RedEnemyYaw[EnemyNum];

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

	//�G�̃��f��
	Mesh GreenEnemyModel;
	//���b�V���ɓn���s����쐬
	D3DXMATRIXA16 mat_transform, mat_scale, mat_rotate;

	//�G�̓����蔻��
	OrientedBoundingBox enemyObb[EnemyNum];
	//�e�����̃x�N�g��
	//�����蔻��Ɏg��
	D3DXVECTOR3 forward;
	D3DXVECTOR3 right;
	D3DXVECTOR3 up;

	//�G�̈ʒu
	D3DXVECTOR3 GreenEnemyPos[EnemyNum];

	//�G�̐����t���O
	//true�Ȃ�Ε`�悵�āAfalse�Ȃ�Ώ�����悤�ɂ���
	bool GreenEnemyAliveFlag[EnemyNum];

	//�ΐF�̓G�̌����i���ʁj
	D3DXVECTOR3 GreenEnemyYaw[EnemyNum];

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

};