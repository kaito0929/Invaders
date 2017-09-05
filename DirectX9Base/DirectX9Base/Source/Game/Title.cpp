#include "Title.h"

Title::Title(ISceneChanger* changer) : BaseScene(changer)
{

}

Title::~Title()
{

}

void Title::Initialize()
{
	//�^�C�g����ʂ̕`��
	TitleTex.Load("Texture/title.png");
	TitleSprite.SetPos(650, 450);
	TitleSprite.SetSize(1300, 900);

	//�G���^�[�������悤�Ɏw������e�N�X�`��
	EnterTex.Load("Texture/pushspace.png");
	EnterSprite.SetPos(650, 700);
	EnterSprite.SetSize(600, 400);

	sound.Initialize();
	se.Initialize();

	DrawCount = 0;
	DrawFlag = true;

	TutorialTex[0].Load("Texture/setumei2.png");
	TutorialTex[1].Load("Texture/setumei1.png");
	TutorialTex[2].Load("Texture/setumei3.png");

	TutorialSprite.SetPos(650, 400);
	TutorialSprite.SetSize(1300, 800);

	TutorialNumber = 0;

	fade.Initialize();


}


void Title::Draw()
{
	Direct3D::SetRenderState(RENDER_ALPHABLEND);
	//�^�C�g����ʂ̕`��
	Direct3D::DrawSprite(TitleSprite, TitleTex);

	if (DrawFlag == true)
	{
		//�G���^�[�L�[�������悤�Ɏw��
		Direct3D::DrawSprite(EnterSprite, EnterTex);
	}

	if (titleState == TUTORIAL)
	{
		Direct3D::DrawSprite(TutorialSprite, TutorialTex[TutorialNumber]);
	}

	fade.Draw();

	Direct3D::SetRenderState(RENDER_POINTSPRITE);

}

void Title::Update()
{
	DirectInput* pDi = DirectInput::GetInstance();

	sound.TitleSoundPlay();

	switch (titleState)
	{
	case FADEIN:

		if (fade.FadeIn() == true)
		{
			titleState = START;
		}

		break;
	case START:		//�X�y�[�X�L�[�������悤�Ɏw��

		PushKeyDraw();

		//��Փx�I�����ăX�y�[�X�L�[����������t�F�[�h�A�E�g�J�n
		if (pDi->KeyJustPressed(DIK_SPACE))
		{
			se.DecisionSEPlay();
			titleState = TUTORIAL;
		}

		break;

	case TUTORIAL:	//�������

		//��Փx�I�����ăX�y�[�X�L�[����������t�F�[�h�A�E�g�J�n
		if (pDi->KeyJustPressed(DIK_SPACE))
		{
			if (FadeFlag == false)
			{
				se.DecisionSEPlay();
			}
			//�����̉摜��؂�ւ���
			if (TutorialNumber < 2)
			{
				//���l�����Z���Ď��̉摜��`��
				TutorialNumber++;
			}
			//������ʂ��I���
			else
			{
				//�X�y�[�X�L�[����������t�F�[�h�A�E�g�J�n
				if (FadeFlag == false)
				{
					FadeFlag = true;
					sound.TitleSoundStop();
				}
			}

			
		}

		if (FadeFlag == true)
		{
			//���S�ɉ�ʂ��Â��Ȃ����Ȃ�V�[�������C���Q�[���ɕύX
			if (fade.FadeOut() == true)
			{
				sound.TitleSoundStop();
				mSceneChanger->ChangeScene(STATE_MAIN);
			}
		}
		break;
	}

}


//�e�N�X�`����_�ł����邽�߂̏���
void Title::PushKeyDraw()
{
	//�J�E���g���v���X
	DrawCount++;

	//�t���O��true��false�ɐ؂�ւ��邱�Ƃɂ����
	//�e�N�X�`���̕\����\����؂�ւ��Ă���
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