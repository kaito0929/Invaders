#include "Fade.h"

//�R���X�g���N�^
Fade::Fade()
{

}

//�f�X�g���N�^
Fade::~Fade()
{

}

//������
void Fade::Initialize()
{
	//�t�F�[�h�A�E�g�p�̃e�N�X�`��
	FadeTex.Load("Material/fade_w.png");
	FadeSprite.SetPos(650, 400);
	FadeSprite.SetSize(1300, 1100);
	FadeSprite.SetAlpha(1);
}

//�`��
void Fade::Draw()
{
	//�t�F�[�h�A�E�g�p�̉摜��`��
	Direct3D::DrawSprite(FadeSprite, FadeTex);
}

//�t�F�[�h�C���̏������s���֐�
//�`�悵�Ă���e�N�X�`���̃��l���}�C�i�X���ăt�F�[�h�C�������o
//���l��0�ɂȂ�����A�t���O��Ԃ��āA����ɉ����ď������s�����Ƃ��o����
bool Fade::FadeIn()
{
	//�t�F�[�h�C�����s��
	FadeSprite.SetAlpha(FadeSprite.GetAlpha() + (FadeSpeed*Fade_In_ChangeNum));

	//�e�N�X�`���̃��l��0�ɂȂ�����t���O��Ԃ�
	if (FadeSprite.GetAlpha() == Fade_In_End)
	{
		return true;
	}

	return false;
}

//�t�F�[�h�A�E�g�̏������s���֐�
//�`�悵�Ă���e�N�X�`���̃��l���v���X���ăt�F�[�h�A�E�g�����o
//���l��1�ɂȂ�����A��L�Ɠ����悤�Ƀt���O��Ԃ�
bool Fade::FadeOut()
{
	//�t�F�[�h�A�E�g���s��
	FadeSprite.SetAlpha(FadeSprite.GetAlpha() + (FadeSpeed*Fade_Out_ChangeNum));

	//�e�N�X�`���̃��l��1�ɂȂ�����t���O��Ԃ�
	if (FadeSprite.GetAlpha() == Fade_Out_End)
	{
		return true;
	}

	return false;
}

