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

	//正面	
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
	//敵の描画
	for (int z = 0; z < 3; z++)
	{
		for (int x = 0; x < 10; x++)
		{
			D3DXMatrixTranslation(&mat_transform, EnemyPos[x + z * 10].x, 0.0f, EnemyPos[x + z * 10].z);		//座標
			D3DXMatrixScaling(&mat_scale, 8.0f, 8.0f, 8.0f);				//拡大
			D3DXMatrixRotationYawPitchRoll(&mat_rotate, 0.0f, 0.0f, 0.0f);	//回転	

			if (EnemyAliveFlag[x + z * 10] == true)
			{
				EnemyModel[z].Draw(mat_transform, mat_scale, mat_rotate);
			}
		}
	}

	DestroyEffectDraw();

	//敵の当たり判定の位置を描画
	//デバッグ用に使うので普段はコメントアウトしておく
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
			//敵が自機に向かって移動
			EnemyPos[i].z -= EnemyMoveSpeed;
			enemyObb[i].UpdateInfo(EnemyPos[i], forward, right, up);
		}
	}

	//敵が全て倒されたかの処理を行う
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

	//敵が全て倒されれば敵を再度出現
	//関数を呼んで位置やフラグを初期状態にする
	if (EnemyOllDestroy == true)
	{
		EnemyReset();
	}

	DestroyEffectSet();
}

//当たり判定を処理する関数
//obbを衝突相手にして使う
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
		//フラグがtrueなら弾と敵が衝突したことになるので
		//エフェクトが再生されるようにする
		if (destroyEffect[i].used == true)
		{
			destroyEffect[i].pos.x += cos(destroyEffect[i].angle.x)*destroyEffect[i].speed;
			destroyEffect[i].pos.y += sin(destroyEffect[i].angle.y)*destroyEffect[i].speed;
			destroyEffect[i].pos.z += sin(destroyEffect[i].angle.z)*destroyEffect[i].speed;
			destroyEffect[i].count++;
		}

		//カウントが60を超えるとフラグをfalseにして
		//カウントも0にしておく
		if (destroyEffect[i].count > 60)
		{
			destroyEffect[i].used = false;
			destroyEffect[i].count = 0;
		}
	}
}

//敵が指定した位置まで到達したらフラグを返す
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