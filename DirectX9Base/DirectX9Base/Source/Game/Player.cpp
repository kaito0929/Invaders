#include "Player.h"

#include <stdio.h>
#include <stdlib.h>	//rand()�֐��p
#include <time.h>	//time()�֐��p
#include <math.h>


Player::Player()
{		

}

Player::~Player()
{

}

//�������֐�
void Player::Initialize()
{
	PlayerModel.Load(_T("Model/Player.x"));

	PlayerPos.x = PlayerPos.y = PlayerPos.z = 0.0f;
	CameraPos.x = CameraPos.y = CameraPos.z = 0.0f;

	PlayerRotateZ = 0.0f;

	//�J�����̈ړ�
	CameraPos.x = PlayerPos.x + (0.0f * -0.6f * 100.0f);
	CameraPos.y = (PlayerPos.y + 40.0f) + (0.0f * -0.6f * 100.0f);
	CameraPos.z = (PlayerPos.z - 20.0f) + (1.0f * -0.6f * 100.0f);

	camera.SetEyePoint(CameraPos);
	camera.SetRelLookAtPoint(0.0f, -0.3f, 1.0f);

	camera.UpdateViewMatrix();

	PlayerAliveFlag = true;

}

//�`��֐�
void Player::Draw()
{
	D3DXMatrixTranslation(&mat_transform, PlayerPos.x, PlayerPos.y, PlayerPos.z);	//���W
	D3DXMatrixScaling(&mat_scale, 0.1f, 0.1f, 0.1f);								//�g��
	D3DXMatrixRotationYawPitchRoll(&mat_rotate, 0.0f, 0.0f, PlayerRotateZ);//��]	

	if (PlayerAliveFlag == true)
	{
		//�v���C���[�i���@�j�̕`��
		PlayerModel.Draw(mat_transform, mat_scale, mat_rotate);
	}
}

void Player::Update()
{
	//�v���C���[�̐����t���O��true�Ȃ�Ώ������s���悤��
	if (PlayerAliveFlag == true)
	{
		PlayerMoveControl();
		CameraControl();
	}
}

//�v���C���[�̓����̐���
void Player::PlayerMoveControl()
{
	DirectInput* pDi = DirectInput::GetInstance();

	//���ւ̈ړ�
	if (pDi->KeyCount(DIK_LEFT))
	{
		//�v���C���[��x���W���}�C�i�X���č��ֈړ�
		PlayerPos.x--;
		//���@�����ւƌX����
		PlayerRotateZ += PlayerRotateZ_ChangeNum;
		if (PlayerRotateZ >= PlayerRotateLeftMax)
		{
			PlayerRotateZ = PlayerRotateLeftMax;
		}
	}

	//�E�ւ̈ړ�
	if (pDi->KeyCount(DIK_RIGHT))
	{
		//�v���C���[��x���W���v���X���č��ֈړ�
		PlayerPos.x++;
		//���@���E�ւƌX����
		PlayerRotateZ -= PlayerRotateZ_ChangeNum;
		if (PlayerRotateZ <= PlayerRotateRightMax)
		{
			PlayerRotateZ = PlayerRotateRightMax;
		}
	}

	//���@�̌X���������Œ���
	PlayerRotateZ *= 0.8f;

}


//�J�����̓����̐���
void Player::CameraControl()
{
	//���@�ɍ��킹���J�����̈ړ�
	CameraPos.x = PlayerPos.x + (0.0f * Camera_Pos_Set * Camera_Distance);
	//���W�̍X�V
	camera.SetEyePoint(CameraPos);
	//�J�����̍X�V
	camera.UpdateViewMatrix();
}

