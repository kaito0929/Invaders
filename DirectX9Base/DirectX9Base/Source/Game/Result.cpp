#include "Result.h"

Result::Result(ISceneChanger* changer) : BaseScene(changer)
{

}

Result::~Result()
{

}

void Result::Initialize()
{
	//リザルト画面のテクスチャ
	ResultTex.Load("Texture/result.png");
	ResultSprite.SetPos(650, 400);
	ResultSprite.SetSize(1300, 900);

	//スペースキーを押すように指示するテクスチャ
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
		//スペースキーを押すように指示
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
	case FADE_IN:	//フェードイン

		if (fade.FadeIn() == true)
		{
			resultState = PUSHSPACE;
		}

		break;
	case PUSHSPACE:	//スペースキーを押すように

		//エンターキーを押したならフラグをtrueにしてフェードアウト開始
		if (pDi->KeyJustPressed(DIK_SPACE))
		{
			if (FadeFlag == false)
			{
				se.DecisionSEPlay();
			}
			FadeFlag = true;
		}

		//FadeFlagがtrueなら実行するように
		if (FadeFlag == true)
		{
			//完全に画面が暗くなったならシーンをメインゲームに変更
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

//スペースキーを押すように指示を出すテクスチャを
//点滅させるための関数
void Result::TextureFlashing()
{
	//カウントをプラス
	DrawCount++;

	//フラグのtrue,falseを切り替えることによって
	//テクスチャの表示非表示を切り替える
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