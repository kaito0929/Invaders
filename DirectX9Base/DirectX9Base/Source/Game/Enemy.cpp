#include "Enemy.h"

//�R���X�g���N�^
Enemy::Enemy()
{
	//���f���̃��[�h
	EnemyModel[0].Load(_T("Model/enemy0.x"));
	EnemyModel[1].Load(_T("Model/enemy1.x"));
	EnemyModel[2].Load(_T("Model/enemy2.x"));
	EnemyModel[3].Load(_T("Model/enemy3.x"));


	//�����蔻��̐ݒ�
	//�E��
	right.x = cos(0.0f);
	right.y = 0.0f;
	right.z = sin(0.0f);
	//��
	up.x = up.z = 0.0f;
	up.y = 1.0f;
	//����	
	forward.x = forward.y = cos(D3DX_PI / 2);
	forward.z = sin(D3DX_PI / 2);

	DestroyTex = new Texture;
	DestroyTex->Load("Texture/effect2.png");

	EnemyRadius[0] = 50.0f;
	EnemyRadius[1] = 35.0f;
	EnemyRadius[2] = 20.0f;

	se.Initialize();
}

//�f�X�g���N�^
Enemy::~Enemy()
{
	delete DestroyTex;
}

//=============================================
//��BlueEnemy�N���X��
//=============================================
//�R���X�g���N�^
BlueEnemy::BlueEnemy()
{

}

//�f�X�g���N�^
BlueEnemy::~BlueEnemy()
{
	delete[] vertex;
}

//������
void BlueEnemy::Initialize()
{
	degree = 0.0f;
	radian = 0.0f;

	for (int i = 0; i < BlueEnemyNum; i++)
	{
		enemyObb[i].SetLength(5, 10, 10);
		enemyObb[i].UpdateInfo(BlueEnemyPos[i], forward, right, up);

		//�p�x���烉�W�A�������߂�
		radian = PI / 180.0f * degree;

		BlueEnemyYaw[i].x = sin(radian);
		BlueEnemyYaw[i].y = 0.0f;
		BlueEnemyYaw[i].z = cos(radian);

		//�p�x��ς���
		degree += 180.0f;

		EnemyRadian[i] = radian;
	}


	for (int i = 0; i < DestroyEffectNum; i++)
	{
		for (int j = 0; j < BlueEnemyNum; j++)
		{
			destroyEffect[i][j].pos = BlueEnemyPos[j];
			destroyEffect[i][j].speed = 1.0f;
			destroyEffect[i][j].angle = D3DXVECTOR3(random.GetRandom_Int(1, 250), random.GetRandom_Int(1, 100), random.GetRandom_Int(100, 1100));
			destroyEffect[i][j].count = 0;
			destroyEffect[i][j].used = false;
		}
	}


	vertex = new VERTEX[DestroyEffectNum];

	BlueEnemyReset();

}

//�`��
void BlueEnemy::Draw()
{
	for (int i = 0; i < BlueEnemyNum; i++)
	{
		D3DXMatrixTranslation(&mat_transform, BlueEnemyPos[i].x, 0.0f, BlueEnemyPos[i].z);		//���W
		D3DXMatrixScaling(&mat_scale, 6.0f, 6.0f, 6.0f);				//�g��
		D3DXMatrixRotationYawPitchRoll(&mat_rotate, EnemyRadian[i], 0.0f, 0.0f);	//��]	

		if (BlueEnemyAliveFlag[i] == true)
		{
			EnemyModel[1].Draw(mat_transform, mat_scale, mat_rotate);
		}
	}
}

//�X�V
void BlueEnemy::Update()
{
	for (int i = 0; i < BlueEnemyNum; i++)
	{
		if (BlueEnemyAliveFlag[i] == true)
		{
			//�G�����@�Ɍ������Ĉړ�
			BlueEnemyPos[i] -= BlueEnemyYaw[i] * EnemyMoveSpeed;
			enemyObb[i].UpdateInfo(BlueEnemyPos[i], forward, right, up);
		}
	}

	for (int i = 0; i < BlueEnemyNum; i++)
	{
		if (BlueEnemyAliveFlag[i] == true)
		{
			BlueEnemyOllDown = false;
			break;
		}
		else
		{
			BlueEnemyOllDown = true;
		}
	}

	DestroyEffectSet();
}

