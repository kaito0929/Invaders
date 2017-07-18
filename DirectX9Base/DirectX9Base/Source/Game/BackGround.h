#pragma once

#include "../Direct3D/mesh.h"
#include "../Direct3D/Direct3D.h"
#include "../Direct3D/Texture.h"
#include "../Direct3D/Sprite.h"
#include "../Direct3D/camera.h"
#include "../BoundingBox/BoundingBox.h"
#include "../Input/directInput.h"

#include "../Random/Random.h"

//描画するポイントスプライトの数
#define NumStars 5000

//背景用のエフェクトを描画するクラス
class BackGround
{
private:

	//ポイントスプライトの座標
	D3DXVECTOR3 pos[NumStars];
	//ポイントスプライトのテクスチャを取得する変数
	Texture *tex;
	//ポイントスプライト描画用の変数
	VERTEX *vertex;

	//エフェクトの座標を決定するために
	//ランダムで数値を取得するために宣言
	Random random;

public:

	BackGround();
	~BackGround();

	//初期化
	void Initialize();
	//描画
	void Draw();

};