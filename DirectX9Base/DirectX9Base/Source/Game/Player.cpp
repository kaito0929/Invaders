#include "Player.h"

//�R���X�g���N�^
Player::Player()
{		

}

//�f�X�g���N�^
Player::~Player()
{

}

//�������֐�
void Player::Initialize()
{
	PlayerModel.Load(_T("Model/Player.x"));

	CameraPos.x = CameraPos.y = CameraPos.z = 0.0f;

	PlayerRoll = PlayerYaw =  0.0f;

	PlayerAngle.x = sin(PlayerYaw);
	PlayerAngle.y = sin(0.0f);
	PlayerAngle.z = cos(PlayerYaw);

	//�J�����̈ʒu�ݒ�
	CameraPos.x = PlayerPos.x + (PlayerAngle.x * Camera_Pos_Set * Camera_Distance);
	CameraPos.y = (PlayerPos.y + 40.0f) + (PlayerAngle.y * -0.6f * 100.0f);
	CameraPos.z = PlayerPos.z + (PlayerAngle.z * Camera_Pos_Set * Camera_Distance);

	//�v���C���[���~��`���悤�Ɉړ�������
	PlayerPos.x = 0.0f - PlayerAngle.x * 150.0f;
	PlayerPos.y = 0.0f;
	PlayerPos.z = 150.0f - PlayerAngle.z * 150.0f;


	camera.SetEyePoint(CameraPos);
	camera.SetRelLookAtPoint(PlayerAngle.x, -0.3f, PlayerAngle.z);

	camera.UpdateViewMatrix();
}

//�`��֐�
void Player::Draw()
{
	D3DXMatrixTranslation(&mat_transform, PlayerPos.x, PlayerPos.y, PlayerPos.z);	//���W
	D3DXMatrixScaling(&mat_scale, 0.1f, 0.1f, 0.1f);								//�g��
	D3DXMatrixRotationYawPitchRoll(&mat_rotate, PlayerYaw, 0.0f, PlayerRoll);//��]	

	//�v���C���[�i���@�j�̕`��
	PlayerModel.Draw(mat_transform, mat_scale, mat_rotate);
}

void Player::Update()
{
	PlayerMoveControl();
	CameraControl();
}

//�v���C���[�̓����̐���
void Player::PlayerMoveControl()
{
	DirectInput* pDi = DirectInput::GetInstance();

	PlayerAngle.x = sin(PlayerYaw);
	PlayerAngle.z = cos(PlayerYaw);

	//���ւ̈ړ�
	if (pDi->KeyCount(DIK_LEFT))
	{
		PlayerYaw += 0.01f;

		//���@�����ւƌX����
		PlayerRoll += PlayerRotateZ_ChangeNum;
		if (PlayerRoll >= PlayerRotateLeftMax)
		{
			PlayerRoll = PlayerRotateLeftMax;
		}
	}

	//�E�ւ̈ړ�
	if (pDi->KeyCount(DIK_RIGHT))
	{
		PlayerYaw -= 0.01f;

		//���@���E�ւƌX����
		PlayerRoll -= PlayerRotateZ_ChangeNum;
		if (PlayerRoll <= PlayerRotateRightMax)
		{
			PlayerRoll = PlayerRotateRightMax;
		}
	}

	//�v���C���[���~��`���悤�Ɉړ�������
	PlayerPos.x = 0.0f - PlayerAngle.x * 150.0f;
	PlayerPos.z = 150.0f - PlayerAngle.z * 150.0f;

	//���@�̌X���������Œ���
	PlayerRoll *= 0.8f;

}


//�J�����̓����̐���
void Player::CameraControl()
{
	//���@�ɍ��킹���J�����̈ړ�
	CameraPos.x = PlayerPos.x + (PlayerAngle.x * Camera_Pos_Set * Camera_Distance);
	CameraPos.y = (PlayerPos.y + 40.0f) + (PlayerAngle.y * -0.6f * 100.0f);
	CameraPos.z = PlayerPos.z + (PlayerAngle.z * Camera_Pos_Set * Camera_Distance);

	//�J�����̍��W�̍X�V
	camera.SetEyePoint(CameraPos);
	//�����̍X�V
	camera.SetRelLookAtPoint(PlayerAngle.x, -0.3f, PlayerAngle.z);

	//�J�����̍X�V
	camera.UpdateViewMatrix();
}

