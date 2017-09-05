#pragma once

#include "../Direct3D/mesh.h"
#include "../Direct3D/Direct3D.h"
#include "../Direct3D/Texture.h"
#include "../Direct3D/Sprite.h"
#include "../Direct3D/camera.h"
#include "../BoundingBox/BoundingBox.h"
#include "../Input/directInput.h"

#include "../Random/Random.h"

#include "../Game/SoundEffect.h"

#define EnemyType 4					//敵の種類
#define EnemyMoveSpeed 0.1f			//敵の移動速度
#define RedEnemyMoveSpeed 0.3f		//赤色の敵の移動速度

#define DestroyEffectNum 20	//敵を倒した時のエフェクトの数

#define PI 3.141592653589793f

#define BlueEnemyNum 6		//青色の敵の総数
#define RedEnemyNum 6		//赤色の敵の総数
#define GreenEnemyNum 24	//緑色の敵の総数
#define PurpleEnemyNum 12	//紫色の敵の総数

#define BulletShotTiming 2	//敵が弾を発射するタイミング
#define BulletEndTiming 3	//敵の弾が消えるタイミング


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
public:

	//コンストラクタ
	Enemy();
	//デストラクタ
	~Enemy();

	//敵のモデル
	Mesh EnemyModel[EnemyType];
	//メッシュに渡す行列を作成
	D3DXMATRIXA16 mat_transform, mat_scale, mat_rotate;

	//各方向のベクトル
	//当たり判定に使う
	D3DXVECTOR3 forward;
	D3DXVECTOR3 right;
	D3DXVECTOR3 up;

	Texture *DestroyTex;
	Random random;

	//全ての敵を倒したかの判定
	bool EnemyOllDestroy;

	//角度
	float degree;
	//ラジアン
	float radian;

	float EnemyRadius[3];

	SoundEffect se;
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


	//敵の位置
	D3DXVECTOR3 BlueEnemyPos[BlueEnemyNum];

	//敵の生存フラグ
	//trueならば描画して、falseならば消えるようにする
	bool BlueEnemyAliveFlag[BlueEnemyNum];

	//青色の敵の向き（正面）
	D3DXVECTOR3 BlueEnemyYaw[BlueEnemyNum];

	DestroyEffect destroyEffect[DestroyEffectNum][BlueEnemyNum];

	VERTEX *vertex;

	//青色の敵を全部倒した時のフラグ
	bool BlueEnemyOllDown;

	float EnemyRadian[BlueEnemyNum];


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

	bool BlueEnemyCollision(OrientedBoundingBox obb);

	//敵が消滅する際のエフェクトを描画
	void DestroyEffectDraw();
	//敵がやられた時のエフェクトの位置などを設定する関数
	void DestroyEffectSet();

	bool GetBlueEnemyOllDown() { return BlueEnemyOllDown; }

	//敵の当たり判定
	OrientedBoundingBox enemyObb[BlueEnemyNum];


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


	//敵の位置
	D3DXVECTOR3 RedEnemyPos[RedEnemyNum];

	//敵の生存フラグ
	//trueならば描画して、falseならば消えるようにする
	bool RedEnemyAliveFlag[RedEnemyNum];

	//赤色の敵の向き（正面）
	D3DXVECTOR3 RedEnemyYaw[RedEnemyNum];

	DestroyEffect destroyEffect[DestroyEffectNum][RedEnemyNum];

	VERTEX *vertex;

	//赤色の敵を全部倒した時のフラグ
	bool RedEnemyOllDown;


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

	bool RedEnemyCollision(OrientedBoundingBox obb);

	//敵が消滅する際のエフェクトを描画
	void DestroyEffectDraw();
	//敵がやられた時のエフェクトの位置などを設定する関数
	void DestroyEffectSet();

	bool GetRedEnemyOllDown() { return RedEnemyOllDown; }

	//敵の当たり判定
	OrientedBoundingBox enemyObb[RedEnemyNum];


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

	//敵の位置
	D3DXVECTOR3 GreenEnemyPos[GreenEnemyNum];

	//敵の生存フラグ
	//trueならば描画して、falseならば消えるようにする
	bool GreenEnemyAliveFlag[GreenEnemyNum];

	//緑色の敵の向き（正面）
	D3DXVECTOR3 GreenEnemyYaw[GreenEnemyNum];

	DestroyEffect destroyEffect[DestroyEffectNum][GreenEnemyNum];

	VERTEX *vertex;

	//緑色の敵を全部倒した時のフラグ
	bool GreenEnemyOllDown;

	//緑の敵が発射する弾
	Mesh EnemyBullet;
	//メッシュに渡す行列を作成
	D3DXMATRIXA16 mat_bulletTransform, mat_bulletScale, mat_bulletRotate;

	//弾を発射しているかのフラグ
	bool GreenEnemyShotFlag[GreenEnemyNum];

	//弾発射用のカウント
	int ShotCount;
	//弾発射を管理するフレーム
	int ShotFrame;

	//弾が発射済みかのフラグ
	bool BulletFiredFlag;

	// 敵を波打たせるための数値
	float Wave;

	D3DXVECTOR3 BulletPos[GreenEnemyNum];
	D3DXVECTOR3 BulletAngle[GreenEnemyNum];

	//弾の当たり判定
	OrientedBoundingBox bulletObb[GreenEnemyNum];

	//各方向のベクトル
	//当たり判定に使う
	D3DXVECTOR3 forward_bullet;
	D3DXVECTOR3 right_bullet;
	D3DXVECTOR3 up_bullet;

	float EnemyRadian[GreenEnemyNum];


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

	bool GreenEnemyCollision(OrientedBoundingBox obb);


	//敵が消滅する際のエフェクトを描画
	void DestroyEffectDraw();
	//敵がやられた時のエフェクトの位置などを設定する関数
	void DestroyEffectSet();

	//敵の弾を発射させる関数
	void EnemyBulletShot();
	void EnemyBulletSet();

	bool EnemyBulletCollision(OrientedBoundingBox obb);

	bool GetGreenEnemyOllDown() { return GreenEnemyOllDown; }

	//敵の当たり判定
	OrientedBoundingBox enemyObb[GreenEnemyNum];


};


