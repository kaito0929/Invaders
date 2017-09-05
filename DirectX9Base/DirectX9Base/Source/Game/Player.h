#pragma once

#include "../Direct3D/mesh.h"
#include "../Direct3D/Direct3D.h"
#include "../Direct3D/Texture.h"
#include "../Direct3D/Sprite.h"
#include "../Direct3D/camera.h"
#include "../BoundingBox/BoundingBox.h"
#include "../Input/directInput.h"

#include "../Game/Enemy.h"
#include "../Random/Random.h"

#define PlayerRotateZ_ChangeNum 0.1f	//���@�̌�����ς��鎞�̐��l

#define PlayerRotateLeftMax 1.0f		//���@�̍������̌X���̍ő�l
#define PlayerRotateRightMax -1.0f		//���@�̉E�����̌X���̍ő�l
#define PlayerMoveLeftMax -100.0f		//���@�̍������ւ̈ړ�����
#define PlayerMoveRightMax 100.0f		//���@�̉E�����ւ̈ړ�����

#define Camera_Pos_Set -0.6f		//�J�����̈ʒu�ݒ�
#define Camera_Distance 100			//�J�����Ǝ��@�̋���

class Player
{
private:

	//�v���C���[�̃��f��
	Mesh PlayerModel;
	
	//���b�V���ɓn���s����쐬
	D3DXMATRIXA16 mat_transform, mat_scale, mat_rotate;

	float PlayerYaw;
	//�v���C���[�̃��f�����X���邽�߂̕ϐ�
	float PlayerRoll;

	Texture HitPointTex;
	Sprite HitPointSprite[3];

	//�J��������
	Camera camera;
	//�J�����̈ʒu
	D3DXVECTOR3 CameraPos;

	OrientedBoundingBox playerObb;

	//�e�����̃x�N�g��
	//�����蔻��Ɏg��
	D3DXVECTOR3 forward;
	D3DXVECTOR3 right;
	D3DXVECTOR3 up;

	//���@�����ł������ɕ\������e�N�X�`��
	Texture *DestroyTex;
	VERTEX *vertex;
	//�G�t�F�N�g�����ł������������肷�郉���_���̐��l
	Random random;


public:

	//�R���X�g���N�^
	Player();
	//�f�X�g���N�^
	~Player();

	//������
	void Initialize();
	//���ۂ̓���
	void Update();
	//�`��
	void Draw();

	//�v���C���[�̈ړ��̐���
	void PlayerMoveControl();

	//�J�����̓����̐���
	void CameraControl();

	//���Ŏ��̃G�t�F�N�g��`�悷��
	void EffectDraw();
	//���Ŏ��̃G�t�F�N�g�̈ʒu�Ȃǂ�ݒ肷��֐�
	void EffectSet();
	//���Ŏ��̃G�t�F�N�g�̋O��
	void EffecMove();

	//�v���C���[�̈ʒu
	D3DXVECTOR3 PlayerPos;
	//�v���C���[�̌����Ă������
	D3DXVECTOR3 PlayerAngle;

	OrientedBoundingBox GetPlayerObb() { return playerObb; };

	//���@�̎c��̗�
	int PlayerHp;
	//�v���C���[�̐����t���O
	bool PlayerAliveFlag;
	//���Ŏ��̃G�t�F�N�g
	DestroyEffect destroyEffect[DestroyEffectNum];


};