bool BlueEnemy::BlueEnemyCollision(OrientedBoundingBox obb)
{
	for (int i = 0; i < BlueEnemyNum; i++)
	{
		//�G�̐����t���O��true�Ȃ�Ώ������s��
		if (BlueEnemyAliveFlag[i] == true)
		{
			//�Փ˔�����s��
			if (OrientedBoundingBox::Collision(obb, enemyObb[i]))
			{
				//����ƏՓ˂����G�̐����t���O��false�ɂ���
				//�`�悵�Ȃ��悤�ɂ���
				BlueEnemyAliveFlag[i] = false;

				se.ShotHitSEPlay();

				//�Փ˂������͓G���|���ꂽ�ꍇ�����Ȃ̂�
				//���ŃG�t�F�N�g��p��
				for (int j = 0; j < DestroyEffectNum; j++)
				{
					//�G�t�F�N�g�̍��W���Փ˂����G�̈ʒu��
					destroyEffect[j][i].pos = BlueEnemyPos[i];
					//�t���O��true�ɂ��Ďg�p����
					destroyEffect[j][i].used = true;
					////�\�����鎞�Ԃ�0�ɂ��ă��Z�b�g
					destroyEffect[j][i].count = 0;
				}

				return true;
			}
		}
	}

	return false;
}

void BlueEnemy::BlueEnemyReset()
{
	int count = 0;
	for (int i = 0; i < BlueEnemyNum; i++)
	{
		if (i > 0)
		{
			if (i % 2 == 0)
			{
				count++;
			}
		}

		//�G��x���W��ݒ�
		BlueEnemyPos[i].x = 0.0f - BlueEnemyYaw[i].x*EnemyRadius[count];

		//�G��z���W��ݒ�
		BlueEnemyPos[i].z = 170.0f - BlueEnemyYaw[i].z*EnemyRadius[count];

		//�G�̐����t���O��true��
		BlueEnemyAliveFlag[i] = true;

		BlueEnemyOllDown = false;
	}

}

//�G���|���ꂽ�ꍇ�̃G�t�F�N�g��`��
void BlueEnemy::DestroyEffectDraw()
{
	for (int i = 0; i < DestroyEffectNum; i++)
	{
		for (int j = 0; j < BlueEnemyNum; j++)
		{
			//�t���O��true�ɂȂ��Ă���Ε`��
			if (destroyEffect[i][j].used == true)
			{
				//�ʒu��ݒ�
				vertex[i].pos = destroyEffect[i][j].pos;
				//�傫���̐ݒ�
				vertex[i].size = 5.0f;
				//�F�̐ݒ�
				vertex[i].color = (DWORD)D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

				Direct3D::GetInstance()->DrawPointSprite(vertex, DestroyEffectNum, *DestroyTex);
			}
		}
	}
}

void BlueEnemy::DestroyEffectSet()
{
	for (int i = 0; i < DestroyEffectNum; i++)
	{
		for (int j = 0; j < BlueEnemyNum; j++)
		{
			//�t���O��true�Ȃ�e�ƓG���Փ˂������ƂɂȂ�̂�
			//�G�t�F�N�g���Đ������悤�ɂ���
			if (destroyEffect[i][j].used == true)
			{
				destroyEffect[i][j].pos.x += cos(destroyEffect[i][j].angle.x)*destroyEffect[i][j].speed;
				destroyEffect[i][j].pos.y += sin(destroyEffect[i][j].angle.y)*destroyEffect[i][j].speed;
				destroyEffect[i][j].pos.z += sin(destroyEffect[i][j].angle.z)*destroyEffect[i][j].speed;
				destroyEffect[i][j].count++;
			}

			//�J�E���g��60�𒴂���ƃt���O��false�ɂ���
			//�J�E���g��0�ɂ��Ă���
			if (destroyEffect[i][j].count >= 60)
			{
				destroyEffect[i][j].used = false;
				destroyEffect[i][j].count = 0;
			}
		}
	}
}

//=============================================
//��RedEnemy�N���X��
//=============================================
//�R���X�g���N�^
RedEnemy::RedEnemy()
{

}

//�f�X�g���N�^
RedEnemy::~RedEnemy()
{
	delete[] vertex;
}

