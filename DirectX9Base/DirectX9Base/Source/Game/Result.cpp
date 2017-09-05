#include "Result.h"

Result::Result(ISceneChanger* changer) : BaseScene(changer)
{

}

Result::~Result()
{

}

void Result::Initialize()
{
	//���U���g��ʂ̃e�N�X�`��
	ResultTex.Load("Texture/result.png");
	ResultSprite.SetPos(650, 400);
	ResultSprite.SetSize(1300, 900);

	//�X�y�[�X�L�[�������悤�Ɏw������e�N�X�`��
	EnterTex.Load("Texture/pushspace.png");
	EnterSprite.SetPos(650, 700);
	EnterSprite.SetSize(600, 400);

	fade.Initialize();
	sound.Initialize();
	se.Initialize();

	resultState = FADE_IN;

	numDisplay.LoadTexture("Texture/number.png");
	numDisplay.SetPosition(1200, 100);
	numDisplay.SetSize(150);
}

void Result::Draw()
{
	Direct3D::SetRenderState(RENDER_ALPHABLEND);
	Direct3D::DrawSprite(ResultSprite, ResultTex);

	if (DrawFlag == true)
	{
		//�X�y�[�X�L�[�������悤�Ɏw��
		Direct3D::DrawSprite(EnterSprite, EnterTex);
	}

	numDisplay.Draw(Score);

	fade.Draw();
}

void Result::Update()
{
	DirectInput* pDi = DirectInput::GetInstance();

	sound.ResultSoundPlay();

	switch (resultState)
	{
	case FADE_IN:	//�t�F�[�h�C��

		if (fade.FadeIn() == true)
		{
			resultState = PUSHSPACE;
		}

		break;
	case PUSHSPACE:	//�X�y�[�X�L�[�������悤��

		//�G���^�[�L�[���������Ȃ�t���O��true�ɂ��ăt�F�[�h�A�E�g�J�n
		if (pDi->KeyJustPressed(DIK_SPACE))
		{
			if (FadeFlag == false)
			{
				se.DecisionSEPlay();
			}
			FadeFlag = true;
		}

		//FadeFlag��true�Ȃ���s����悤��
		if (FadeFlag == true)
		{
			//���S�ɉ�ʂ��Â��Ȃ����Ȃ�V�[�������C���Q�[���ɕύX
			if (fade.FadeOut() == true)
			{
				sound.ResultSoundStop();
				mSceneChanger->ChangeScene(STATE_TITLE);
			}
		}

		TextureFlashing();

		break;
	}
	
}

//�X�y�[�X�L�[�������悤�Ɏw�����o���e�N�X�`����
//�_�ł����邽�߂̊֐�
void Result::TextureFlashing()
{
	//�J�E���g���v���X
	DrawCount++;

	//�t���O��true,false��؂�ւ��邱�Ƃɂ����
	//�e�N�X�`���̕\����\����؂�ւ���
	if (DrawFlag == false)
	{
		if (DrawCount % Texture_Draw_Speed == Texture_Draw_Timing)
		{
			DrawFlag = true;
		}
	}
	else
	{
		if (DrawCount % Texture_Draw_Speed == Texture_Draw_Timing)
		{
			DrawFlag = false;
		}
	}

}