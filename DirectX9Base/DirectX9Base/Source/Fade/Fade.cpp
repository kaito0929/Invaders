#include "Fade.h"

//コンストラクタ
Fade::Fade()
{

}

//デストラクタ
Fade::~Fade()
{

}

//初期化
void Fade::Initialize()
{
	//フェードアウト用のテクスチャ
	FadeTex.Load("Material/fade_w.png");
	FadeSprite.SetPos(650, 400);
	FadeSprite.SetSize(1300, 1100);
	FadeSprite.SetAlpha(1);
}

//描画
void Fade::Draw()
{
	//フェードアウト用の画像を描画
	Direct3D::DrawSprite(FadeSprite, FadeTex);
}

//フェードインの処理を行う関数
//描画しているテクスチャのα値をマイナスしてフェードインを演出
//α値が0になったら、フラグを返して、それに応じて処理を行うことが出来る
bool Fade::FadeIn()
{
	//フェードインを行う
	FadeSprite.SetAlpha(FadeSprite.GetAlpha() + (FadeSpeed*Fade_In_ChangeNum));

	//テクスチャのα値が0になったらフラグを返す
	if (FadeSprite.GetAlpha() == Fade_In_End)
	{
		return true;
	}

	return false;
}

//フェードアウトの処理を行う関数
//描画しているテクスチャのα値をプラスしてフェードアウトを演出
//α値が1になったら、上記と同じようにフラグを返す
bool Fade::FadeOut()
{
	//フェードアウトを行う
	FadeSprite.SetAlpha(FadeSprite.GetAlpha() + (FadeSpeed*Fade_Out_ChangeNum));

	//テクスチャのα値が1になったらフラグを返す
	if (FadeSprite.GetAlpha() == Fade_Out_End)
	{
		return true;
	}

	return false;
}

