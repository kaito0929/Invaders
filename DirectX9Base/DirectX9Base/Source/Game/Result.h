#pragma once

#include "../Direct3D/Direct3D.h"
#include "../Direct3D/Texture.h"
#include "../Direct3D/Sprite.h"
#include "../Input/directInput.h"

#include "../Scene/SceneManager.h"
#include "../Scene/ISceneChanger.h"
#include "../Scene/BaseScene.h"

#include "Sound.h"
#include "SoundEffect.h"
#include "../Fade/Fade.h"
#include "GameState.h"
#include "NumDisplay.h"

#define Texture_Draw_Speed 30	//テクスチャを点滅させるスピード
#define Texture_Draw_Timing 0	//テクスチャを描画するタイミング

//リザルト画面のフロー
enum RESULT_STATE
{
	FADE_IN,
	PUSHSPACE,
};

class Result : public BaseScene
{
private:

	//リザルト画面に表示するテクスチャ
	Texture ResultTex;
	Sprite ResultSprite;

	//エンターキーを押してもらう指示のテクスチャ
	Texture EnterTex;
	Sprite EnterSprite;

	//フェードアウトを実行するかのフラグ
	//エンターキーを押したならtrueにする
	bool FadeFlag;

	//エンターキーの操作を促すフォントを点滅させるための変数
	int DrawCount;
	bool DrawFlag;

	//音楽再生用
	Sound sound;
	SoundEffect se;

	//フェードイン、フェードアウト用
	Fade fade;

	//リザルト画面のフロー
	RESULT_STATE resultState;
	NumDisplay numDisplay;

public:
	//コンストラクタ
	Result::Result(ISceneChanger* changer);
	//デストラクタ
	~Result();

	//初期化
	void Initialize() override;
	//実際の動き
	void Update() override;
	//描画
	void Draw() override;

	void TextureFlashing();
};