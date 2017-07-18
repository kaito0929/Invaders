#pragma once

#include "../Direct3D/mesh.h"
#include "../Direct3D/Direct3D.h"
#include "../Direct3D/Texture.h"
#include "../Direct3D/Sprite.h"
#include "../Direct3D/camera.h"
#include "../BoundingBox/BoundingBox.h"
#include "../Input/directInput.h"

#include "../Random/Random.h"

#define EnemyType 3					//敵の種類
#define EnemyNum 30					//敵の総数
#define EnemyMoveSpeed 0.1f			//敵の移動速度
#define EnemyBorderlinePosZ 10.0f	//敵が到達してはいけないz座標

#define DestroyEffectNum 20			//敵を倒した時のエフェクトの数


struct DestroyEffect
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 angle;
	float speed;
	int count;
	bool used;
};

class Enemy
{
private:

	//敵のモデル
	Mesh EnemyModel[EnemyType];
	//メッシュに渡す行列を作成
	D3DXMATRIXA16 mat_transform, mat_scale, mat_rotate;

	//敵の位置
	D3DXVECTOR3 EnemyPos[EnemyNum];

	//敵の当たり判定
	OrientedBoundingBox enemyObb[EnemyNum];
	//各方向のベクトル
	//当たり判定に使う
	D3DXVECTOR3 forward;
	D3DXVECTOR3 right;
	D3DXVECTOR3 up;

	//敵の生存フラグ
	//trueならば描画して、falseならば消えるようにする
	bool EnemyAliveFlag[EnemyNum];
	//全ての敵を倒したかの判定
	bool EnemyOllDestroy;

	DestroyEffect destroyEffect[DestroyEffectNum];
	Texture *DestroyTex;

	VERTEX *vertex;
	Random random;

public:

	Enemy();
	~Enemy();

	//初期化
	void Initialize();
	//実際の動き
	void Update();
	//描画
	void Draw();

	//敵との当たり判定を行う関数
	bool EnemyCollision(OrientedBoundingBox obb);

	//敵が一度全滅した時に再度出現させるための関数
	void EnemyReset();

	//敵が消滅する際のエフェクトを描画
	void DestroyEffectDraw();
	//敵がやられた時のエフェクトの位置などを設定する関数
	void DestroyEffectSet();

	bool EnemyBorderlineReaching();
};