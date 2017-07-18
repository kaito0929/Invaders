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

	//正面	
	forward.x = forward.y = cos(D3DX_PI/2);
	forward.z = sin(D3DX_PI/2);

	bulletObb.SetLength(10,10,10);

	bulletObb.UpdateInfo(BulletPos, forward, right, up);
}

void Bullet::Draw()
{
	//弾の描画
	//フラグがtrueになっていれば描画するように
	//フラグをtrueにするのはスペースキーを押した時
	if (BulletShotFlag == true)
	{
		D3DXMatrixTranslation(&mat_transform, BulletPos.x, BulletPos.y, BulletPos.z);	//座標
		D3DXMatrixScaling(&mat_scale, 0.1f, 0.1f, 0.1f);								//拡大
		D3DXMatrixRotationYawPitchRoll(&mat_rotate, 0.0f, 0.0f, 0.0f);//回転

		BulletModel.Draw(mat_transform, mat_scale, mat_rotate);
	}

	//弾の当たり判定の描画
	//基本的にデバッグ時に使用するので普段はコメントアウトしておく
	bulletObb.DrawLine();

}

void Bullet::Update()
{
	//当たり判定の更新
	bulletObb.UpdateInfo(BulletPos, forward, right, up);

	//弾が指定した位置まで移動したらフラグをfaleに
	//falseになることによって再び弾が発射できるようになる
	if (BulletPos.z > BulletPosZMax)
	{
		BulletShotFlag = false;
	}
}

//弾の発射位置を設定する関数
void Bullet::BulletPosSet(D3DXVECTOR3 pPos)
{
	//弾の発射フラグによって処理が変化
	if (BulletShotFlag == true)
	{
		//trueなら奥へ移動
		BulletPos.z += BulletMoveSpeed;
	}
	else
	{
		//falseなら位置を更新
		BulletPos = pPos;
	}
}