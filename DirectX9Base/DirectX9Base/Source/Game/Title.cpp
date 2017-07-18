#include "Title.h"

Title::Title(ISceneChanger* changer) : BaseScene(changer)
{

}

Title::~Title()
{

}

void Title::Initialize()
{
	//タイトル画面の描画
	TitleTex.Load("Texture/title.png");
	TitleSprite.SetPos(630, 400);
	TitleSprite.SetSize(1300, 900);

	//エンターを押すように指示するテクスチャ
	EnterTex.Load("Texture/pushspace.png");
	EnterSprite.SetPos(650, 700);
	EnterSprite.SetSize(600, 400);

	sound.Initialize();
	se.Initialize();

	DrawCount = 0;
	DrawFlag = true;

	fade.Initialize();
}


void Title::Draw()
{
	Direct3D::SetRenderState(RENDER_ALPHABLEND);

	//タイトル画面の描画
	Direct3D::DrawSprite(TitleSprite, TitleTex);

	if (DrawFlag == true)
	{
		//エンターキーを押すように指示
		Direct3D::DrawSprite(EnterSprite, EnterTex);
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
	case START:		//スペースキーを押すように指示

		PushKeyDraw();

		//難易度選択してスペースキーを押したらフェードアウト開始
		if (pDi->KeyJustPressed(DIK_SPACE))
		{
			if (FadeFlag == false)
			{
				FadeFlag = true;
				se.DecisionSEPlay();
			}
		}

		if (FadeFlag == true)
		{
			//完全に画面が暗くなったならシーンをメインゲームに変更
			if (fade.FadeOut() == true)
			{
				sound.TitleSoundStop();
				mSceneChanger->ChangeScene(STATE_MAIN);
			}
		}

		break;
	}

}


//テクスチャを点滅させるための処理
void Title::PushKeyDraw()
{
	//カウントをプラス
	DrawCount++;

	//フラグをtrueとfalseに切り替えることによって
	//テクスチャの表示非表示を切り替えていく
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