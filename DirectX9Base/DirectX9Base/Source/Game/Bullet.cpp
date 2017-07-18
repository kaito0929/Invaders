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

	BulletPos.x = BulletPos.y = BulletPos.z = 0.0f;

	right.x = cos(0);
	right.y = 0;
	right.z = sin(0);

	up.x = up.z = 0;
	up.y = 1;

	//����	
	forward.x = forward.y = cos(D3DX_PI/2);
	forward.z = sin(D3DX_PI/2);

	bulletObb.SetLength(10,10,10);

	bulletObb.UpdateInfo(BulletPos, forward, right, up);
}

void Bullet::Draw()
{
	//�e�̕`��
	//�t���O��true�ɂȂ��Ă���Ε`�悷��悤��
	//�t���O��true�ɂ���̂̓X�y�[�X�L�[����������
	if (BulletShotFlag == true)
	{
		D3DXMatrixTranslation(&mat_transform, BulletPos.x, BulletPos.y, BulletPos.z);	//���W
		D3DXMatrixScaling(&mat_scale, 0.1f, 0.1f, 0.1f);								//�g��
		D3DXMatrixRotationYawPitchRoll(&mat_rotate, 0.0f, 0.0f, 0.0f);//��]

		BulletModel.Draw(mat_transform, mat_scale, mat_rotate);
	}

	//�e�̓����蔻��̕`��
	//��{�I�Ƀf�o�b�O���Ɏg�p����̂ŕ��i�̓R�����g�A�E�g���Ă���
	bulletObb.DrawLine();

}

void Bullet::Update()
{
	//�����蔻��̍X�V
	bulletObb.UpdateInfo(BulletPos, forward, right, up);

	//�e���w�肵���ʒu�܂ňړ�������t���O��fale��
	//false�ɂȂ邱�Ƃɂ���čĂђe�����˂ł���悤�ɂȂ�
	if (BulletPos.z > BulletPosZMax)
	{
		BulletShotFlag = false;
	}
}

//�e�̔��ˈʒu��ݒ肷��֐�
void Bullet::BulletPosSet(D3DXVECTOR3 pPos)
{
	//�e�̔��˃t���O�ɂ���ď������ω�
	if (BulletShotFlag == true)
	{
		//true�Ȃ牜�ֈړ�
		BulletPos.z += BulletMoveSpeed;
	}
	else
	{
		//false�Ȃ�ʒu���X�V
		BulletPos = pPos;
	}
}