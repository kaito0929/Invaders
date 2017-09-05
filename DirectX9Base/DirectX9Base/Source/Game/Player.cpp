#include "Player.h"

//�R���X�g���N�^
Player::Player()
{		

}

//�f�X�g���N�^
Player::~Player()
{
	delete DestroyTex;
	delete[] vertex;
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

	//�v���C���[�̈ʒu�ݒ�
	PlayerPos.x = 0.0f - PlayerAngle.x * 170.0f;
	PlayerPos.y = 0.0f;
	PlayerPos.z = 170.0f - PlayerAngle.z * 170.0f;

	PlayerAliveFlag = true;
	PlayerHp = 3;

	HitPointTex.Load("Texture/heart_gloss.png");

	for (int i = 0; i < 3; i++)
	{
		HitPointSprite[i].SetSize(70, 70);
	}

	HitPointSprite[0].SetPos(1190, 700);
	HitPointSprite[1].SetPos(1120, 700);
	HitPointSprite[2].SetPos(1050, 700);

	for (int i = 0; i < DestroyEffectNum; i++)
	{
		destroyEffect[i].pos = PlayerPos;
		destroyEffect[i].speed = 1.0f;
		destroyEffect[i].angle = D3DXVECTOR3(random.GetRandom_Int(1, 250), random.GetRandom_Int(1, 100), random.GetRandom_Int(100, 1100));
		destroyEffect[i].count = 0;
		destroyEffect[i].used = false;
	}


	DestroyTex = new Texture;
	DestroyTex->Load("Texture/effect1.png");
	vertex = new VERTEX[DestroyEffectNum];



	//�����蔻��----------------------------------------
	//����	
	forward.x = cos(-PlayerYaw + (D3DX_PI / 2));
	forward.y = cos(0.0f + (D3DX_PI / 2));
	forward.z = sin(-PlayerYaw + (D3DX_PI / 2));

	////�E��
	right.x = cos(-PlayerYaw);
	right.y = 0;
	right.z = sin(-PlayerYaw);

	up.x = 0;
	up.y = 1;
	up.z = 0;

	playerObb.SetLength(20, 10, 10);
	playerObb.UpdateInfo(PlayerPos,forward,right,up);

	//--------------------------------------------------

	camera.SetEyePoint(CameraPos);
	camera.SetRelLookAtPoint(PlayerAngle.x, -0.3f, PlayerAngle.z);

	camera.UpdateViewMatrix();
}

//�`��֐�
void Player::Draw()
{
	if (PlayerAliveFlag == true)
	{
		D3DXMatrixTranslation(&mat_transform, PlayerPos.x, PlayerPos.y, PlayerPos.z);	//���W
		D3DXMatrixScaling(&mat_scale, 0.1f, 0.1f, 0.1f);								//�g��
		D3DXMatrixRotationYawPitchRoll(&mat_rotate, PlayerYaw, 0.0f, PlayerRoll);//��]	

		//�v���C���[�i���@�j�̕`��
		PlayerModel.Draw(mat_transform, mat_scale, mat_rotate);
	}

	//�v���C���[��HP�̕`��
	//�ϐ���1���邽�тɃe�N�X�`��������Ȃ��Ȃ�悤�ɂ���
	for (int i = 0; i < PlayerHp; i++)
	{
		Direct3D::DrawSprite(HitPointSprite[i], HitPointTex);
	}

}

void Player::Update()
{
	//�����蔻��̍X�V
	playerObb.UpdateInfo(PlayerPos, forward, right, up);
	//���@�̐���֐�
	PlayerMoveControl();

	//�J�����̓����𐧌䂷��֐�
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
	PlayerPos.x = 0.0f - PlayerAngle.x * 170.0f;
	PlayerPos.z = 170.0f - PlayerAngle.z * 170.0f;

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

//���Ŏ��̃G�t�F�N�g��`�悷��֐�
void Player::EffectDraw()
{
	for (int i = 0; i < DestroyEffectNum; i++)
	{
		//�t���O��true�ɂȂ��Ă���Ε`��
		if (destroyEffect[i].used == true)
		{
			//�ʒu��ݒ�
			vertex[i].pos = destroyEffect[i].pos;
			//�傫���̐ݒ�
			vertex[i].size = 15.0f;
			//�F�̐ݒ�
			vertex[i].color = (DWORD)D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

			Direct3D::GetInstance()->DrawPointSprite(vertex, DestroyEffectNum, *DestroyTex);
		}
	}
}

//���Ŏ��̃G�t�F�N�g�̈ʒu��t���O��ݒ肷��
void Player::EffectSet()
{
	for (int i = 0; i < DestroyEffectNum; i++)
	{
		if (destroyEffect[i].used == false)
		{
			destroyEffect[i].pos = PlayerPos;
			destroyEffect[i].used = true;
			destroyEffect[i].count = 0;
		}
	}
}

//���Ŏ��̃G�t�F�N�g�̋O��
void Player::EffecMove()
{
	for (int i = 0; i < DestroyEffectNum; i++)
	{
		//�t���O��true�Ȃ�e�ƓG���Փ˂������ƂɂȂ�̂�
		//�G�t�F�N�g���Đ������悤�ɂ���
		if (destroyEffect[i].used == true)
		{
			destroyEffect[i].pos.x += cos(destroyEffect[i].angle.x)*destroyEffect[i].speed;
			destroyEffect[i].pos.y += sin(destroyEffect[i].angle.y)*destroyEffect[i].speed;
			destroyEffect[i].pos.z += sin(destroyEffect[i].angle.z)*destroyEffect[i].speed;

			//�J�E���g�����Z���邱�Ƃŉ�ʑJ�ڂ̏����ɂ���
			destroyEffect[i].count++;
		}
	}

}

