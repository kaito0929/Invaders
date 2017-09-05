#pragma once

#include "../Direct3D/Direct3D.h"
#include "../Direct3D/Texture.h"
#include "../Direct3D/Sprite.h"


//自機か敵が倒された時のエフェクト
struct DestroyEffect
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 angle;		//方向
	float speed;			//速さ
	int count;				//描画する時間
	bool used;				//使用中か
};


class Effect
{
private:


	VERTEX *vertex;

public:
	Effect();
	~Effect();

	//初期化
	void Initialize();
	//実際の動き
	void Update();
	//描画
	void Draw();

	void EffectSet(D3DXVECTOR3 pos);
	void EffectMove();
};