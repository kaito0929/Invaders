#include "Enemy.h"

//コンストラクタ
Enemy::Enemy()
{
	//モデルのロード
	EnemyModel[0].Load(_T("Model/enemy0.x"));
	EnemyModel[1].Load(_T("Model/enemy1.x"));
	EnemyModel[2].Load(_T("Model/enemy2.x"));
	EnemyModel[3].Load(_T("Model/enemy3.x"));


	//当たり判定の設定
	//右側
	right.x = cos(0.0f);
	right.y = 0.0f;
	right.z = sin(0.0f);
	//上
	up.x = up.z = 0.0f;
	up.y = 1.0f;
	//正面	
	forward.x = forward.y = cos(D3DX_PI / 2);
	forward.z = sin(D3DX_PI / 2);

	DestroyTex = new Texture;
	DestroyTex->Load("Texture/effect2.png");

	EnemyRadius[0] = 50.0f;
	EnemyRadius[1] = 35.0f;
	EnemyRadius[2] = 20.0f;

	se.Initialize();
}

//デストラクタ
Enemy::~Enemy()
{
	delete DestroyTex;
}

//=============================================
//■BlueEnemyクラス■
//=============================================
//コンストラクタ
BlueEnemy::BlueEnemy()
{

}

//デストラクタ
BlueEnemy::~BlueEnemy()
{
	delete[] vertex;
}

