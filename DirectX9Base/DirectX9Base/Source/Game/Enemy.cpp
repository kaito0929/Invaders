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
		angle[i].x = angle[i].z = 1.0f * i;
		angle[i].y = 0.0f;

		angleTest[i].x = sin(angle[i].x);
		angleTest[i].z = cos(angle[i].z);
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
			D3DXMatrixRotationYawPitchRoll(&mat_rotate, -angleTest[x + z * 10].x, 0.0f, 0.0f);	//��]	

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
		angleTest[i].x = sin(angle[i].x);
		angleTest[i].z = cos(angle[i].z);

		if (EnemyAliveFlag[i] == true)
		{
			//�G�����@�Ɍ������Ĉړ�
			EnemyPos[i] += angleTest[i] * EnemyMoveSpeed;
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
			EnemyPos[x + z * 10].x = 0.0f + sin(angle[x + z * 10].x)*30.0f;

			//�G��z���W��ݒ�
			//x���W�Ɠ����悤��20f�����炵�ĕ`��
			EnemyPos[x + z * 10].z = 150.0f + cos(angle[x + z * 10].z)*30.0f;

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