#pragma once

#include "../Direct3D/Texture.h"
#include "../Direct3D/Sprite.h"
#include "../Direct3D/mesh.h"
#include "../Direct3D/Direct3D.h"
#include "../Direct3D/camera.h"
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
#include "../Random/Random.h"


//画面のx軸での中央の数値
#define Screen_CenterX 650
//画面外
#define Screen_Out -120

//スタートの文字を動かす数値
#define StartTex_Move 25
//プレイヤーの操作が可能になるまでのインターバル
#define Start_Count_Max 10

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

	//音再生用
	Sound sound;
	SoundEffect se;

	//スコアの表示用
	NumDisplay numDisplay;

	MAINGAME_STATE mainState;

	//フェードイン、アウト関係
	Fade fade;
	//背景描画用
	BackGround backGround;

	//ゲーム開始の合図を行うテクスチャ
	Texture StartTex;
	Sprite StartSprite;

	//スタートのテクスチャのx座標
	int StartTexPosX;
	//スタートの合図がしてからのインターバル
	int StartCount;

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