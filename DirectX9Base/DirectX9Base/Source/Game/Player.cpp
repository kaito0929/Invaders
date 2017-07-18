#include "Player.h"

#include <stdio.h>
#include <stdlib.h>	//rand()関数用
#include <time.h>	//time()関数用
#include <math.h>


Player::Player()
{		

}

Player::~Player()
{

}

//初期化関数
void Player::Initialize()
{
	PlayerModel.Load(_T("Model/Player.x"));

	PlayerPos.x = PlayerPos.y = PlayerPos.z = 0.0f;
	CameraPos.x = CameraPos.y = CameraPos.z = 0.0f;

	PlayerRotateZ = 0.0f;

	//カメラの移動
	CameraPos.x = PlayerPos.x + (0.0f * -0.6f * 100.0f);
	CameraPos.y = (PlayerPos.y + 40.0f) + (0.0f * -0.6f * 100.0f);
	CameraPos.z = (PlayerPos.z - 20.0f) + (1.0f * -0.6f * 100.0f);

	camera.SetEyePoint(CameraPos);
	camera.SetRelLookAtPoint(0.0f, -0.3f, 1.0f);

	camera.UpdateViewMatrix();

	PlayerAliveFlag = true;

}

//描画関数
void Player::Draw()
{
	D3DXMatrixTranslation(&mat_transform, PlayerPos.x, PlayerPos.y, PlayerPos.z);	//座標
	D3DXMatrixScaling(&mat_scale, 0.1f, 0.1f, 0.1f);								//拡大
	D3DXMatrixRotationYawPitchRoll(&mat_rotate, 0.0f, 0.0f, PlayerRotateZ);//回転	

	if (PlayerAliveFlag == true)
	{
		//プレイヤー（自機）の描画
		PlayerModel.Draw(mat_transform, mat_scale, mat_rotate);
	}
}

void Player::Update()
{
	//プレイヤーの生存フラグがtrueならば処理を行うように
	if (PlayerAliveFlag == true)
	{
		PlayerMoveControl();
		CameraControl();
	}
}

//プレイヤーの動きの制御
void Player::PlayerMoveControl()
{
	DirectInput* pDi = DirectInput::GetInstance();

	//左への移動
	if (pDi->KeyCount(DIK_LEFT))
	{
		//プレイヤーのx座標をマイナスして左へ移動
		PlayerPos.x--;
		//自機を左へと傾ける
		PlayerRotateZ += PlayerRotateZ_ChangeNum;
		if (PlayerRotateZ >= PlayerRotateLeftMax)
		{
			PlayerRotateZ = PlayerRotateLeftMax;
		}
	}

	//右への移動
	if (pDi->KeyCount(DIK_RIGHT))
	{
		//プレイヤーのx座標をプラスして左へ移動
		PlayerPos.x++;
		//自機を右へと傾ける
		PlayerRotateZ -= PlayerRotateZ_ChangeNum;
		if (PlayerRotateZ <= PlayerRotateRightMax)
		{
			PlayerRotateZ = PlayerRotateRightMax;
		}
	}

	//自機の傾きを自動で直す
	PlayerRotateZ *= 0.8f;

}


//カメラの動きの制御
void Player::CameraControl()
{
	//自機に合わせたカメラの移動
	CameraPos.x = PlayerPos.x + (0.0f * Camera_Pos_Set * Camera_Distance);
	//座標の更新
	camera.SetEyePoint(CameraPos);
	//カメラの更新
	camera.UpdateViewMatrix();
}

