#pragma once

#include "../Direct3D/Texture.h"
#include "../Direct3D/Sprite.h"
#include "../Direct3D/Direct3D.h"
#include "../Input/directInput.h"
#include "../Input/Xinput.h"
#include "../BoundingBox/BoundingBox.h"

#include "../Scene/SceneManager.h"
#include "../Scene/ISceneChanger.h"
#include "../Scene/BaseScene.h"

#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Sound.h"
#include "SoundEffect.h"
#include "NumDisplay.h"
#include "BackGround.h"
#include "../Fade/Fade.h"


#define Screen_CenterX 650			//画面のx軸での中央の数値
#define Screen_Out -120				//画面外
#define StartTex_Move 25			//スタートの文字を動かす数値
#define Start_Count_Max 10			//プレイヤーの操作が可能になるまでのインターバル
#define ScoreAddNum 20				//スコアに加算する数値
#define RedEnemy_ScoreAddNum 50		//赤色の敵を倒した場合に加算される数値
#define OneSecond 60				//一秒経過を判定する数値
#define Player_Draw_Speed 5			//敵の弾が当たった際の点滅させる速さ
#define Player_Draw_Timing 0		//点滅する時の表示するタイミング
#define Enemy_Reset_Timing 15		//敵の位置などを初期化するタイミング
#define TimeAddNum 3				//青色の敵を倒した際に残り時間に加算する数値
#define PlayerRigorTime 120			//プレイヤーの硬直時間

extern int Score;

//メインゲームのフロー
enum MAINGAME_STATE
{
	FADE,	//フェードイン
	SIGNAL,	//開始の合図
	MAIN,	//メインの開始
};

class GameState : public BaseScene
{
private:

	Player player;
	Bullet bullet;

	Enemy enemy;
	BlueEnemy blueEnemy;
	RedEnemy redEnemy;
	GreenEnemy greenEnemy;
	PurpleEnemy purpleEnemy;

	//音再生用
	Sound sound;
	SoundEffect se;

	//フェードイン、アウト関係
	Fade fade;

	//背景描画用
	BackGround backGround;

	//スコアの表示用
	NumDisplay numDisplay;
	//数字がスコアと分かるようにするテクスチャ
	Texture ScoreTex;
	Sprite ScoreSprite;

	//メインゲームのフロー
	MAINGAME_STATE mainState;

	//ゲーム開始の合図を行うテクスチャ
	Texture StartTex;
	Sprite StartSprite;

	//スタートのテクスチャのx座標
	float StartTexPosX;
	//スタートの合図がしてからのインターバル
	int StartCount;

	//残り時間
	int Time;
	//残り時間管理用のフレーム
	int TimeFrame;
	//残り時間表示用
	NumDisplay timeDisplay;

	//残り時間を示す数字のテクスチャ
	Texture TimeTex;
	//残り時間を示す数字の位置や大きさ
	Sprite TimeSprite;

	//スコアと残り時間が増えたのが
	//分かりやすくなるテクスチャ
	Texture NumPlusTex[3];
	Sprite NumPlusSprite[3];

	//敵の弾と衝突したかのフラグ
	bool PlayerCollisionFlag;
	//敵の弾と衝突してからのカウント
	int PlayerCollisionCount;

	//自機を点滅させるためのフラグ
	bool PlayerDrawFlag;

	//今発射している弾
	int BulletNum;

public:

	//コンストラクタ
	GameState::GameState(ISceneChanger* changer);
	//デストラクタ
	~GameState();			

	//初期化
	void Initialize() override;
	//実際の動き
	void Update() override;
	//描画
	void Draw() override;

	void TimeCount();

	//敵が移動可能範囲から抜けたかの判定を行う関数
	bool EnemyMoveMax();
};