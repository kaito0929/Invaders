#pragma once

#include "../Direct3D/mesh.h"
#include "../Direct3D/Direct3D.h"
#include "../Direct3D/Texture.h"
#include "../Direct3D/Sprite.h"
#include "../Direct3D/camera.h"
#include "../BoundingBox/BoundingBox.h"
#include "../Input/directInput.h"

#define PlayerRotateZ_ChangeNum 0.1f	//自機の向きを変える時の数値

#define PlayerRotateLeftMax 1.0f
#define PlayerRotateRightMax -1.0f

#define Camera_Pos_Set -0.6f		//カメラの位置設定
#define Camera_Distance 100			//カメラと自機の距離

class Player
{
private:

	//プレイヤーのモデル
	Mesh PlayerModel;
	
	//メッシュに渡す行列を作成
	D3DXMATRIXA16 mat_transform, mat_scale, mat_rotate;

	//プレイヤーのモデルを傾けるための変数
	float PlayerRotateZ;

	//カメラ操作
	Camera camera;
	//カメラの位置
	D3DXVECTOR3 CameraPos;

public:

	//コンストラクタ
	Player();
	//デストラクタ
	~Player();

	//初期化
	void Initialize();
	//実際の動き
	void Update();
	//描画
	void Draw();

	//プレイヤーの移動の制御
	void PlayerMoveControl();

	//カメラの動きの制御
	void CameraControl();


	//プレイヤーの位置
	D3DXVECTOR3 PlayerPos;

	//プレイヤーの生存フラグ
	bool PlayerAliveFlag;


};