//������
void RedEnemy::Initialize()
{
	degree = 90.0f;
	radian = 0;

	for (int i = 0; i < RedEnemyNum; i++)
	{
		enemyObb[i].SetLength(5, 10, 10);
		enemyObb[i].UpdateInfo(RedEnemyPos[i], forward, right, up);

		//�p�x���烉�W�A�������߂�
		radian = PI / 180 * degree;

		RedEnemyYaw[i].x = sin(radian);
		RedEnemyYaw[i].y = 0.0f;
		RedEnemyYaw[i].z = cos(radian);

		//�p�x��ς���
		degree += 180.0f;
	}


	for (int i = 0; i < DestroyEffectNum; i++)
	{
		for (int j = 0; j < RedEnemyNum; j++)
		{
			destroyEffect[i][j].pos = RedEnemyPos[j];
			destroyEffect[i][j].speed = 1.0f;
			destroyEffect[i][j].angle = D3DXVECTOR3(random.GetRandom_Int(1, 250), random.GetRandom_Int(1, 100), random.GetRandom_Int(100, 1100));
			destroyEffect[i][j].count = 0;
			destroyEffect[i][j].used = false;
		}
	}

	vertex = new VERTEX[DestroyEffectNum];

	RedEnemyReset();
}

//�`��
void RedEnemy::Draw()
{
	for (int i = 0; i < RedEnemyNum; i++)
	{
		D3DXMatrixTranslation(&mat_transform, RedEnemyPos[i].x, 0.0f, RedEnemyPos[i].z);		//���W
		D3DXMatrixScaling(&mat_scale, 6.0f, 6.0f, 6.0f);				//�g��
		D3DXMatrixRotationYawPitchRoll(&mat_rotate, -RedEnemyYaw[i].x, 0.0f, 0.0f);	//��]	

		if (RedEnemyAliveFlag[i] == true)
		{
			EnemyModel[2].Draw(mat_transform, mat_scale, mat_rotate);
		}
	}
}

//�X�V
void RedEnemy::Update()
{
	for (int i = 0; i < RedEnemyNum; i++)
	{
		if (RedEnemyAliveFlag[i] == true)
		{
			//�G�����@�Ɍ������Ĉړ�
			RedEnemyPos[i] += RedEnemyYaw[i] * RedEnemyMoveSpeed;
			enemyObb[i].UpdateInfo(RedEnemyPos[i], forward, right, up);
		}
	}


	for (int i = 0; i < RedEnemyNum; i++)
	{
		if (RedEnemyAliveFlag[i] == true)
		{
			RedEnemyOllDown = false;
			break;
		}
		else
		{
			RedEnemyOllDown = true;
		}
	}
	

	DestroyEffectSet();
}

bool RedEnemy::RedEnemyCollision(OrientedBoundingBox obb)
{
	for (int i = 0; i < RedEnemyNum; i++)
	{
		//�G�̐����t���O��true�Ȃ�Ώ������s��
		if (RedEnemyAliveFlag[i] == true)
		{
			//�Փ˔�����s��
			if (OrientedBoundingBox::Collision(obb, enemyObb[i]))
			{
				//����ƏՓ˂����G�̐����t���O��false�ɂ���
				//�`�悵�Ȃ��悤�ɂ���
				RedEnemyAliveFlag[i] = false;

				se.ShotHitSEPlay();

				//�Փ˂������͓G���|���ꂽ�ꍇ�����Ȃ̂�
				//���ŃG�t�F�N�g��p��
				for (int j = 0; j < DestroyEffectNum; j++)
				{
					//�G�t�F�N�g�̍��W���Փ˂����G�̈ʒu��
					destroyEffect[j][i].pos = RedEnemyPos[i];
					//�t���O��true�ɂ��Ďg�p����
					destroyEffect[j][i].used = true;
					////�\�����鎞�Ԃ�0�ɂ��ă��Z�b�g
					destroyEffect[j][i].count = 0;
				}

				return true;
			}
		}
	}

	return false;
}

void RedEnemy::RedEnemyReset()
{
	int count = 0;
	for (int i = 0; i < RedEnemyNum; i++)
	{
		if (i > 0)
		{
			if (i % 2)
			{
				count++;
			}
		}

		//�G��x���W��ݒ�
		RedEnemyPos[i].x = 0.0f + RedEnemyYaw[i].x*EnemyRadius[count];

		//�G��z���W��ݒ�
		RedEnemyPos[i].z = 170.0f + RedEnemyYaw[i].z*EnemyRadius[count];

		//�G�̐����t���O��true��
		RedEnemyAliveFlag[i] = true;

		RedEnemyOllDown = false;
	}
}

