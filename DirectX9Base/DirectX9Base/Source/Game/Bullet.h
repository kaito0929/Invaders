#pragma once

#include "../Direct3D/mesh.h"
#include "../Direct3D/Direct3D.h"
#include "../Direct3D/Texture.h"
#include "../Direct3D/Sprite.h"
#include "../Direct3D/camera.h"
#include "../BoundingBox/BoundingBox.h"
#include "../Input/directInput.h"

//弾のz座標の最大値
#define BulletPosZMax 200.0f
//弾の移動速度
#define BulletMoveSpeed 3.0f 

class Bullet
{
private:

	//弾のモデル
	Mesh BulletModel;
	//メッシュに渡す行列を作成
	D3DXMATRIXA16 mat_transform, mat_scale, mat_rotate;
	//弾の座標
	D3DXVECTOR3 BulletPos;

	//各方向のベクトル
	//当たり判定に使う
	D3DXVECTOR3 forward;
	D3DXVECTOR3 right;
	D3DXVECTOR3 up;

public:
	Bullet();
	~Bullet();

	//初期化
	void Initialize();
	//実際の動き
	void Update();
	//描画
	void Draw();

	//弾の場所を決定
	void BulletPosSet(D3DXVECTOR3 pPos);
	//弾を発射しているかのフラグ
	bool BulletShotFlag;

	//弾の当たり判定
	OrientedBoundingBox bulletObb;

};