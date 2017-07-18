#pragma once

#include "../Direct3D/mesh.h"
#include "../Direct3D/Direct3D.h"
#include "../Direct3D/Texture.h"
#include "../Direct3D/Sprite.h"
#include "../Direct3D/camera.h"
#include "../BoundingBox/BoundingBox.h"
#include "../Input/directInput.h"

#include "../Scene/SceneManager.h"
#include "../Scene/ISceneChanger.h"
#include "../Scene/BaseScene.h"

#include "Sound.h"
#include "SoundEffect.h"
#include "../Fade/Fade.h"
#include "GameState.h"
#include "NumDisplay.h"

//テクスチャを点滅させる関係
#define TEXTURE_DARW_SPEED 30
#define TEXTURE_DARW_TIMING 0

enum RESULTSTATE
{
	Fade_IN,
	PUSHSPACE,
};

class Result : public BaseScene
{
private:

	//1Pが勝利した場合に表示するテクスチャ
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

	Sound sound;
	SoundEffect se;

	Fade fade;
	RESULTSTATE resultState;
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