//�G���|���ꂽ�ꍇ�̃G�t�F�N�g��`��
void RedEnemy::DestroyEffectDraw()
{
	for (int i = 0; i < DestroyEffectNum; i++)
	{
		for (int j = 0; j < RedEnemyNum; j++)
		{
			//�t���O��true�ɂȂ��Ă���Ε`��
			if (destroyEffect[i][j].used == true)
			{
				//�ʒu��ݒ�
				vertex[i].pos = destroyEffect[i][j].pos;
				//�傫���̐ݒ�
				vertex[i].size = 5.0f;
				//�F�̐ݒ�
				vertex[i].color = (DWORD)D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

				Direct3D::GetInstance()->DrawPointSprite(vertex, DestroyEffectNum, *DestroyTex);
			}
		}
	}
}

void RedEnemy::DestroyEffectSet()
{
	for (int i = 0; i < DestroyEffectNum; i++)
	{
		for (int j = 0; j < RedEnemyNum; j++)
		{
			//�t���O��true�Ȃ�e�ƓG���Փ˂������ƂɂȂ�̂�
			//�G�t�F�N�g���Đ������悤�ɂ���
			if (destroyEffect[i][j].used == true)
			{
				destroyEffect[i][j].pos.x += cos(destroyEffect[i][j].angle.x)*destroyEffect[i][j].speed;
				destroyEffect[i][j].pos.y += sin(destroyEffect[i][j].angle.y)*destroyEffect[i][j].speed;
				destroyEffect[i][j].pos.z += sin(destroyEffect[i][j].angle.z)*destroyEffect[i][j].speed;
				destroyEffect[i][j].count++;
			}

			//�J�E���g��60�𒴂���ƃt���O��false�ɂ���
			//�J�E���g��0�ɂ��Ă���
			if (destroyEffect[i][j].count >= 60)
			{
				destroyEffect[i][j].used = false;
				destroyEffect[i][j].count = 0;
			}
		}
	}
}

//=============================================
//��GreenEnemy�N���X��
//=============================================
//�R���X�g���N�^
GreenEnemy::GreenEnemy()
{

}

//�f�X�g���N�^
GreenEnemy::~GreenEnemy()
{
	delete[] vertex;
}

//������
void GreenEnemy::Initialize()
{
	degree = 22.5f;
	radian = 0;

	for (int i = 0; i < GreenEnemyNum; i++)
	{
		enemyObb[i].SetLength(5, 10, 10);
		enemyObb[i].UpdateInfo(GreenEnemyPos[i], forward, right, up);

		//�p�x���烉�W�A�������߂�
		radian = PI / 180 * degree;

		GreenEnemyYaw[i].x = sin(radian);
		GreenEnemyYaw[i].y = 0.0f;
		GreenEnemyYaw[i].z = cos(radian);

		//�p�x��ς���
		degree += 45.0f;

		EnemyRadian[i] = radian;
	}

	for (int i = 0; i < DestroyEffectNum; i++)
	{
		for (int j = 0; j < GreenEnemyNum; j++)
		{
			destroyEffect[i][j].pos = GreenEnemyPos[j];
			destroyEffect[i][j].speed = 1.0f;
			destroyEffect[i][j].angle = D3DXVECTOR3(random.GetRandom_Int(1, 250), random.GetRandom_Int(1, 100), random.GetRandom_Int(100, 1100));
			destroyEffect[i][j].count = 0;
			destroyEffect[i][j].used = false;
		}
	}

	vertex = new VERTEX[DestroyEffectNum];

	EnemyBullet.Load(_T("Model/EnemyBullet.x"));

	right.x = cos(0);
	right.y = 0;
	right.z = sin(0);

	up.x = up.z = 0;
	up.y = 1;

	//����	
	forward.x = forward.y = cos(D3DX_PI / 2);
	forward.z = sin(D3DX_PI / 2);

	for (int i = 0; i < GreenEnemyNum; i++)
	{
		bulletObb[i].SetLength(10, 10, 10);

		bulletObb[i].UpdateInfo(BulletPos[i], forward, right, up);

		GreenEnemyShotFlag[i] = false;
	}




	ShotCount = 0;
	ShotFrame = 0;

	BulletFiredFlag = false;

	Wave = 0;

	GreenEnemyReset();
}

