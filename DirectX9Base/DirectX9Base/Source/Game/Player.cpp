#include "Player.h"

//コンストラクタ
Player::Player()
{		

}

//デストラクタ
Player::~Player()
{
	delete DestroyTex;
	delete[] vertex;
}

//初期化関数
void Player::Initialize()
{
	PlayerModel.Load(_T("Model/Player.x"));

	CameraPos.x = CameraPos.y = CameraPos.z = 0.0f;

	PlayerRoll = PlayerYaw =  0.0f;

	PlayerAngle.x = sin(PlayerYaw);
	PlayerAngle.y = sin(0.0f);
	PlayerAngle.z = cos(PlayerYaw);

	//カメラの位置設定
	CameraPos.x = PlayerPos.x + (PlayerAngle.x * Camera_Pos_Set * Camera_Distance);
	CameraPos.y = (PlayerPos.y + 40.0f) + (PlayerAngle.y * -0.6f * 100.0f);
	CameraPos.z = PlayerPos.z + (PlayerAngle.z * Camera_Pos_Set * Camera_Distance);

	//プレイヤーの位置設定
	PlayerPos.x = 0.0f - PlayerAngle.x * 170.0f;
	PlayerPos.y = 0.0f;
	PlayerPos.z = 170.0f - PlayerAngle.z * 170.0f;

	PlayerAliveFlag = true;
	PlayerHp = 3;

	HitPointTex.Load("Texture/heart_gloss.png");

	for (int i = 0; i < 3; i++)
	{
		HitPointSprite[i].SetSize(70, 70);
	}

	HitPointSprite[0].SetPos(1190, 700);
	HitPointSprite[1].SetPos(1120, 700);
	HitPointSprite[2].SetPos(1050, 700);

	for (int i = 0; i < DestroyEffectNum; i++)
	{
		destroyEffect[i].pos = PlayerPos;
		destroyEffect[i].speed = 1.0f;
		destroyEffect[i].angle = D3DXVECTOR3(random.GetRandom_Int(1, 250), random.GetRandom_Int(1, 100), random.GetRandom_Int(100, 1100));
		destroyEffect[i].count = 0;
		destroyEffect[i].used = false;
	}


	DestroyTex = new Texture;
	DestroyTex->Load("Texture/effect1.png");
	vertex = new VERTEX[DestroyEffectNum];



	//当たり判定----------------------------------------
	//正面	
	forward.x = cos(-PlayerYaw + (D3DX_PI / 2));
	forward.y = cos(0.0f + (D3DX_PI / 2));
	forward.z = sin(-PlayerYaw + (D3DX_PI / 2));

	////右側
	right.x = cos(-PlayerYaw);
	right.y = 0;
	right.z = sin(-PlayerYaw);

	up.x = 0;
	up.y = 1;
	up.z = 0;

	playerObb.SetLength(20, 10, 10);
	playerObb.UpdateInfo(PlayerPos,forward,right,up);

	//--------------------------------------------------

	camera.SetEyePoint(CameraPos);
	camera.SetRelLookAtPoint(PlayerAngle.x, -0.3f, PlayerAngle.z);

	camera.UpdateViewMatrix();
}

//描画関数
void Player::Draw()
{
	if (PlayerAliveFlag == true)
	{
		D3DXMatrixTranslation(&mat_transform, PlayerPos.x, PlayerPos.y, PlayerPos.z);	//座標
		D3DXMatrixScaling(&mat_scale, 0.1f, 0.1f, 0.1f);								//拡大
		D3DXMatrixRotationYawPitchRoll(&mat_rotate, PlayerYaw, 0.0f, PlayerRoll);//回転	

		//プレイヤー（自機）の描画
		PlayerModel.Draw(mat_transform, mat_scale, mat_rotate);
	}

	//プレイヤーのHPの描画
	//変数が1減るたびにテクスチャが一つずつなくなるようにする
	for (int i = 0; i < PlayerHp; i++)
	{
		Direct3D::DrawSprite(HitPointSprite[i], HitPointTex);
	}

}

void Player::Update()
{
	//当たり判定の更新
	playerObb.UpdateInfo(PlayerPos, forward, right, up);
	//自機の制御関数
	PlayerMoveControl();

	//カメラの動きを制御する関数
	CameraControl();
}

//プレイヤーの動きの制御
void Player::PlayerMoveControl()
{
	DirectInput* pDi = DirectInput::GetInstance();

	PlayerAngle.x = sin(PlayerYaw);
	PlayerAngle.z = cos(PlayerYaw);

	//左への移動
	if (pDi->KeyCount(DIK_LEFT))
	{
		PlayerYaw += 0.01f;

		//自機を左へと傾ける
		PlayerRoll += PlayerRotateZ_ChangeNum;
		if (PlayerRoll >= PlayerRotateLeftMax)
		{
			PlayerRoll = PlayerRotateLeftMax;
		}
	}

	//右への移動
	if (pDi->KeyCount(DIK_RIGHT))
	{
		PlayerYaw -= 0.01f;

		//自機を右へと傾ける
		PlayerRoll -= PlayerRotateZ_ChangeNum;
		if (PlayerRoll <= PlayerRotateRightMax)
		{
			PlayerRoll = PlayerRotateRightMax;
		}
	}

	//プレイヤーを円を描くように移動させる
	PlayerPos.x = 0.0f - PlayerAngle.x * 170.0f;
	PlayerPos.z = 170.0f - PlayerAngle.z * 170.0f;

	//自機の傾きを自動で直す
	PlayerRoll *= 0.8f;

}


//カメラの動きの制御
void Player::CameraControl()
{
	//自機に合わせたカメラの移動
	CameraPos.x = PlayerPos.x + (PlayerAngle.x * Camera_Pos_Set * Camera_Distance);
	CameraPos.y = (PlayerPos.y + 40.0f) + (PlayerAngle.y * -0.6f * 100.0f);
	CameraPos.z = PlayerPos.z + (PlayerAngle.z * Camera_Pos_Set * Camera_Distance);

	//カメラの座標の更新
	camera.SetEyePoint(CameraPos);
	//方向の更新
	camera.SetRelLookAtPoint(PlayerAngle.x, -0.3f, PlayerAngle.z);

	//カメラの更新
	camera.UpdateViewMatrix();
}

//消滅時のエフェクトを描画する関数
void Player::EffectDraw()
{
	for (int i = 0; i < DestroyEffectNum; i++)
	{
		//フラグがtrueになっていれば描画
		if (destroyEffect[i].used == true)
		{
			//位置を設定
			vertex[i].pos = destroyEffect[i].pos;
			//大きさの設定
			vertex[i].size = 15.0f;
			//色の設定
			vertex[i].color = (DWORD)D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

			Direct3D::GetInstance()->DrawPointSprite(vertex, DestroyEffectNum, *DestroyTex);
		}
	}
}

//消滅時のエフェクトの位置やフラグを設定する
void Player::EffectSet()
{
	for (int i = 0; i < DestroyEffectNum; i++)
	{
		if (destroyEffect[i].used == false)
		{
			destroyEffect[i].pos = PlayerPos;
			destroyEffect[i].used = true;
			destroyEffect[i].count = 0;
		}
	}
}

//消滅時のエフェクトの軌道
void Player::EffecMove()
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

			//カウントを加算することで画面遷移の条件にする
			destroyEffect[i].count++;
		}
	}

}

