#include "Bullet.h"

Bullet::Bullet()
{

}

Bullet::~Bullet()
{

}

void Bullet::Initialize()
{
	BulletModel.Load(_T("Model/Bullet.x"));

	for (int i = 0; i < BulletMax; i++)
	{
		BulletPos[i].x = BulletPos[i].y = BulletPos[i].z = 0.0f;
		BulletShotAngle[i].x = BulletShotAngle[i].y = BulletShotAngle[i].z = 0.0f;

		bulletObb[i].SetLength(10, 10, 10);

		bulletObb[i].UpdateInfo(BulletPos[i], forward, right, up);
	}

	right.x = cos(0);
	right.y = 0;
	right.z = sin(0);

	up.x = up.z = 0;
	up.y = 1;

	//����	
	forward.x = forward.y = cos(D3DX_PI/2);
	forward.z = sin(D3DX_PI/2);

}

void Bullet::Draw()
{
	for (int i = 0; i < BulletMax; i++)
	{
		//�e�̕`��
		//�t���O��true�ɂȂ��Ă���Ε`�悷��悤��
		//�t���O��true�ɂ���̂̓X�y�[�X�L�[����������
		if (BulletShotFlag[i] == true)
		{
			D3DXMatrixTranslation(&mat_transform, BulletPos[i].x, BulletPos[i].y, BulletPos[i].z);	//���W
			D3DXMatrixScaling(&mat_scale, 0.1f, 0.1f, 0.1f);								//�g��
			D3DXMatrixRotationYawPitchRoll(&mat_rotate, 0.0f, 0.0f, 0.0f);//��]

			BulletModel.Draw(mat_transform, mat_scale, mat_rotate);
		}
	}

	//�e�̓����蔻��̕`��
	//��{�I�Ƀf�o�b�O���Ɏg�p����̂ŕ��i�̓R�����g�A�E�g���Ă���
	//bulletObb.DrawLine();

}

void Bullet::Update()
{
	for (int i = 0; i < BulletMax; i++)
	{
		//�����蔻��̍X�V
		bulletObb[i].UpdateInfo(BulletPos[i], forward, right, up);
	}
}

//�e�̔��ˈʒu��ݒ肷��֐�
void Bullet::BulletSet(D3DXVECTOR3 pPos, D3DXVECTOR3 pAngle)
{
	for (int i = 0; i < BulletMax; i++)
	{
		//�e�̔��˃t���O�ɂ���ď������ω�
		if (BulletShotFlag[i] == true)
		{
			//true�Ȃ牜�ֈړ�
			BulletPos[i] += BulletShotAngle[i] * BulletMoveSpeed;
		}
		else
		{
			//�e�̔��ˊp�x���X�V
			BulletShotAngle[i] = pAngle;
			//false�Ȃ�ʒu���X�V
			BulletPos[i] = pPos;
		}
	}
}