//�`��
void GreenEnemy::Draw()
{
	
	D3DXVECTOR3 scale;

	scale.x = 6.0f + sin(Wave)*1.0f;
	scale.y= 6.0f + cos(Wave)*1.0f;
	scale.z = 6.0f;

	for (int i = 0; i < GreenEnemyNum; i++)
	{

		//�ΐF�̓G�̕`��ݒ�
		D3DXMatrixTranslation(&mat_transform, GreenEnemyPos[i].x, 0.0f, GreenEnemyPos[i].z);		//���W
		D3DXMatrixScaling(&mat_scale, scale.x, scale.y, scale.z);				//�g��
		D3DXMatrixRotationYawPitchRoll(&mat_rotate, EnemyRadian[i], 0.0f, 0.0f);	//��]	

		if (GreenEnemyAliveFlag[i] == true)
		{
			EnemyModel[0].Draw(mat_transform, mat_scale, mat_rotate);
		}


		//�ΐF�̓G���甭�˂����e
		D3DXMatrixTranslation(&mat_bulletTransform, BulletPos[i].x, 0.0f, BulletPos[i].z);		//���W
		D3DXMatrixScaling(&mat_bulletScale, 0.1f, 0.1f, 0.1f);				//�g��
		D3DXMatrixRotationYawPitchRoll(&mat_bulletRotate, -GreenEnemyYaw[i].x, 0.0f, 0.0f);	//��]	

		if (GreenEnemyShotFlag[i] == true)
		{
			EnemyBullet.Draw(mat_bulletTransform, mat_bulletScale, mat_bulletRotate);
		}
	}
	

}

//�X�V
void GreenEnemy::Update()
{
	for (int i = 0; i < GreenEnemyNum; i++)
	{
		if (GreenEnemyAliveFlag[i] == true)
		{
			//�G�����@�Ɍ������Ĉړ�
			GreenEnemyPos[i] -= GreenEnemyYaw[i] * EnemyMoveSpeed;
			enemyObb[i].UpdateInfo(GreenEnemyPos[i], forward, right, up);
		}

		bulletObb[i].UpdateInfo(BulletPos[i], forward, right, up);
	}

	//�G���S�ł������̃t���O���擾
	for (int i = 0; i < GreenEnemyNum; i++)
	{
		if (GreenEnemyAliveFlag[i] == true)
		{
			GreenEnemyOllDown = false;
			break;
		}
		else
		{
			GreenEnemyOllDown = true;
		}
	}

	if (ShotCount < BulletShotTiming && BulletFiredFlag == false)
	{
		// �G��g�ł�����
		Wave += 0.1f;
	}

	EnemyBulletSet();
	EnemyBulletShot();
	DestroyEffectSet();
}

bool GreenEnemy::GreenEnemyCollision(OrientedBoundingBox obb)
{
	for (int i = 0; i < GreenEnemyNum; i++)
	{
		//�G�̐����t���O��true�Ȃ�Ώ������s��
		if (GreenEnemyAliveFlag[i] == true)
		{
			//�Փ˔�����s��
			if (OrientedBoundingBox::Collision(obb, enemyObb[i]))
			{
				//����ƏՓ˂����G�̐����t���O��false�ɂ���
				//�`�悵�Ȃ��悤�ɂ���
				GreenEnemyAliveFlag[i] = false;

				se.ShotHitSEPlay();

				//�Փ˂������͓G���|���ꂽ�ꍇ�����Ȃ̂�
				//���ŃG�t�F�N�g��p��
				for (int j = 0; j < DestroyEffectNum; j++)
				{
					//�G�t�F�N�g�̍��W���Փ˂����G�̈ʒu��
					destroyEffect[j][i].pos = GreenEnemyPos[i];
					//�t���O��true�ɂ��Ďg�p����
					destroyEffect[j][i].used = true;
					////�\�����鎞�Ԃ�0�ɂ��ă��Z�b�g
					destroyEffect[j][i].count = 0;
				}
				return true;
			}
		}
	}

	return false;
}

void GreenEnemy::GreenEnemyReset()
{
	int count = 0;
	for (int i = 0; i < GreenEnemyNum; i++)
	{
		if (i > 0)
		{
			if (i % 8 == 0)
			{
				count++;
			}
		}

		//�G��x���W��ݒ�
		//���@���痣�ꂽ�ʒu�ɂȂ�悤�ɂ��Ă���
		//�`�悷��悤�ɂ��Ă���
		GreenEnemyPos[i].x = 0.0f - GreenEnemyYaw[i].x*EnemyRadius[count];

		//�G��z���W��ݒ�
		GreenEnemyPos[i].z = 170.0f - GreenEnemyYaw[i].z*EnemyRadius[count];

		//�G�̐����t���O��true��
		GreenEnemyAliveFlag[i] = true;

		GreenEnemyOllDown = false;

		GreenEnemyShotFlag[i] = false;
	}

	ShotCount = 0;
	ShotFrame = 0;
	BulletFiredFlag = false;
	Wave = 0.0f;
}

