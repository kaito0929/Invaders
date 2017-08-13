#include "Enemy.h"

//�R���X�g���N�^
Enemy::Enemy()
{

}

//�f�X�g���N�^
Enemy::~Enemy()
{
	delete DestroyTex;
	delete[] vertex;
}

//������
void Enemy::Initialize()
{
	EnemyModel[0].Load(_T("Model/enemy0.x"));
	EnemyModel[1].Load(_T("Model/enemy1.x"));
	EnemyModel[2].Load(_T("Model/enemy2.x"));

	right.x = cos(0);
	right.y = 0;
	right.z = sin(0);

	up.x = up.z = 0;
	up.y = 1;

	//����	
	forward.x = forward.y = cos(D3DX_PI / 2);
	forward.z = sin(D3DX_PI / 2);

	for (int i = 0; i < EnemyNum; i++)
	{
		enemyObb[i].SetLength(5, 10, 10);
		enemyObb[i].UpdateInfo(EnemyPos[i], forward, right, up);
		angle[i].x = sin(1.0f * i);
		angle[i].z = cos(1.0f * i);
		angle[i].y = 0.0f;
	}



	EnemyReset();

	DestroyTex = new Texture;
	DestroyTex->Load("Texture/test.png");

	for (int i = 0; i < DestroyEffectNum; i++)
	{
		for (int j = 0; j < EnemyNum; j++)
		{
			destroyEffect[i][j].pos = EnemyPos[j];
			destroyEffect[i][j].speed = 1.0f;
			destroyEffect[i][j].angle = D3DXVECTOR3(random.GetRandom_Int(1, 250), random.GetRandom_Int(1, 100), random.GetRandom_Int(100, 1100));
			destroyEffect[i][j].count = 0;
			destroyEffect[i][j].used = false;
		}
	}


	vertex = new VERTEX[DestroyEffectNum];


}

//�`��
void Enemy::Draw()
{
	//�G�̕`��
	for (int z = 0; z < EnemyColumnNum; z++)
	{
		for (int x = 0; x < EnemyRowNum; x++)
		{
			D3DXMatrixTranslation(&mat_transform, EnemyPos[x + z * 10].x, 0.0f, EnemyPos[x + z * 10].z);		//���W
			D3DXMatrixScaling(&mat_scale, 8.0f, 8.0f, 8.0f);				//�g��
			D3DXMatrixRotationYawPitchRoll(&mat_rotate, -angle[x + z * 10].x, 0.0f, 0.0f);	//��]	

			if (EnemyAliveFlag[x + z * 10] == true)
			{
				EnemyModel[z].Draw(mat_transform, mat_scale, mat_rotate);
			}
		}
	}


	//�G�̓����蔻��̈ʒu��`��
	//�f�o�b�O�p�Ɏg���̂ŕ��i�̓R�����g�A�E�g���Ă���
	/*for (int i = 0; i < EnemyNum; i++)
	{
		enemyObb[i].DrawLine();
	}*/
}

void Enemy::Update()
{
	for (int i = 0; i < EnemyNum; i++)
	{
		if (EnemyAliveFlag[i] == true)
		{
			//�G�����@�Ɍ������Ĉړ�
			EnemyPos[i] += angle[i] * EnemyMoveSpeed;
			//EnemyPos[i].z += cos(angle[i].z) * EnemyMoveSpeed;
			enemyObb[i].UpdateInfo(EnemyPos[i], forward, right, up);
		}
	}

	//�G���S�ē|���ꂽ���̏������s��
	for (int i = 0; i < EnemyNum; i++)
	{
		if (EnemyAliveFlag[i] == false)
		{
			EnemyOllDestroy = true;
		}
		else
		{
			EnemyOllDestroy = false;
			break;
		}
	}

	//�G���S�ē|�����ΓG���ēx�o��
	//�֐����Ă�ňʒu��t���O��������Ԃɂ���
	if (EnemyOllDestroy == true)
	{
		EnemyReset();
	}

	

	DestroyEffectSet();
}

