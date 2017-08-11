#include "Player.h"

//コンストラクタ
Player::Player()
{		

}

//デストラクタ
Player::~Player()
{

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

	//プレイヤーを円を描くように移動させる
	PlayerPos.x = 0.0f - PlayerAngle.x * 150.0f;
	PlayerPos.y = 0.0f;
	PlayerPos.z = 150.0f - PlayerAngle.z * 150.0f;


	camera.SetEyePoint(CameraPos);
	camera.SetRelLookAtPoint(PlayerAngle.x, -0.3f, PlayerAngle.z);

	camera.UpdateViewMatrix();
}

//描画関数
void Player::Draw()
{
	D3DXMatrixTranslation(&mat_transform, PlayerPos.x, PlayerPos.y, PlayerPos.z);	//座標
	D3DXMatrixScaling(&mat_scale, 0.1f, 0.1f, 0.1f);								//拡大
	D3DXMatrixRotationYawPitchRoll(&mat_rotate, PlayerYaw, 0.0f, PlayerRoll);//回転	

	//プレイヤー（自機）の描画
	PlayerModel.Draw(mat_transform, mat_scale, mat_rotate);
}

void Player::Update()
{
	PlayerMoveControl();
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
	PlayerPos.x = 0.0f - PlayerAngle.x * 150.0f;
	PlayerPos.z = 150.0f - PlayerAngle.z * 150.0f;

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