//�G���|���ꂽ�ꍇ�̃G�t�F�N�g��`��
void GreenEnemy::DestroyEffectDraw()
{
	for (int i = 0; i < DestroyEffectNum; i++)
	{
		for (int j = 0; j < GreenEnemyNum; j++)
		{
			//�t���O��true�ɂȂ��Ă���Ε`��
			if (destroyEffect[i][j].used == true)
			{
				//�ʒu��ݒ�
				vertex[i].pos = destroyEffect[i][j].pos;
				//�傫���̐ݒ�
				vertex[i].size = 5.0f;
				//�F�̐ݒ�
				vertex[i].color = (DWORD)D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

				Direct3D::GetInstance()->DrawPointSprite(vertex, DestroyEffectNum, *DestroyTex);
			}
		}
	}
}

void GreenEnemy::DestroyEffectSet()
{
	for (int i = 0; i < DestroyEffectNum; i++)
	{
		for (int j = 0; j < GreenEnemyNum; j++)
		{
			//�t���O��true�Ȃ�e�ƓG���Փ˂������ƂɂȂ�̂�
			//�G�t�F�N�g���Đ������悤�ɂ���
			if (destroyEffect[i][j].used == true)
			{
				destroyEffect[i][j].pos.x += cos(destroyEffect[i][j].angle.x)*destroyEffect[i][j].speed;
				destroyEffect[i][j].pos.y += sin(destroyEffect[i][j].angle.y)*destroyEffect[i][j].speed;
				destroyEffect[i][j].pos.z += sin(destroyEffect[i][j].angle.z)*destroyEffect[i][j].speed;
				destroyEffect[i][j].count++;
			}

			//�J�E���g��60�𒴂���ƃt���O��false�ɂ���
			//�J�E���g��0�ɂ��Ă���
			if (destroyEffect[i][j].count >= 60)
			{
				destroyEffect[i][j].used = false;
				destroyEffect[i][j].count = 0;
			}
		}
	}
}

//�G�̒e�̔��˂𐧌䂷��֐�
void GreenEnemy::EnemyBulletShot()
{
	//�e���˂̕b�����Ǘ�����t���[�������Z
	ShotFrame++;
	//�t���[����60�𒴂����ꍇ�A��b���o��
	if (ShotFrame >= 60)
	{
		//��b�o�����̂ŃJ�E���g��1���Z
		ShotCount++;
		//�t���[�������Z�b�g���čĂуJ�E���g
		ShotFrame = 0;
	}

	for (int i = 0; i < GreenEnemyNum; i++)
	{
		//�e�𔭎˂��Ă��Ȃ���ԂȂ�Ώ���
		if (GreenEnemyShotFlag[i] == false)
		{
			//�O�b�J�E���g����邲�Ƃɏ���
			if (ShotCount == BulletShotTiming && BulletFiredFlag == false)
			{
				//�t���O��true�ɂ��Ēe�𔭎˂�����
				if (GreenEnemyAliveFlag[i] == true)
				{
					GreenEnemyShotFlag[i] = true;
					Wave = 0.0f;
				}
			}
		}
		else
		{
			//�e�𔭎˂�����Ԃň�b�o�߂�����t���O��false�ɂ���
			if (ShotCount == BulletEndTiming)
			{
				GreenEnemyShotFlag[i] = false;
			}
		}
	}

	if (ShotCount == BulletShotTiming)
	{
		//��x�������˂����邽�߂ɔ��ˍς݂����f����t���O��
		//true�ɂ��Ă���
		BulletFiredFlag = true;
	}

	//�J�E���g�����Z�b�g
	if (ShotCount == BulletEndTiming)
	{
		ShotCount = 0;
		BulletFiredFlag = false;
	}

}

//�G�̔��˂���e�̈ʒu��ݒ肷��֐�
void GreenEnemy::EnemyBulletSet()
{
	for (int i = 0; i < GreenEnemyNum; i++)
	{
		//�G���e�𔭎˂��Ă���ꍇ�ɏ���
		if (GreenEnemyShotFlag[i] == true)
		{
			//�G�������Ă�������Ɍ������Đi�ނ悤�ɂ���
			BulletPos[i] -= BulletAngle[i] * 3.0f;
		}
		//�G���e�𔭎˂��Ă��Ȃ����
		else
		{
			//�G�̈ʒu�Ɗp�x���擾����
			BulletPos[i] = GreenEnemyPos[i];
			BulletAngle[i] = GreenEnemyYaw[i];
		}
	}
}


