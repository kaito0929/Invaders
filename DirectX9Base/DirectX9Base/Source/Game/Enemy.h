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
#define EnemyNum 30					//�G�̑���
#define EnemyMoveSpeed 0.1f			//�G�̈ړ����x
#define EnemyBorderlinePosZ 10.0f	//�G�����B���Ă͂����Ȃ�z���W

#define DestroyEffectNum 20			//�G��|�������̃G�t�F�N�g�̐�


struct DestroyEffect
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 angle;
	float speed;
	int count;
	bool used;
};

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

	DestroyEffect destroyEffect[DestroyEffectNum];
	Texture *DestroyTex;

	VERTEX *vertex;
	Random random;

public:

	Enemy();
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

	bool EnemyBorderlineReaching();
};