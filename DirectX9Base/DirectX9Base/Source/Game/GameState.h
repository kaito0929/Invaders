#pragma once

#include "../Direct3D/Texture.h"
#include "../Direct3D/Sprite.h"
#include "../Direct3D/Direct3D.h"
#include "../Input/directInput.h"
#include "../Input/Xinput.h"

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


#define Screen_CenterX 650		//画面のx軸での中央の数値
#define Screen_Out -120			//画面外

#define StartTex_Move 25		//スタートの文字を動かす数値
#define Start_Count_Max 10		//プレイヤーの操作が可能になるまでのインターバル

#define ScorePulsNum 20			//スコアに加算する数値
#define RedEnemy_ScorePulsNum 50

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
	Enemy enemy;
	Bullet bullet;
	BlueEnemy blueEnemy;
	RedEnemy redEnemy;
	GreenEnemy greenEnemy;

	//音再生用
	Sound sound;
	SoundEffect se;

	//フェードイン、アウト関係
	Fade fade;
	//背景描画用
	BackGround backGround;

	//スコアの表示用
	NumDisplay numDisplay;

	//メインゲームのフロー
	MAINGAME_STATE mainState;

	//ゲーム開始の合図を行うテクスチャ
	Texture StartTex;
	Sprite StartSprite;

	//スタートのテクスチャのx座標
	int StartTexPosX;
	//スタートの合図がしてからのインターバル
	int StartCount;

	//残り時間
	int Time;
	//残り時間管理用のフレーム
	int TimeFrame;
	//残り時間表示用
	NumDisplay timeDisplay;

	int BulletCount;

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
};