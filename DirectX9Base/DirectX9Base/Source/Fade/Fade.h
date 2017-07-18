#pragma once

#include "../Direct3D/mesh.h"
#include "../Direct3D/Direct3D.h"
#include "../Direct3D/Texture.h"
#include "../Direct3D/Sprite.h"
#include "../Direct3D/camera.h"
#include "../BoundingBox/BoundingBox.h"
#include "../Input/directInput.h"

//フェードアウト用の数値
#define FADE_OUT_CHANGENUM 1 
#define FADE_OUT_END 1
//フェードイン用の数値
#define FADE_IN_CHANGENUM -1 
#define FADE_IN_END 0

#define FADE_SPEED 0.01f


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
	//実際の動き
	void Update();
	//描画
	void Draw();

	bool FadeIn();
	bool FadeOut();


};