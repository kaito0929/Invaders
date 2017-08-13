#include "Enemy.h"

//コンストラクタ
Enemy::Enemy()
{

}

//デストラクタ
Enemy::~Enemy()
{
	delete DestroyTex;
	delete[] vertex;
}

//初期化
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

//描画
void Enemy::Draw()
{
	//敵の描画
	for (int z = 0; z < EnemyColumnNum; z++)
	{
		for (int x = 0; x < EnemyRowNum; x++)
		{
			D3DXMatrixTranslation(&mat_transform, EnemyPos[x + z * 10].x, 0.0f, EnemyPos[x + z * 10].z);		//座標
			D3DXMatrixScaling(&mat_scale, 8.0f, 8.0f, 8.0f);				//拡大
			D3DXMatrixRotationYawPitchRoll(&mat_rotate, -angle[x + z * 10].x, 0.0f, 0.0f);	//回転	

			if (EnemyAliveFlag[x + z * 10] == true)
			{
				EnemyModel[z].Draw(mat_transform, mat_scale, mat_rotate);
			}
		}
	}


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
			EnemyPos[i] += angle[i] * EnemyMoveSpeed;
			//EnemyPos[i].z += cos(angle[i].z) * EnemyMoveSpeed;
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
		//敵の生存フラグがtrueならば処理を行う
		if (EnemyAliveFlag[i] == true)
		{
			//衝突判定を行う
			if (OrientedBoundingBox::Collision(obb, enemyObb[i]))
			{
				//相手と衝突した敵の生存フラグをfalseにして
				//描画しないようにする
				EnemyAliveFlag[i] = false;

				//衝突した時は敵が倒された場合だけなので
				//消滅エフェクトを用意
				for (int j = 0; j < DestroyEffectNum; j++)
				{
					//エフェクトの座標を衝突した敵の位置に
					destroyEffect[j][i].pos = EnemyPos[i];
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

//敵の位置や生存フラグを初期化する関数
//敵が全滅した場合にリポップさせる場合に使用する
void Enemy::EnemyReset()
{
	for (int z = 0; z < EnemyColumnNum; z++)
	{
		for (int x = 0; x < EnemyRowNum; x++)
		{
			//敵のx座標を設定
			//左端を-90にしておいて、そこから20fずつずらして
			//自機から離れた位置になるようにしておく
			//描画するようにしておく
			EnemyPos[x + z * 10].x = 0.0f + angle[x + z * 10].x*30.0f;

			//敵のz座標を設定
			//x座標と同じように20fずつずらして描画
			EnemyPos[x + z * 10].z = 150.0f + angle[x + z * 10].z*30.0f;

			//敵の生存フラグをtrueに
			EnemyAliveFlag[x + z * 10] = true;
		}
	}

	//敵が全て倒された場合のフラグもfalseにして
	//ゲームが再開できるようにする
	EnemyOllDestroy = false;
}

//敵が倒された場合のエフェクトを描画
void Enemy::DestroyEffectDraw()
{
	for (int i = 0; i < DestroyEffectNum; i++)
	{
		for (int j = 0; j < EnemyNum; j++)
		{
			//フラグがtrueになっていれば描画
			if (destroyEffect[i][j].used == true)
			{
				//位置を設定
				vertex[i].pos = destroyEffect[i][j].pos;
				//大きさの設定
				vertex[i].size = 15.0f;
				//色の設定
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

}

//初期化
void BlueEnemy::Initialize()
{
	//モデルのロード
	BlueEnemyModel.Load(_T("Model/enemy1.x"));

	//当たり判定の設定
	//右側
	right.x = cos(0);
	right.y = 0;
	right.z = sin(0);
	//上
	up.x = up.z = 0;
	up.y = 1;
	//正面	
	forward.x = forward.y = cos(D3DX_PI / 2);
	forward.z = sin(D3DX_PI / 2);

	degree = 0;
	radian = 0;

	for (int i = 0; i < BlueEnemyNum; i++)
	{
		enemyObb[i].SetLength(5, 10, 10);
		enemyObb[i].UpdateInfo(BlueEnemyPos[i], forward, right, up);

		//角度からラジアンを求める
		radian = PI / 180 * degree;

		BlueEnemyYaw[i].x = sin(radian);
		BlueEnemyYaw[i].y = 0.0f;
		BlueEnemyYaw[i].z = cos(radian);

		//角度を変える
		degree += 180.0f;
	}

	BlueEnemyReset();

}

//描画
void BlueEnemy::Draw()
{
	for (int x = 0; x < BlueEnemyNum; x++)
	{
		D3DXMatrixTranslation(&mat_transform, BlueEnemyPos[x].x, 0.0f, BlueEnemyPos[x].z);		//座標
		D3DXMatrixScaling(&mat_scale, 8.0f, 8.0f, 8.0f);				//拡大
		D3DXMatrixRotationYawPitchRoll(&mat_rotate, -BlueEnemyYaw[x].x, 0.0f, 0.0f);	//回転	

		if (BlueEnemyAliveFlag[x] == true)
		{
			BlueEnemyModel.Draw(mat_transform, mat_scale, mat_rotate);
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
			BlueEnemyPos[i] += BlueEnemyYaw[i] * EnemyMoveSpeed;
			enemyObb[i].UpdateInfo(BlueEnemyPos[i], forward, right, up);
		}
	}
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

				////衝突した時は敵が倒された場合だけなので
				////消滅エフェクトを用意
				//for (int j = 0; j < DestroyEffectNum; j++)
				//{
				//	//エフェクトの座標を衝突した敵の位置に
				//	destroyEffect[j][i].pos = BlueEnemyPos[i];
				//	//フラグをtrueにして使用中に
				//	destroyEffect[j][i].used = true;
				//	////表示する時間を0にしてリセット
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
		//敵のx座標を設定
		//左端を-90にしておいて、そこから20fずつずらして
		//自機から離れた位置になるようにしておく
		//描画するようにしておく
		BlueEnemyPos[x].x = 0.0f + BlueEnemyYaw[x].x*EnemyRadius

		//敵のz座標を設定
		//x座標と同じように20fずつずらして描画
		BlueEnemyPos[x].z = 150.0f + BlueEnemyYaw[x].z*EnemyRadius

		//敵の生存フラグをtrueに
		BlueEnemyAliveFlag[x] = true;
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

}

//初期化
void RedEnemy::Initialize()
{
	//モデルのロード
	RedEnemyModel.Load(_T("Model/enemy2.x"));

	//当たり判定の設定
	//右側
	right.x = cos(0);
	right.y = 0;
	right.z = sin(0);
	//上
	up.x = up.z = 0;
	up.y = 1;
	//正面	
	forward.x = forward.y = cos(D3DX_PI / 2);
	forward.z = sin(D3DX_PI / 2);

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

	RedEnemyReset();
}

//描画
void RedEnemy::Draw()
{
	for (int x = 0; x < RedEnemyNum; x++)
	{
		D3DXMatrixTranslation(&mat_transform, RedEnemyPos[x].x, 0.0f, RedEnemyPos[x].z);		//座標
		D3DXMatrixScaling(&mat_scale, 8.0f, 8.0f, 8.0f);				//拡大
		D3DXMatrixRotationYawPitchRoll(&mat_rotate, -RedEnemyYaw[x].x, 0.0f, 0.0f);	//回転	

		if (RedEnemyAliveFlag[x] == true)
		{
			RedEnemyModel.Draw(mat_transform, mat_scale, mat_rotate);
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

				////衝突した時は敵が倒された場合だけなので
				////消滅エフェクトを用意
				//for (int j = 0; j < DestroyEffectNum; j++)
				//{
				//	//エフェクトの座標を衝突した敵の位置に
				//	destroyEffect[j][i].pos = BlueEnemyPos[i];
				//	//フラグをtrueにして使用中に
				//	destroyEffect[j][i].used = true;
				//	////表示する時間を0にしてリセット
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
		//敵のx座標を設定
		//左端を-90にしておいて、そこから20fずつずらして
		//自機から離れた位置になるようにしておく
		//描画するようにしておく
		RedEnemyPos[x].x = 0.0f + RedEnemyYaw[x].x*EnemyRadius

		//敵のz座標を設定
		//x座標と同じように20fずつずらして描画
		RedEnemyPos[x].z = 150.0f + RedEnemyYaw[x].z*EnemyRadius

		//敵の生存フラグをtrueに
		RedEnemyAliveFlag[x] = true;
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

}

//初期化
void GreenEnemy::Initialize()
{
	//モデルのロード
	GreenEnemyModel.Load(_T("Model/enemy0.x"));

	//当たり判定の設定
	//右側
	right.x = cos(0);
	right.y = 0;
	right.z = sin(0);
	//上
	up.x = up.z = 0;
	up.y = 1;
	//正面	
	forward.x = forward.y = cos(D3DX_PI / 2);
	forward.z = sin(D3DX_PI / 2);

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
		degree += 22.5f;

		if (degree == 0.0f || degree == 90.0f || degree == 180.0f || degree == 270.0f)
		{
			//角度を変える
			degree += 22.5f;
		}
	}

	GreenEnemyReset();
}

//描画
void GreenEnemy::Draw()
{
	for (int x = 0; x < GreenEnemyNum; x++)
	{
		D3DXMatrixTranslation(&mat_transform, GreenEnemyPos[x].x, 0.0f, GreenEnemyPos[x].z);		//座標
		D3DXMatrixScaling(&mat_scale, 8.0f, 8.0f, 8.0f);				//拡大
		D3DXMatrixRotationYawPitchRoll(&mat_rotate, -GreenEnemyYaw[x].x, 0.0f, 0.0f);	//回転	

		if (GreenEnemyAliveFlag[x] == true)
		{
			GreenEnemyModel.Draw(mat_transform, mat_scale, mat_rotate);
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
			GreenEnemyPos[i] += GreenEnemyYaw[i] * EnemyMoveSpeed;
			enemyObb[i].UpdateInfo(GreenEnemyPos[i], forward, right, up);
		}
	}
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

				////衝突した時は敵が倒された場合だけなので
				////消滅エフェクトを用意
				//for (int j = 0; j < DestroyEffectNum; j++)
				//{
				//	//エフェクトの座標を衝突した敵の位置に
				//	destroyEffect[j][i].pos = BlueEnemyPos[i];
				//	//フラグをtrueにして使用中に
				//	destroyEffect[j][i].used = true;
				//	////表示する時間を0にしてリセット
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
		//敵のx座標を設定
		//自機から離れた位置になるようにしておく
		//描画するようにしておく
		GreenEnemyPos[x].x = 0.0f + GreenEnemyYaw[x].x*EnemyRadius

		//敵のz座標を設定
		GreenEnemyPos[x].z = 150.0f + GreenEnemyYaw[x].z*EnemyRadius

		//敵の生存フラグをtrueに
		GreenEnemyAliveFlag[x] = true;

		HitPoint = 0;
	}
}