//初期化
void BlueEnemy::Initialize()
{
	degree = 0.0f;
	radian = 0.0f;

	for (int i = 0; i < BlueEnemyNum; i++)
	{
		enemyObb[i].SetLength(5, 10, 10);
		enemyObb[i].UpdateInfo(BlueEnemyPos[i], forward, right, up);

		//角度からラジアンを求める
		radian = PI / 180.0f * degree;

		BlueEnemyYaw[i].x = sin(radian);
		BlueEnemyYaw[i].y = 0.0f;
		BlueEnemyYaw[i].z = cos(radian);

		//角度を変える
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

//描画
void BlueEnemy::Draw()
{
	for (int i = 0; i < BlueEnemyNum; i++)
	{
		D3DXMatrixTranslation(&mat_transform, BlueEnemyPos[i].x, 0.0f, BlueEnemyPos[i].z);		//座標
		D3DXMatrixScaling(&mat_scale, 6.0f, 6.0f, 6.0f);				//拡大
		D3DXMatrixRotationYawPitchRoll(&mat_rotate, EnemyRadian[i], 0.0f, 0.0f);	//回転	

		if (BlueEnemyAliveFlag[i] == true)
		{
			EnemyModel[1].Draw(mat_transform, mat_scale, mat_rotate);
		}
	}
}

//更新
void BlueEnemy::Update()
{
	for (int i = 0; i < BlueEnemyNum; i++)
	{
		if (BlueEnemyAliveFlag[i] == true)
		{
			//敵が自機に向かって移動
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
		//敵の生存フラグがtrueならば処理を行う
		if (BlueEnemyAliveFlag[i] == true)
		{
			//衝突判定を行う
			if (OrientedBoundingBox::Collision(obb, enemyObb[i]))
			{
				//相手と衝突した敵の生存フラグをfalseにして
				//描画しないようにする
				BlueEnemyAliveFlag[i] = false;

				se.ShotHitSEPlay();

				//衝突した時は敵が倒された場合だけなので
				//消滅エフェクトを用意
				for (int j = 0; j < DestroyEffectNum; j++)
				{
					//エフェクトの座標を衝突した敵の位置に
					destroyEffect[j][i].pos = BlueEnemyPos[i];
					//フラグをtrueにして使用中に
					destroyEffect[j][i].used = true;
					////表示する時間を0にしてリセット
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

		//敵のx座標を設定
		BlueEnemyPos[i].x = 0.0f - BlueEnemyYaw[i].x*EnemyRadius[count];

		//敵のz座標を設定
		BlueEnemyPos[i].z = 170.0f - BlueEnemyYaw[i].z*EnemyRadius[count];

		//敵の生存フラグをtrueに
		BlueEnemyAliveFlag[i] = true;

		BlueEnemyOllDown = false;
	}

}

//敵が倒された場合のエフェクトを描画
void BlueEnemy::DestroyEffectDraw()
{
	for (int i = 0; i < DestroyEffectNum; i++)
	{
		for (int j = 0; j < BlueEnemyNum; j++)
		{
			//フラグがtrueになっていれば描画
			if (destroyEffect[i][j].used == true)
			{
				//位置を設定
				vertex[i].pos = destroyEffect[i][j].pos;
				//大きさの設定
				vertex[i].size = 5.0f;
				//色の設定
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
			//フラグがtrueなら弾と敵が衝突したことになるので
			//エフェクトが再生されるようにする
			if (destroyEffect[i][j].used == true)
			{
				destroyEffect[i][j].pos.x += cos(destroyEffect[i][j].angle.x)*destroyEffect[i][j].speed;
				destroyEffect[i][j].pos.y += sin(destroyEffect[i][j].angle.y)*destroyEffect[i][j].speed;
				destroyEffect[i][j].pos.z += sin(destroyEffect[i][j].angle.z)*destroyEffect[i][j].speed;
				destroyEffect[i][j].count++;
			}

			//カウントが60を超えるとフラグをfalseにして
			//カウントも0にしておく
			if (destroyEffect[i][j].count >= 60)
			{
				destroyEffect[i][j].used = false;
				destroyEffect[i][j].count = 0;
			}
		}
	}
}

//=============================================
//■RedEnemyクラス■
//=============================================
//コンストラクタ
RedEnemy::RedEnemy()
{

}

//デストラクタ
RedEnemy::~RedEnemy()
{
	delete[] vertex;
}

//初期化
void RedEnemy::Initialize()
{
	degree = 90.0f;
	radian = 0;

	for (int i = 0; i < RedEnemyNum; i++)
	{
		enemyObb[i].SetLength(5, 10, 10);
		enemyObb[i].UpdateInfo(RedEnemyPos[i], forward, right, up);

		//角度からラジアンを求める
		radian = PI / 180 * degree;

		RedEnemyYaw[i].x = sin(radian);
		RedEnemyYaw[i].y = 0.0f;
		RedEnemyYaw[i].z = cos(radian);

		//角度を変える
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

//描画
void RedEnemy::Draw()
{
	for (int i = 0; i < RedEnemyNum; i++)
	{
		D3DXMatrixTranslation(&mat_transform, RedEnemyPos[i].x, 0.0f, RedEnemyPos[i].z);		//座標
		D3DXMatrixScaling(&mat_scale, 6.0f, 6.0f, 6.0f);				//拡大
		D3DXMatrixRotationYawPitchRoll(&mat_rotate, -RedEnemyYaw[i].x, 0.0f, 0.0f);	//回転	

		if (RedEnemyAliveFlag[i] == true)
		{
			EnemyModel[2].Draw(mat_transform, mat_scale, mat_rotate);
		}
	}
}

//更新
void RedEnemy::Update()
{
	for (int i = 0; i < RedEnemyNum; i++)
	{
		if (RedEnemyAliveFlag[i] == true)
		{
			//敵が自機に向かって移動
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
		//敵の生存フラグがtrueならば処理を行う
		if (RedEnemyAliveFlag[i] == true)
		{
			//衝突判定を行う
			if (OrientedBoundingBox::Collision(obb, enemyObb[i]))
			{
				//相手と衝突した敵の生存フラグをfalseにして
				//描画しないようにする
				RedEnemyAliveFlag[i] = false;

				se.ShotHitSEPlay();

				//衝突した時は敵が倒された場合だけなので
				//消滅エフェクトを用意
				for (int j = 0; j < DestroyEffectNum; j++)
				{
					//エフェクトの座標を衝突した敵の位置に
					destroyEffect[j][i].pos = RedEnemyPos[i];
					//フラグをtrueにして使用中に
					destroyEffect[j][i].used = true;
					////表示する時間を0にしてリセット
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

		//敵のx座標を設定
		RedEnemyPos[i].x = 0.0f + RedEnemyYaw[i].x*EnemyRadius[count];

		//敵のz座標を設定
		RedEnemyPos[i].z = 170.0f + RedEnemyYaw[i].z*EnemyRadius[count];

		//敵の生存フラグをtrueに
		RedEnemyAliveFlag[i] = true;

		RedEnemyOllDown = false;
	}
}

//敵が倒された場合のエフェクトを描画
void RedEnemy::DestroyEffectDraw()
{
	for (int i = 0; i < DestroyEffectNum; i++)
	{
		for (int j = 0; j < RedEnemyNum; j++)
		{
			//フラグがtrueになっていれば描画
			if (destroyEffect[i][j].used == true)
			{
				//位置を設定
				vertex[i].pos = destroyEffect[i][j].pos;
				//大きさの設定
				vertex[i].size = 5.0f;
				//色の設定
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
			//フラグがtrueなら弾と敵が衝突したことになるので
			//エフェクトが再生されるようにする
			if (destroyEffect[i][j].used == true)
			{
				destroyEffect[i][j].pos.x += cos(destroyEffect[i][j].angle.x)*destroyEffect[i][j].speed;
				destroyEffect[i][j].pos.y += sin(destroyEffect[i][j].angle.y)*destroyEffect[i][j].speed;
				destroyEffect[i][j].pos.z += sin(destroyEffect[i][j].angle.z)*destroyEffect[i][j].speed;
				destroyEffect[i][j].count++;
			}

			//カウントが60を超えるとフラグをfalseにして
			//カウントも0にしておく
			if (destroyEffect[i][j].count >= 60)
			{
				destroyEffect[i][j].used = false;
				destroyEffect[i][j].count = 0;
			}
		}
	}
}

//=============================================
//■GreenEnemyクラス■
//=============================================
//コンストラクタ
GreenEnemy::GreenEnemy()
{

}

//デストラクタ
GreenEnemy::~GreenEnemy()
{
	delete[] vertex;
}

//初期化
void GreenEnemy::Initialize()
{
	degree = 22.5f;
	radian = 0;

	for (int i = 0; i < GreenEnemyNum; i++)
	{
		enemyObb[i].SetLength(5, 10, 10);
		enemyObb[i].UpdateInfo(GreenEnemyPos[i], forward, right, up);

		//角度からラジアンを求める
		radian = PI / 180 * degree;

		GreenEnemyYaw[i].x = sin(radian);
		GreenEnemyYaw[i].y = 0.0f;
		GreenEnemyYaw[i].z = cos(radian);

		//角度を変える
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

	//正面	
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

//描画
void GreenEnemy::Draw()
{
	
	D3DXVECTOR3 scale;

	scale.x = 6.0f + sin(Wave)*1.0f;
	scale.y= 6.0f + cos(Wave)*1.0f;
	scale.z = 6.0f;

	for (int i = 0; i < GreenEnemyNum; i++)
	{

		//緑色の敵の描画設定
		D3DXMatrixTranslation(&mat_transform, GreenEnemyPos[i].x, 0.0f, GreenEnemyPos[i].z);		//座標
		D3DXMatrixScaling(&mat_scale, scale.x, scale.y, scale.z);				//拡大
		D3DXMatrixRotationYawPitchRoll(&mat_rotate, EnemyRadian[i], 0.0f, 0.0f);	//回転	

		if (GreenEnemyAliveFlag[i] == true)
		{
			EnemyModel[0].Draw(mat_transform, mat_scale, mat_rotate);
		}


		//緑色の敵から発射される弾
		D3DXMatrixTranslation(&mat_bulletTransform, BulletPos[i].x, 0.0f, BulletPos[i].z);		//座標
		D3DXMatrixScaling(&mat_bulletScale, 0.1f, 0.1f, 0.1f);				//拡大
		D3DXMatrixRotationYawPitchRoll(&mat_bulletRotate, -GreenEnemyYaw[i].x, 0.0f, 0.0f);	//回転	

		if (GreenEnemyShotFlag[i] == true)
		{
			EnemyBullet.Draw(mat_bulletTransform, mat_bulletScale, mat_bulletRotate);
		}
	}
	

}

//更新
void GreenEnemy::Update()
{
	for (int i = 0; i < GreenEnemyNum; i++)
	{
		if (GreenEnemyAliveFlag[i] == true)
		{
			//敵が自機に向かって移動
			GreenEnemyPos[i] -= GreenEnemyYaw[i] * EnemyMoveSpeed;
			enemyObb[i].UpdateInfo(GreenEnemyPos[i], forward, right, up);
		}

		bulletObb[i].UpdateInfo(BulletPos[i], forward, right, up);
	}

	//敵が全滅したかのフラグを取得
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
		// 敵を波打たせる
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
		//敵の生存フラグがtrueならば処理を行う
		if (GreenEnemyAliveFlag[i] == true)
		{
			//衝突判定を行う
			if (OrientedBoundingBox::Collision(obb, enemyObb[i]))
			{
				//相手と衝突した敵の生存フラグをfalseにして
				//描画しないようにする
				GreenEnemyAliveFlag[i] = false;

				se.ShotHitSEPlay();

				//衝突した時は敵が倒された場合だけなので
				//消滅エフェクトを用意
				for (int j = 0; j < DestroyEffectNum; j++)
				{
					//エフェクトの座標を衝突した敵の位置に
					destroyEffect[j][i].pos = GreenEnemyPos[i];
					//フラグをtrueにして使用中に
					destroyEffect[j][i].used = true;
					////表示する時間を0にしてリセット
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

		//敵のx座標を設定
		//自機から離れた位置になるようにしておく
		//描画するようにしておく
		GreenEnemyPos[i].x = 0.0f - GreenEnemyYaw[i].x*EnemyRadius[count];

		//敵のz座標を設定
		GreenEnemyPos[i].z = 170.0f - GreenEnemyYaw[i].z*EnemyRadius[count];

		//敵の生存フラグをtrueに
		GreenEnemyAliveFlag[i] = true;

		GreenEnemyOllDown = false;

		GreenEnemyShotFlag[i] = false;
	}

	ShotCount = 0;
	ShotFrame = 0;
	BulletFiredFlag = false;
	Wave = 0.0f;
}

//敵が倒された場合のエフェクトを描画
void GreenEnemy::DestroyEffectDraw()
{
	for (int i = 0; i < DestroyEffectNum; i++)
	{
		for (int j = 0; j < GreenEnemyNum; j++)
		{
			//フラグがtrueになっていれば描画
			if (destroyEffect[i][j].used == true)
			{
				//位置を設定
				vertex[i].pos = destroyEffect[i][j].pos;
				//大きさの設定
				vertex[i].size = 5.0f;
				//色の設定
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
			//フラグがtrueなら弾と敵が衝突したことになるので
			//エフェクトが再生されるようにする
			if (destroyEffect[i][j].used == true)
			{
				destroyEffect[i][j].pos.x += cos(destroyEffect[i][j].angle.x)*destroyEffect[i][j].speed;
				destroyEffect[i][j].pos.y += sin(destroyEffect[i][j].angle.y)*destroyEffect[i][j].speed;
				destroyEffect[i][j].pos.z += sin(destroyEffect[i][j].angle.z)*destroyEffect[i][j].speed;
				destroyEffect[i][j].count++;
			}

			//カウントが60を超えるとフラグをfalseにして
			//カウントも0にしておく
			if (destroyEffect[i][j].count >= 60)
			{
				destroyEffect[i][j].used = false;
				destroyEffect[i][j].count = 0;
			}
		}
	}
}

//敵の弾の発射を制御する関数
void GreenEnemy::EnemyBulletShot()
{
	//弾発射の秒数を管理するフレームを加算
	ShotFrame++;
	//フレームが60を超えた場合、一秒が経過
	if (ShotFrame >= 60)
	{
		//一秒経ったのでカウントを1加算
		ShotCount++;
		//フレームをリセットして再びカウント
		ShotFrame = 0;
	}

	for (int i = 0; i < GreenEnemyNum; i++)
	{
		//弾を発射していない状態ならば処理
		if (GreenEnemyShotFlag[i] == false)
		{
			//三秒カウントされるごとに処理
			if (ShotCount == BulletShotTiming && BulletFiredFlag == false)
			{
				//フラグをtrueにして弾を発射させる
				if (GreenEnemyAliveFlag[i] == true)
				{
					GreenEnemyShotFlag[i] = true;
					Wave = 0.0f;
				}
			}
		}
		else
		{
			//弾を発射した状態で一秒経過したらフラグをfalseにする
			if (ShotCount == BulletEndTiming)
			{
				GreenEnemyShotFlag[i] = false;
			}
		}
	}

	if (ShotCount == BulletShotTiming)
	{
		//一度だけ発射させるために発射済みか判断するフラグを
		//trueにしておく
		BulletFiredFlag = true;
	}

	//カウントをリセット
	if (ShotCount == BulletEndTiming)
	{
		ShotCount = 0;
		BulletFiredFlag = false;
	}

}

//敵の発射する弾の位置を設定する関数
void GreenEnemy::EnemyBulletSet()
{
	for (int i = 0; i < GreenEnemyNum; i++)
	{
		//敵が弾を発射している場合に処理
		if (GreenEnemyShotFlag[i] == true)
		{
			//敵が向いている方向に向かって進むようにする
			BulletPos[i] -= BulletAngle[i] * 3.0f;
		}
		//敵が弾を発射していない状態
		else
		{
			//敵の位置と角度を取得する
			BulletPos[i] = GreenEnemyPos[i];
			BulletAngle[i] = GreenEnemyYaw[i];
		}
	}
}


//緑色の敵が発射する弾との衝突判定を処理する関数
bool GreenEnemy::EnemyBulletCollision(OrientedBoundingBox obb)
{
	for (int i = 0; i < GreenEnemyNum; i++)
	{
		//弾の生存フラグがtrueならば処理を行う
		if (GreenEnemyShotFlag[i] == true)
		{
			//衝突判定を行う
			if (OrientedBoundingBox::Collision(bulletObb[i],obb ))
			{
				//相手と衝突した時に弾の発射のフラグをtrueにして
				//描画しないようにする
				GreenEnemyShotFlag[i] = false;
				return true;
			}
		}
	}

	return false;
}


//=============================================
//■PurpleEnemyクラス■
//=============================================
//コンストラクタ
PurpleEnemy::PurpleEnemy()
{

}

//デストラクタ
PurpleEnemy::~PurpleEnemy()
{
	delete[] vertex;
}

//初期化
void PurpleEnemy::Initialize()
{
	degree = 45.0f;
	radian = 0;

	for (int i = 0; i < PurpleEnemyNum; i++)
	{
		enemyObb[i].SetLength(5, 10, 10);
		enemyObb[i].UpdateInfo(PurpleEnemyPos[i], forward, right, up);

		//角度からラジアンを求める
		radian = PI / 180 * degree;

		PurpleEnemyYaw[i].x = sin(radian);
		PurpleEnemyYaw[i].y = 0.0f;
		PurpleEnemyYaw[i].z = cos(radian);

		//角度を変える
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

//描画
void PurpleEnemy::Draw()
{
	for (int i = 0; i < PurpleEnemyNum; i++)
	{
		D3DXMatrixTranslation(&mat_transform, PurpleEnemyPos[i].x, 0.0f, PurpleEnemyPos[i].z);		//座標
		D3DXMatrixScaling(&mat_scale, 6.0f, 6.0f,6.0f);				//拡大
		D3DXMatrixRotationYawPitchRoll(&mat_rotate, EnemyRadian[i], 0.0f, 0.0f);	//回転	

		if (PurpleEnemyAliveFlag[i] == true)
		{
			EnemyModel[3].Draw(mat_transform, mat_scale, mat_rotate);
		}
	}
}

//更新
void PurpleEnemy::Update()
{
	for (int i = 0; i < PurpleEnemyNum; i++)
	{
		if (PurpleEnemyAliveFlag[i] == true)
		{
			//敵が自機に向かって移動
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

//紫色の敵の衝突判定
//他の敵と違ってHPがあるので処理は異なっている
bool PurpleEnemy::PurpleEnemyCollision(OrientedBoundingBox obb, bool *flag)
{
	for (int i = 0; i < PurpleEnemyNum; i++)
	{
		//敵の生存フラグがtrueならば処理を行う
		if (PurpleEnemyAliveFlag[i] == true)
		{
			//衝突判定を行う
			if (OrientedBoundingBox::Collision(obb, enemyObb[i]))
			{
				//弾と衝突した敵のHPを減らす
				HitPoint[i]--;
				//弾を描画しているフラグをfalseに
				*flag = false;

				se.ShotHitSEPlay();
				

				//HPが0になれば敵の描画フラグを消し、フラグを返す
				if (HitPoint[i] == 0)
				{
					//相手と衝突した敵の生存フラグをfalseにして
					//描画しないようにする
					PurpleEnemyAliveFlag[i] = false;

					//衝突した時は敵が倒された場合だけなので
					//消滅エフェクトを用意
					for (int j = 0; j < DestroyEffectNum; j++)
					{
						//エフェクトの座標を衝突した敵の位置に
						destroyEffect[j][i].pos = PurpleEnemyPos[i];
						//フラグをtrueにして使用中に
						destroyEffect[j][i].used = true;
						////表示する時間を0にしてリセット
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

		//敵のx座標を設定
		//自機から離れた位置になるようにしておく
		//描画するようにしておく
		PurpleEnemyPos[i].x = 0.0f - PurpleEnemyYaw[i].x*EnemyRadius[count];

		//敵のz座標を設定
		PurpleEnemyPos[i].z = 170.0f - PurpleEnemyYaw[i].z*EnemyRadius[count];

		//敵の生存フラグをtrueに
		PurpleEnemyAliveFlag[i] = true;

		PurpleEnemyOllDown = false;

		HitPoint[i] = 2;
	}
}

//敵が倒された場合のエフェクトを描画
void PurpleEnemy::DestroyEffectDraw()
{
	for (int i = 0; i < DestroyEffectNum; i++)
	{
		for (int j = 0; j < PurpleEnemyNum; j++)
		{
			//フラグがtrueになっていれば描画
			if (destroyEffect[i][j].used == true)
			{
				//位置を設定
				vertex[i].pos = destroyEffect[i][j].pos;
				//大きさの設定
				vertex[i].size = 5.0f;
				//色の設定
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
			//フラグがtrueなら弾と敵が衝突したことになるので
			//エフェクトが再生されるようにする
			if (destroyEffect[i][j].used == true)
			{
				destroyEffect[i][j].pos.x += cos(destroyEffect[i][j].angle.x)*destroyEffect[i][j].speed;
				destroyEffect[i][j].pos.y += sin(destroyEffect[i][j].angle.y)*destroyEffect[i][j].speed;
				destroyEffect[i][j].pos.z += sin(destroyEffect[i][j].angle.z)*destroyEffect[i][j].speed;
				destroyEffect[i][j].count++;
			}

			//カウントが60を超えるとフラグをfalseにして
			//カウントも0にしておく
			if (destroyEffect[i][j].count >= 60)
			{
				destroyEffect[i][j].used = false;
				destroyEffect[i][j].count = 0;
			}
		}
	}
}