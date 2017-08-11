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
#define EnemyNum 8					//敵の総数
#define EnemyMoveSpeed 0.1f			//敵の移動速度
#define EnemyBorderlinePosZ 10.0f	//敵が到達してはいけないz座標

#define EnemyColumnNum 3			//敵の縦列の長さ
#define EnemyRowNum 10				//敵の横列の長さ

#define DestroyEffectNum 20			//敵を倒した時のエフェクトの数

#define PI 3.141592653589793

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


//================================================================
//クラス名  ：BlueEnemyクラス
//基底クラス：Enemyクラス
//
//内容：Enemyクラスから派生させたクラス。青色の敵のクラス
//================================================================

class BlueEnemy : public Enemy
{
private:
	//敵のモデル
	Mesh BlueEnemyModel;
	//メッシュに渡す行列を作成
	D3DXMATRIXA16 mat_transform, mat_scale, mat_rotate;

	//敵の当たり判定
	OrientedBoundingBox enemyObb[EnemyNum];
	//各方向のベクトル
	//当たり判定に使う
	D3DXVECTOR3 forward;
	D3DXVECTOR3 right;
	D3DXVECTOR3 up;

	//敵の位置
	D3DXVECTOR3 BlueEnemyPos[EnemyNum];

	//敵の生存フラグ
	//trueならば描画して、falseならば消えるようにする
	bool BlueEnemyAliveFlag[EnemyNum];

	//青色の敵の向き（正面）
	D3DXVECTOR3 BlueEnemyYaw[EnemyNum];

	//角度
	float degree;
	//ラジアン
	float radian;

public:

	//コンストラクタ
	BlueEnemy();
	//デストラクタ
	~BlueEnemy();

	//初期化
	void Initialize();
	//実際の動き
	void Update();
	//描画
	void Draw();

	void BlueEnemyReset();

};


//================================================================
//クラス名  ：RedEnemyクラス
//基底クラス：Enemyクラス
//
//内容：Enemyクラスから派生させたクラス。赤色の敵のクラス
//================================================================

class RedEnemy : public Enemy
{
private:

	//敵のモデル
	Mesh RedEnemyModel;
	//メッシュに渡す行列を作成
	D3DXMATRIXA16 mat_transform, mat_scale, mat_rotate;

	//敵の当たり判定
	OrientedBoundingBox enemyObb[EnemyNum];
	//各方向のベクトル
	//当たり判定に使う
	D3DXVECTOR3 forward;
	D3DXVECTOR3 right;
	D3DXVECTOR3 up;

	//敵の位置
	D3DXVECTOR3 RedEnemyPos[EnemyNum];

	//敵の生存フラグ
	//trueならば描画して、falseならば消えるようにする
	bool RedEnemyAliveFlag[EnemyNum];

	//赤色の敵の向き（正面）
	D3DXVECTOR3 RedEnemyYaw[EnemyNum];

public:

	//コンストラクタ
	RedEnemy();
	//デストラクタ
	~RedEnemy();

	//初期化
	void Initialize();
	//実際の動き
	void Update();
	//描画
	void Draw();

	void RedEnemyReset();

};


//================================================================
//クラス名  ：GreenEnemyクラス
//基底クラス：Enemyクラス
//
//内容：Enemyクラスから派生させたクラス。緑色の敵のクラス
//================================================================

class GreenEnemy : public Enemy
{
private:

	//敵のモデル
	Mesh GreenEnemyModel;
	//メッシュに渡す行列を作成
	D3DXMATRIXA16 mat_transform, mat_scale, mat_rotate;

	//敵の当たり判定
	OrientedBoundingBox enemyObb[EnemyNum];
	//各方向のベクトル
	//当たり判定に使う
	D3DXVECTOR3 forward;
	D3DXVECTOR3 right;
	D3DXVECTOR3 up;

	//敵の位置
	D3DXVECTOR3 GreenEnemyPos[EnemyNum];

	//敵の生存フラグ
	//trueならば描画して、falseならば消えるようにする
	bool GreenEnemyAliveFlag[EnemyNum];

	//緑色の敵の向き（正面）
	D3DXVECTOR3 GreenEnemyYaw[EnemyNum];

public:

	//コンストラクタ
	GreenEnemy();
	//デストラクタ
	~GreenEnemy();

	//初期化
	void Initialize();
	//実際の動き
	void Update();
	//描画
	void Draw();

	void GreenEnemyReset();

};