//�ΐF�̓G�����˂���e�Ƃ̏Փ˔������������֐�
bool GreenEnemy::EnemyBulletCollision(OrientedBoundingBox obb)
{
	for (int i = 0; i < GreenEnemyNum; i++)
	{
		//�e�̐����t���O��true�Ȃ�Ώ������s��
		if (GreenEnemyShotFlag[i] == true)
		{
			//�Փ˔�����s��
			if (OrientedBoundingBox::Collision(bulletObb[i],obb ))
			{
				//����ƏՓ˂������ɒe�̔��˂̃t���O��true�ɂ���
				//�`�悵�Ȃ��悤�ɂ���
				GreenEnemyShotFlag[i] = false;
				return true;
			}
		}
	}

	return false;
}


//=============================================
//��PurpleEnemy�N���X��
//=============================================
//�R���X�g���N�^
PurpleEnemy::PurpleEnemy()
{

}

//�f�X�g���N�^
PurpleEnemy::~PurpleEnemy()
{
	delete[] vertex;
}

//������
void PurpleEnemy::Initialize()
{
	degree = 45.0f;
	radian = 0;

	for (int i = 0; i < PurpleEnemyNum; i++)
	{
		enemyObb[i].SetLength(5, 10, 10);
		enemyObb[i].UpdateInfo(PurpleEnemyPos[i], forward, right, up);

		//�p�x���烉�W�A�������߂�
		radian = PI / 180 * degree;

		PurpleEnemyYaw[i].x = sin(radian);
		PurpleEnemyYaw[i].y = 0.0f;
		PurpleEnemyYaw[i].z = cos(radian);

		//�p�x��ς���
		degree += 90.0f;

		EnemyRadian[i] = radian;
	}

	for (int i = 0; i < DestroyEffectNum; i++)
	{
		for (int j = 0; j < PurpleEnemyNum; j++)
		{
			destroyEffect[i][j].pos = PurpleEnemyPos[j];
			destroyEffect[i][j].speed = 1.0f;
			destroyEffect[i][j].angle = D3DXVECTOR3(random.GetRandom_Int(1, 250), random.GetRandom_Int(1, 100), random.GetRandom_Int(100, 1100));
			destroyEffect[i][j].count = 0;
			destroyEffect[i][j].used = false;
		}
	}

	vertex = new VERTEX[DestroyEffectNum];

	PurpleEnemyReset();
}

//�`��
void PurpleEnemy::Draw()
{
	for (int i = 0; i < PurpleEnemyNum; i++)
	{
		D3DXMatrixTranslation(&mat_transform, PurpleEnemyPos[i].x, 0.0f, PurpleEnemyPos[i].z);		//���W
		D3DXMatrixScaling(&mat_scale, 6.0f, 6.0f,6.0f);				//�g��
		D3DXMatrixRotationYawPitchRoll(&mat_rotate, EnemyRadian[i], 0.0f, 0.0f);	//��]	

		if (PurpleEnemyAliveFlag[i] == true)
		{
			EnemyModel[3].Draw(mat_transform, mat_scale, mat_rotate);
		}
	}
}

//�X�V
void PurpleEnemy::Update()
{
	for (int i = 0; i < PurpleEnemyNum; i++)
	{
		if (PurpleEnemyAliveFlag[i] == true)
		{
			//�G�����@�Ɍ������Ĉړ�
			PurpleEnemyPos[i] -= PurpleEnemyYaw[i] * EnemyMoveSpeed;
			enemyObb[i].UpdateInfo(PurpleEnemyPos[i], forward, right, up);
		}
	}


	for (int i = 0; i < PurpleEnemyNum; i++)
	{
		if (PurpleEnemyAliveFlag[i] == true)
		{
			PurpleEnemyOllDown = false;
			break;
		}
		else
		{
			PurpleEnemyOllDown = true;
		}
	}


	DestroyEffectSet();
}

