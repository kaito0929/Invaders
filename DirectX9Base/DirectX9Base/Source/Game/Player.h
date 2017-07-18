#pragma once

#include "../Direct3D/mesh.h"
#include "../Direct3D/Direct3D.h"
#include "../Direct3D/Texture.h"
#include "../Direct3D/Sprite.h"
#include "../Direct3D/camera.h"
#include "../BoundingBox/BoundingBox.h"
#include "../Input/directInput.h"

#define PlayerRotateZ_ChangeNum 0.1f	//���@�̌�����ς��鎞�̐��l

#define PlayerRotateLeftMax 1.0f
#define PlayerRotateRightMax -1.0f

#define Camera_Pos_Set -0.6f		//�J�����̈ʒu�ݒ�
#define Camera_Distance 100			//�J�����Ǝ��@�̋���

class Player
{
private:

	//�v���C���[�̃��f��
	Mesh PlayerModel;
	
	//���b�V���ɓn���s����쐬
	D3DXMATRIXA16 mat_transform, mat_scale, mat_rotate;

	//�v���C���[�̃��f�����X���邽�߂̕ϐ�
	float PlayerRotateZ;

	//�J��������
	Camera camera;
	//�J�����̈ʒu
	D3DXVECTOR3 CameraPos;

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


	//�v���C���[�̈ʒu
	D3DXVECTOR3 PlayerPos;

	//�v���C���[�̐����t���O
	bool PlayerAliveFlag;


};