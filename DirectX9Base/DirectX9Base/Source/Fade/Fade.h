#pragma once

#include "../Direct3D/mesh.h"
#include "../Direct3D/Direct3D.h"
#include "../Direct3D/Texture.h"
#include "../Direct3D/Sprite.h"
#include "../Direct3D/camera.h"
#include "../BoundingBox/BoundingBox.h"
#include "../Input/directInput.h"

//フェードアウト用の数値
#define Fade_Out_ChangeNum 1	//フェードアウト時にα値に加算する数値
#define Fade_Out_End 1			//テクスチャのα値を比べて処理を終了させる数値

//フェードイン用の数値
#define Fade_In_ChangeNum -1	//フェードイン時にα値に加算する数値
#define Fade_In_End 0			//テクスチャのα値を比べて処理を終了させる数値

#define FadeSpeed 0.01f			//フェードイン、フェードアウトの速さ


class Fade
{
private:

	//フェードイン用のテクスチャ
	Texture FadeTex;
	Sprite FadeSprite;

public:
	
	//コンストラクタ
	Fade();
	//デストラクタ
	~Fade();

	//初期化
	void Initialize();
	//描画
	void Draw();

	//フェードインの処理を行う関数
	bool FadeIn();
	//フェードアウトの処理を行う関数
	bool FadeOut();


};