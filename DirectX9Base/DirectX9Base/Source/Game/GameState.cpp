#include "GameState.h"

int Score;

GameState::GameState(ISceneChanger* changer) : BaseScene(changer)
{
	
}

GameState::~GameState()
{
	
}

void GameState::Initialize()
{
	player.Initialize();
	enemy.Initialize();
	bullet.Initialize();
	sound.Initialize();
	se.Initialize();
	fade.Initialize();
	backGround.Initialize();

	Score = 0;

	numDisplay.LoadTexture("Texture/number.png");
	numDisplay.SetPosition(1100, 100);
	numDisplay.SetSize(100);

	StartTex.Load("Texture/start.png");
	StartSprite.SetPos(StartTexPosX, 300);
	StartSprite.SetSize(400, 200);

	StartTexPosX = 1500;
	StartCount = 0;

	mainState = FADE;

}

void GameState::Draw()
{
	//RenderStateをRENDER_POINTSPRITEに設定
	//背景と敵を描画するまで継続
	Direct3D::SetRenderState(RENDER_POINTSPRITE);
	backGround.Draw();
	enemy.Draw();

	//ポイントスプライトを描画し終わったので
	//RenderStateをRENDER_ALPHABLENDに変更
	Direct3D::SetRenderState(RENDER_ALPHABLEND);
	player.Draw();
	bullet.Draw();
	numDisplay.Draw(Score);

	StartSprite.SetPos(StartTexPosX, 300);
	Direct3D::DrawSprite(StartSprite, StartTex);
	fade.Draw();

}

void GameState::Update()
{
	DirectInput* pDi = DirectInput::GetInstance();

	switch (mainState)
	{
	case FADE:	//フェードインを開始

		//フェードインが終了したら処理
		if (fade.FadeIn() == true)
		{
			mainState = SIGNAL;
		}

		break;
	case SIGNAL:	//開始の合図を出す

		//スタートのテクスチャを画面中央まで移動
		if (StartTexPosX != Screen_CenterX)
		{
			StartTexPosX -= StartTex_Move;
		}
		else
		{
			//画面中央に移動したらSEを再生
			se.StartSEPlay();
			//プレイヤーの操作が可能になるまでのカウントを加算
			StartCount++;
		}

		//カウントが10を超えたらプレイヤーの操作を可能に
		if (StartCount >= Start_Count_Max)
		{
			mainState = MAIN;
		}


		break;
	case MAIN:		//メインゲーム

		player.Update();
		enemy.Update();
		bullet.Update();
		sound.MainSoundPlay();

		//弾の発射位置を設定
		bullet.BulletPosSet(player.PlayerPos);

		//弾の発射　操作はスペースキーで行う
		if (pDi->KeyJustPressed(DIK_SPACE))
		{
			if (bullet.BulletShotFlag == false)
			{
				bullet.BulletShotFlag = true;
				se.ShotSEPlay();
			}
		}

		if (bullet.BulletShotFlag == true)
		{
			//弾と敵の当たり判定を処理
			if (enemy.EnemyCollision(bullet.bulletObb))
			{
				bullet.BulletShotFlag = false;
				Score += 20;
			}
		}

		if (enemy.EnemyBorderlineReaching() == true)
		{
			mSceneChanger->ChangeScene(STATE_RESULT);
		}

		//スタートのテクスチャを画面外に移動
		if (StartTexPosX != Screen_Out)
		{
			StartTexPosX -= StartTex_Move;
		}

		break;
	}
	
}
