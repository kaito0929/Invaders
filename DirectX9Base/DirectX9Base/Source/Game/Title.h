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


//テクスチャを点滅させる関係
#define Texture_Draw_Speed 30
#define Texture_Draw_Timing 0

//タイトルのフロー
enum TITLESTATE
{
	FADEIN,
	START,
	TUTORIAL,
};


class Title : public BaseScene
{
private:

	//タイトルのテクスチャ
	Texture TitleTex;
	Sprite TitleSprite;

	//エンターキーを押してもらう指示のテクスチャ
	Texture EnterTex;
	Sprite EnterSprite;

	//フェードアウトを実行するかのフラグ
	//スペースキーを押したならtrueにする
	bool FadeFlag;

	//操作を促すフォントを点滅させるための変数
	int DrawCount;
	bool DrawFlag;

	//タイトル画面でのフロー
	TITLESTATE titleState;

	Sound sound;
	SoundEffect se;

	Texture TutorialTex[3];
	Sprite TutorialSprite;

	int TutorialNumber;

	Fade fade;

public:
	//コンストラクタ
	Title::Title(ISceneChanger* changer);
	//デストラクタ
	~Title();

	//初期化
	void Initialize() override;
	//実際の動き
	void Update() override;
	//描画
	void Draw() override;

	void PushKeyDraw();

};