//================================================================
//クラス名  ：PurpleEnemyクラス
//基底クラス：Enemyクラス
//
//内容：Enemyクラスから派生させたクラス。紫色の敵のクラス
//================================================================

class PurpleEnemy : public Enemy
{
private:

	//敵の位置
	D3DXVECTOR3 PurpleEnemyPos[PurpleEnemyNum];

	//敵の生存フラグ
	//trueならば描画して、falseならば消えるようにする
	bool PurpleEnemyAliveFlag[PurpleEnemyNum];

	//緑色の敵の向き（正面）
	D3DXVECTOR3 PurpleEnemyYaw[PurpleEnemyNum];

	DestroyEffect destroyEffect[DestroyEffectNum][PurpleEnemyNum];

	VERTEX *vertex;

	//紫色の敵を全部倒した時のフラグ
	bool PurpleEnemyOllDown;

	int HitPoint[PurpleEnemyNum];

	float EnemyRadian[PurpleEnemyNum];


public:

	//コンストラクタ
	PurpleEnemy();
	//デストラクタ
	~PurpleEnemy();

	//初期化
	void Initialize();
	//実際の動き
	void Update();
	//描画
	void Draw();

	//紫色の敵の位置や生存フラグなどの初期化
	void PurpleEnemyReset();

	//紫色の敵の衝突判定
	bool PurpleEnemyCollision(OrientedBoundingBox obb, bool* flag);

	//敵が消滅する際のエフェクトを描画
	void DestroyEffectDraw();
	//敵がやられた時のエフェクトの位置などを設定する関数
	void DestroyEffectSet();

	//紫色の敵が全て倒された時のフラグを渡す関数
	bool GetPurpleEnemyOllDown() { return PurpleEnemyOllDown; }

	//敵の当たり判定
	OrientedBoundingBox enemyObb[PurpleEnemyNum];



};
