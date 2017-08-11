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

#define EnemyColumnNum 3			//敵の縦列の長さ
#define EnemyRowNum 10				//敵の横列の長さ

#define DestroyEffectNum 20			//敵を倒した時のエフェクトの数

//敵がやられた際のエフェクト用の構造体
struct DestroyEffect
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 angle;		//方向
	float speed;			//速さ
	int count;				//描画する時間
	bool used;				//使用中か
};


//================================================================
//クラス名  ：Enemyクラス
//基底クラス：
//
//内容：このクラスをユニットの基底クラスとして派生させていく
//================================================================

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

	DestroyEffect destroyEffect[DestroyEffectNum][EnemyNum];
	Texture *DestroyTex;

	VERTEX *vertex;
	Random random;

	D3DXVECTOR3 angle[EnemyNum];
	D3DXVECTOR3 angleTest[EnemyNum];

public:

	//コンストラクタ
	Enemy();
	//デストラクタ
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

	//敵が指定した位置まで到達した場合にtrueを返し
	//画面遷移を開始させる関数
	bool EnemyBorderlineReaching();
};