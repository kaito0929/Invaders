#include "Fade.h"

Fade::Fade()
{

}

Fade::~Fade()
{

}

void Fade::Initialize()
{

	//フェードアウト用のテクスチャ
	FadeTex.Load("Material/fade_b.png");
	FadeSprite.SetPos(650, 400);
	FadeSprite.SetSize(1300, 1100);
	FadeSprite.SetAlpha(1);

}

void Fade::Draw()
{
	//フェードアウト用の画像を描画
	Direct3D::DrawSprite(FadeSprite, FadeTex);
}

void Fade::Update()
{

}

bool Fade::FadeIn()
{
	//フェードインを行う
	FadeSprite.SetAlpha(FadeSprite.GetAlpha() + (FADE_SPEED*FADE_IN_CHANGENUM));

	if (FadeSprite.GetAlpha() == FADE_IN_END)
	{
		return true;
	}

	return false;
}

bool Fade::FadeOut()
{
	//フェードアウトを行う
	FadeSprite.SetAlpha(FadeSprite.GetAlpha() + (FADE_SPEED*FADE_OUT_CHANGENUM));

	if (FadeSprite.GetAlpha() == FADE_OUT_END)
	{
		return true;
	}

	return false;
}