//���F�̓G�̏Փ˔���
//���̓G�ƈ����HP������̂ŏ����͈قȂ��Ă���
bool PurpleEnemy::PurpleEnemyCollision(OrientedBoundingBox obb, bool *flag)
{
	for (int i = 0; i < PurpleEnemyNum; i++)
	{
		//�G�̐����t���O��true�Ȃ�Ώ������s��
		if (PurpleEnemyAliveFlag[i] == true)
		{
			//�Փ˔�����s��
			if (OrientedBoundingBox::Collision(obb, enemyObb[i]))
			{
				//�e�ƏՓ˂����G��HP�����炷
				HitPoint[i]--;
				//�e��`�悵�Ă���t���O��false��
				*flag = false;

				se.ShotHitSEPlay();
				

				//HP��0�ɂȂ�ΓG�̕`��t���O�������A�t���O��Ԃ�
				if (HitPoint[i] == 0)
				{
					//����ƏՓ˂����G�̐����t���O��false�ɂ���
					//�`�悵�Ȃ��悤�ɂ���
					PurpleEnemyAliveFlag[i] = false;

					//�Փ˂������͓G���|���ꂽ�ꍇ�����Ȃ̂�
					//���ŃG�t�F�N�g��p��
					for (int j = 0; j < DestroyEffectNum; j++)
					{
						//�G�t�F�N�g�̍��W���Փ˂����G�̈ʒu��
						destroyEffect[j][i].pos = PurpleEnemyPos[i];
						//�t���O��true�ɂ��Ďg�p����
						destroyEffect[j][i].used = true;
						////�\�����鎞�Ԃ�0�ɂ��ă��Z�b�g
						destroyEffect[j][i].count = 0;
					}

					return true;

				}
			}
		}
	}

	return false;
}

void PurpleEnemy::PurpleEnemyReset()
{
	int count = 0;
	for (int i = 0; i < PurpleEnemyNum; i++)
	{
		if (i > 0)
		{
			if (i % 4==0)
			{
				count++;
			}
		}

		//�G��x���W��ݒ�
		//���@���痣�ꂽ�ʒu�ɂȂ�悤�ɂ��Ă���
		//�`�悷��悤�ɂ��Ă���
		PurpleEnemyPos[i].x = 0.0f - PurpleEnemyYaw[i].x*EnemyRadius[count];

		//�G��z���W��ݒ�
		PurpleEnemyPos[i].z = 170.0f - PurpleEnemyYaw[i].z*EnemyRadius[count];

		//�G�̐����t���O��true��
		PurpleEnemyAliveFlag[i] = true;

		PurpleEnemyOllDown = false;

		HitPoint[i] = 2;
	}
}

//�G���|���ꂽ�ꍇ�̃G�t�F�N�g��`��
void PurpleEnemy::DestroyEffectDraw()
{
	for (int i = 0; i < DestroyEffectNum; i++)
	{
		for (int j = 0; j < PurpleEnemyNum; j++)
		{
			//�t���O��true�ɂȂ��Ă���Ε`��
			if (destroyEffect[i][j].used == true)
			{
				//�ʒu��ݒ�
				vertex[i].pos = destroyEffect[i][j].pos;
				//�傫���̐ݒ�
				vertex[i].size = 5.0f;
				//�F�̐ݒ�
				vertex[i].color = (DWORD)D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

				Direct3D::GetInstance()->DrawPointSprite(vertex, DestroyEffectNum, *DestroyTex);
			}
		}
	}
}

void PurpleEnemy::DestroyEffectSet()
{
	for (int i = 0; i < DestroyEffectNum; i++)
	{
		for (int j = 0; j < PurpleEnemyNum; j++)
		{
			//�t���O��true�Ȃ�e�ƓG���Փ˂������ƂɂȂ�̂�
			//�G�t�F�N�g���Đ������悤�ɂ���
			if (destroyEffect[i][j].used == true)
			{
				destroyEffect[i][j].pos.x += cos(destroyEffect[i][j].angle.x)*destroyEffect[i][j].speed;
				destroyEffect[i][j].pos.y += sin(destroyEffect[i][j].angle.y)*destroyEffect[i][j].speed;
				destroyEffect[i][j].pos.z += sin(destroyEffect[i][j].angle.z)*destroyEffect[i][j].speed;
				destroyEffect[i][j].count++;
			}

			//�J�E���g��60�𒴂���ƃt���O��false�ɂ���
			//�J�E���g��0�ɂ��Ă���
			if (destroyEffect[i][j].count >= 60)
			{
				destroyEffect[i][j].used = false;
				destroyEffect[i][j].count = 0;
			}
		}
	}
}