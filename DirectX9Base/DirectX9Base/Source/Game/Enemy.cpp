#include "Enemy.h"

Enemy::Enemy()
{

}

Enemy::~Enemy()
{
	delete DestroyTex;
	delete[] vertex;
}

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
	}


	EnemyReset();

	DestroyTex = new Texture;
	DestroyTex->Load("Texture/test.png");

	for (int i = 0; i < DestroyEffectNum; i++)
	{
		destroyEffect[i].pos = EnemyPos[0];
		destroyEffect[i].speed = 1.0f;
		destroyEffect[i].angle = D3DXVECTOR3(random.GetRandom_Int(1, 250), random.GetRandom_Int(1, 100), random.GetRandom_Int(100, 1100));
		destroyEffect[i].count = 0;
	}


	vertex = new VERTEX[DestroyEffectNum];

}

void Enemy::Draw()
{
	//�G�̕`��
	for (int z = 0; z < 3; z++)
	{
		for (int x = 0; x < 10; x++)
		{
			D3DXMatrixTranslation(&mat_transform, EnemyPos[x + z * 10].x, 0.0f, EnemyPos[x + z * 10].z);		//���W
			D3DXMatrixScaling(&mat_scale, 8.0f, 8.0f, 8.0f);				//�g��
			D3DXMatrixRotationYawPitchRoll(&mat_rotate, 0.0f, 0.0f, 0.0f);	//��]	

			if (EnemyAliveFlag[x + z * 10] == true)
			{
				EnemyModel[z].Draw(mat_transform, mat_scale, mat_rotate);
			}
		}
	}

	DestroyEffectDraw();

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
			EnemyPos[i].z -= EnemyMoveSpeed;
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
		if (EnemyAliveFlag[i] == true)
		{
			if (OrientedBoundingBox::Collision(obb, enemyObb[i]))
			{
				EnemyAliveFlag[i] = false;

				for (int j = 0; j < DestroyEffectNum; j++)
				{
					destroyEffect[j].pos = EnemyPos[i];
					destroyEffect[j].used = true;
					destroyEffect[j].count = 0;
				}
				return true;
			}
		}
	}

	return false;
}

void Enemy::EnemyReset()
{
	for (int z = 0; z < 3; z++)
	{
		for (int x = 0; x < 10; x++)
		{
			EnemyPos[x + z * 10].x = -90.0f + x * 20.0f;
			EnemyPos[x + z * 10].z = 150.0f + z * 20.0f;
			EnemyAliveFlag[x + z * 10] = true;
		}
	}

	EnemyOllDestroy = false;
}

void Enemy::DestroyEffectDraw()
{
	for (int i = 0; i < DestroyEffectNum; i++)
	{
		vertex[i].pos = destroyEffect[i].pos;
		vertex[i].size = 15.0f;
		vertex[i].color = (DWORD)D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

		if (destroyEffect[i].used == true)
		{
			Direct3D::GetInstance()->DrawPointSprite(vertex, DestroyEffectNum, *DestroyTex);
		}
	}
}

void Enemy::DestroyEffectSet()
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
			destroyEffect[i].count++;
		}

		//�J�E���g��60�𒴂���ƃt���O��false�ɂ���
		//�J�E���g��0�ɂ��Ă���
		if (destroyEffect[i].count > 60)
		{
			destroyEffect[i].used = false;
			destroyEffect[i].count = 0;
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