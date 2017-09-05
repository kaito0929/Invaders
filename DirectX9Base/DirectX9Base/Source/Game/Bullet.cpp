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

	//正面	
	forward.x = forward.y = cos(D3DX_PI/2);
	forward.z = sin(D3DX_PI/2);

}

void Bullet::Draw()
{
	for (int i = 0; i < BulletMax; i++)
	{
		//弾の描画
		//フラグがtrueになっていれば描画するように
		//フラグをtrueにするのはスペースキーを押した時
		if (BulletShotFlag[i] == true)
		{
			D3DXMatrixTranslation(&mat_transform, BulletPos[i].x, BulletPos[i].y, BulletPos[i].z);	//座標
			D3DXMatrixScaling(&mat_scale, 0.1f, 0.1f, 0.1f);								//拡大
			D3DXMatrixRotationYawPitchRoll(&mat_rotate, 0.0f, 0.0f, 0.0f);//回転

			BulletModel.Draw(mat_transform, mat_scale, mat_rotate);
		}
	}

	//弾の当たり判定の描画
	//基本的にデバッグ時に使用するので普段はコメントアウトしておく
	//bulletObb.DrawLine();

}

void Bullet::Update()
{
	for (int i = 0; i < BulletMax; i++)
	{
		//当たり判定の更新
		bulletObb[i].UpdateInfo(BulletPos[i], forward, right, up);
	}
}

//弾の発射位置を設定する関数
void Bullet::BulletSet(D3DXVECTOR3 pPos, D3DXVECTOR3 pAngle)
{
	for (int i = 0; i < BulletMax; i++)
	{
		//弾の発射フラグによって処理が変化
		if (BulletShotFlag[i] == true)
		{
			//trueなら奥へ移動
			BulletPos[i] += BulletShotAngle[i] * BulletMoveSpeed;
		}
		else
		{
			//弾の発射角度を更新
			BulletShotAngle[i] = pAngle;
			//falseなら位置を更新
			BulletPos[i] = pPos;
		}
	}
}