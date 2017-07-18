#include "Fade.h"

Fade::Fade()
{

}

Fade::~Fade()
{

}

void Fade::Initialize()
{

	//�t�F�[�h�A�E�g�p�̃e�N�X�`��
	FadeTex.Load("Material/fade_b.png");
	FadeSprite.SetPos(650, 400);
	FadeSprite.SetSize(1300, 1100);
	FadeSprite.SetAlpha(1);

}

void Fade::Draw()
{
	//�t�F�[�h�A�E�g�p�̉摜��`��
	Direct3D::DrawSprite(FadeSprite, FadeTex);
}

void Fade::Update()
{

}

bool Fade::FadeIn()
{
	//�t�F�[�h�C�����s��
	FadeSprite.SetAlpha(FadeSprite.GetAlpha() + (FADE_SPEED*FADE_IN_CHANGENUM));

	if (FadeSprite.GetAlpha() == FADE_IN_END)
	{
		return true;
	}

	return false;
}

bool Fade::FadeOut()
{
	//�t�F�[�h�A�E�g���s��
	FadeSprite.SetAlpha(FadeSprite.GetAlpha() + (FADE_SPEED*FADE_OUT_CHANGENUM));

	if (FadeSprite.GetAlpha() == FADE_OUT_END)
	{
		return true;
	}

	return false;
}