//�����蔻�����������֐�
//obb���Փˑ���ɂ��Ďg��
bool Enemy::EnemyCollision(OrientedBoundingBox obb)
{
	for (int i = 0; i < EnemyNum; i++)
	{
		//�G�̐����t���O��true�Ȃ�Ώ������s��
		if (EnemyAliveFlag[i] == true)
		{
			//�Փ˔�����s��
			if (OrientedBoundingBox::Collision(obb, enemyObb[i]))
			{
				//����ƏՓ˂����G�̐����t���O��false�ɂ���
				//�`�悵�Ȃ��悤�ɂ���
				EnemyAliveFlag[i] = false;

				//�Փ˂������͓G���|���ꂽ�ꍇ�����Ȃ̂�
				//���ŃG�t�F�N�g��p��
				for (int j = 0; j < DestroyEffectNum; j++)
				{
					//�G�t�F�N�g�̍��W���Փ˂����G�̈ʒu��
					destroyEffect[j][i].pos = EnemyPos[i];
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

//�G�̈ʒu�␶���t���O������������֐�
//�G���S�ł����ꍇ�Ƀ��|�b�v������ꍇ�Ɏg�p����
void Enemy::EnemyReset()
{
	for (int z = 0; z < EnemyColumnNum; z++)
	{
		for (int x = 0; x < EnemyRowNum; x++)
		{
			//�G��x���W��ݒ�
			//���[��-90�ɂ��Ă����āA��������20f�����炵��
			//���@���痣�ꂽ�ʒu�ɂȂ�悤�ɂ��Ă���
			//�`�悷��悤�ɂ��Ă���
			EnemyPos[x + z * 10].x = 0.0f + angle[x + z * 10].x*30.0f;

			//�G��z���W��ݒ�
			//x���W�Ɠ����悤��20f�����炵�ĕ`��
			EnemyPos[x + z * 10].z = 150.0f + angle[x + z * 10].z*30.0f;

			//�G�̐����t���O��true��
			EnemyAliveFlag[x + z * 10] = true;
		}
	}

	//�G���S�ē|���ꂽ�ꍇ�̃t���O��false�ɂ���
	//�Q�[�����ĊJ�ł���悤�ɂ���
	EnemyOllDestroy = false;
}

//�G���|���ꂽ�ꍇ�̃G�t�F�N�g��`��
void Enemy::DestroyEffectDraw()
{
	for (int i = 0; i < DestroyEffectNum; i++)
	{
		for (int j = 0; j < EnemyNum; j++)
		{
			//�t���O��true�ɂȂ��Ă���Ε`��
			if (destroyEffect[i][j].used == true)
			{
				//�ʒu��ݒ�
				vertex[i].pos = destroyEffect[i][j].pos;
				//�傫���̐ݒ�
				vertex[i].size = 15.0f;
				//�F�̐ݒ�
				vertex[i].color = (DWORD)D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

				Direct3D::GetInstance()->DrawPointSprite(vertex, DestroyEffectNum, *DestroyTex);
			}
		}
	}
}

void Enemy::DestroyEffectSet()
{
	for (int i = 0; i < DestroyEffectNum; i++)
	{
		for (int j = 0; j < EnemyNum; j++)
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

//�G���w�肵���ʒu�܂œ��B������t���O��Ԃ�
bool Enemy::EnemyBorderlineReaching()
{
	for (int i = 0; i < EnemyNum; i++)
	{
		if (EnemyPos[i].z <= EnemyBorderlinePosZ)
		{
			return true;
		}
	}

	return false;
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

}

//������
void BlueEnemy::Initialize()
{
	//���f���̃��[�h
	BlueEnemyModel.Load(_T("Model/enemy1.x"));

	//�����蔻��̐ݒ�
	//�E��
	right.x = cos(0);
	right.y = 0;
	right.z = sin(0);
	//��
	up.x = up.z = 0;
	up.y = 1;
	//����	
	forward.x = forward.y = cos(D3DX_PI / 2);
	forward.z = sin(D3DX_PI / 2);

	degree = 0;
	radian = 0;

	for (int i = 0; i < BlueEnemyNum; i++)
	{
		enemyObb[i].SetLength(5, 10, 10);
		enemyObb[i].UpdateInfo(BlueEnemyPos[i], forward, right, up);

		//�p�x���烉�W�A�������߂�
		radian = PI / 180 * degree;

		BlueEnemyYaw[i].x = sin(radian);
		BlueEnemyYaw[i].y = 0.0f;
		BlueEnemyYaw[i].z = cos(radian);

		//�p�x��ς���
		degree += 180.0f;
	}

	BlueEnemyReset();

}

//�`��
void BlueEnemy::Draw()
{
	for (int x = 0; x < BlueEnemyNum; x++)
	{
		D3DXMatrixTranslation(&mat_transform, BlueEnemyPos[x].x, 0.0f, BlueEnemyPos[x].z);		//���W
		D3DXMatrixScaling(&mat_scale, 8.0f, 8.0f, 8.0f);				//�g��
		D3DXMatrixRotationYawPitchRoll(&mat_rotate, -BlueEnemyYaw[x].x, 0.0f, 0.0f);	//��]	

		if (BlueEnemyAliveFlag[x] == true)
		{
			BlueEnemyModel.Draw(mat_transform, mat_scale, mat_rotate);
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
			BlueEnemyPos[i] += BlueEnemyYaw[i] * EnemyMoveSpeed;
			enemyObb[i].UpdateInfo(BlueEnemyPos[i], forward, right, up);
		}
	}
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

				////�Փ˂������͓G���|���ꂽ�ꍇ�����Ȃ̂�
				////���ŃG�t�F�N�g��p��
				//for (int j = 0; j < DestroyEffectNum; j++)
				//{
				//	//�G�t�F�N�g�̍��W���Փ˂����G�̈ʒu��
				//	destroyEffect[j][i].pos = BlueEnemyPos[i];
				//	//�t���O��true�ɂ��Ďg�p����
				//	destroyEffect[j][i].used = true;
				//	////�\�����鎞�Ԃ�0�ɂ��ă��Z�b�g
				//	destroyEffect[j][i].count = 0;
				//}

				return true;
			}
		}
	}

	return false;
}

void BlueEnemy::BlueEnemyReset()
{
	for (int x = 0; x < BlueEnemyNum; x++)
	{
		//�G��x���W��ݒ�
		//���[��-90�ɂ��Ă����āA��������20f�����炵��
		//���@���痣�ꂽ�ʒu�ɂȂ�悤�ɂ��Ă���
		//�`�悷��悤�ɂ��Ă���
		BlueEnemyPos[x].x = 0.0f + BlueEnemyYaw[x].x*EnemyRadius

		//�G��z���W��ݒ�
		//x���W�Ɠ����悤��20f�����炵�ĕ`��
		BlueEnemyPos[x].z = 150.0f + BlueEnemyYaw[x].z*EnemyRadius

		//�G�̐����t���O��true��
		BlueEnemyAliveFlag[x] = true;
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

}

//������
void RedEnemy::Initialize()
{
	//���f���̃��[�h
	RedEnemyModel.Load(_T("Model/enemy2.x"));

	//�����蔻��̐ݒ�
	//�E��
	right.x = cos(0);
	right.y = 0;
	right.z = sin(0);
	//��
	up.x = up.z = 0;
	up.y = 1;
	//����	
	forward.x = forward.y = cos(D3DX_PI / 2);
	forward.z = sin(D3DX_PI / 2);

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

	RedEnemyReset();
}

//�`��
void RedEnemy::Draw()
{
	for (int x = 0; x < RedEnemyNum; x++)
	{
		D3DXMatrixTranslation(&mat_transform, RedEnemyPos[x].x, 0.0f, RedEnemyPos[x].z);		//���W
		D3DXMatrixScaling(&mat_scale, 8.0f, 8.0f, 8.0f);				//�g��
		D3DXMatrixRotationYawPitchRoll(&mat_rotate, -RedEnemyYaw[x].x, 0.0f, 0.0f);	//��]	

		if (RedEnemyAliveFlag[x] == true)
		{
			RedEnemyModel.Draw(mat_transform, mat_scale, mat_rotate);
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

				////�Փ˂������͓G���|���ꂽ�ꍇ�����Ȃ̂�
				////���ŃG�t�F�N�g��p��
				//for (int j = 0; j < DestroyEffectNum; j++)
				//{
				//	//�G�t�F�N�g�̍��W���Փ˂����G�̈ʒu��
				//	destroyEffect[j][i].pos = BlueEnemyPos[i];
				//	//�t���O��true�ɂ��Ďg�p����
				//	destroyEffect[j][i].used = true;
				//	////�\�����鎞�Ԃ�0�ɂ��ă��Z�b�g
				//	destroyEffect[j][i].count = 0;
				//}

				return true;
			}
		}
	}

	return false;
}

void RedEnemy::RedEnemyReset()
{
	for (int x = 0; x < RedEnemyNum; x++)
	{
		//�G��x���W��ݒ�
		//���[��-90�ɂ��Ă����āA��������20f�����炵��
		//���@���痣�ꂽ�ʒu�ɂȂ�悤�ɂ��Ă���
		//�`�悷��悤�ɂ��Ă���
		RedEnemyPos[x].x = 0.0f + RedEnemyYaw[x].x*EnemyRadius

		//�G��z���W��ݒ�
		//x���W�Ɠ����悤��20f�����炵�ĕ`��
		RedEnemyPos[x].z = 150.0f + RedEnemyYaw[x].z*EnemyRadius

		//�G�̐����t���O��true��
		RedEnemyAliveFlag[x] = true;
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

}

//������
void GreenEnemy::Initialize()
{
	//���f���̃��[�h
	GreenEnemyModel.Load(_T("Model/enemy0.x"));

	//�����蔻��̐ݒ�
	//�E��
	right.x = cos(0);
	right.y = 0;
	right.z = sin(0);
	//��
	up.x = up.z = 0;
	up.y = 1;
	//����	
	forward.x = forward.y = cos(D3DX_PI / 2);
	forward.z = sin(D3DX_PI / 2);

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
		degree += 22.5f;

		if (degree == 0.0f || degree == 90.0f || degree == 180.0f || degree == 270.0f)
		{
			//�p�x��ς���
			degree += 22.5f;
		}
	}

	GreenEnemyReset();
}

//�`��
void GreenEnemy::Draw()
{
	for (int x = 0; x < GreenEnemyNum; x++)
	{
		D3DXMatrixTranslation(&mat_transform, GreenEnemyPos[x].x, 0.0f, GreenEnemyPos[x].z);		//���W
		D3DXMatrixScaling(&mat_scale, 8.0f, 8.0f, 8.0f);				//�g��
		D3DXMatrixRotationYawPitchRoll(&mat_rotate, -GreenEnemyYaw[x].x, 0.0f, 0.0f);	//��]	

		if (GreenEnemyAliveFlag[x] == true)
		{
			GreenEnemyModel.Draw(mat_transform, mat_scale, mat_rotate);
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
			GreenEnemyPos[i] += GreenEnemyYaw[i] * EnemyMoveSpeed;
			enemyObb[i].UpdateInfo(GreenEnemyPos[i], forward, right, up);
		}
	}
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

				////�Փ˂������͓G���|���ꂽ�ꍇ�����Ȃ̂�
				////���ŃG�t�F�N�g��p��
				//for (int j = 0; j < DestroyEffectNum; j++)
				//{
				//	//�G�t�F�N�g�̍��W���Փ˂����G�̈ʒu��
				//	destroyEffect[j][i].pos = BlueEnemyPos[i];
				//	//�t���O��true�ɂ��Ďg�p����
				//	destroyEffect[j][i].used = true;
				//	////�\�����鎞�Ԃ�0�ɂ��ă��Z�b�g
				//	destroyEffect[j][i].count = 0;
				//}

				return true;
			}
		}
	}

	return false;
}

void GreenEnemy::GreenEnemyReset()
{
	for (int x = 0; x < GreenEnemyNum; x++)
	{
		//�G��x���W��ݒ�
		//���@���痣�ꂽ�ʒu�ɂȂ�悤�ɂ��Ă���
		//�`�悷��悤�ɂ��Ă���
		GreenEnemyPos[x].x = 0.0f + GreenEnemyYaw[x].x*EnemyRadius

		//�G��z���W��ݒ�
		GreenEnemyPos[x].z = 150.0f + GreenEnemyYaw[x].z*EnemyRadius

		//�G�̐����t���O��true��
		GreenEnemyAliveFlag[x] = true;

		HitPoint = 0;
	}
}