#include "GameState.h"

//ゲームのスコア
//敵を倒す度に20点加算される
int Score;

//コンストラクタ
GameState::GameState(ISceneChanger* changer) : BaseScene(changer)
{
	
}

//デストラクタ
GameState::~GameState()
{
	
}

//初期化
void GameState::Initialize()
{
	player.Initialize();
	enemy.Initialize();
	bullet.Initialize();
	sound.Initialize();
	se.Initialize();
	fade.Initialize();
	backGround.Initialize();

	blueEnemy.Initialize();
	redEnemy.Initialize();
	greenEnemy.Initialize();

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

	Time = 30;
	TimeFrame = 0;

	timeDisplay.LoadTexture("Texture/number.png");
	timeDisplay.SetPosition(200, 100);
	timeDisplay.SetSize(100);

	BulletCount = 0;
}

//描画
void GameState::Draw()
{
	//RenderStateをRENDER_POINTSPRITEに設定
	//背景と敵を描画するまで継続
	Direct3D::SetRenderState(RENDER_POINTSPRITE);
	backGround.Draw();
	//enemy.Draw();
	//enemy.DestroyEffectDraw();
	blueEnemy.Draw();
	redEnemy.Draw();
	greenEnemy.Draw();

	//ポイントスプライトを描画し終わったので
	//RenderStateをRENDER_ALPHABLENDに変更
	Direct3D::SetRenderState(RENDER_ALPHABLEND);
	player.Draw();
	bullet.Draw();
	numDisplay.Draw(Score);
	timeDisplay.Draw(Time);

	StartSprite.SetPos(StartTexPosX, 300);
	Direct3D::DrawSprite(StartSprite, StartTex);
	fade.Draw();

}

void GameState::Update()
{
	DirectInput* pDi = DirectInput::GetInstance();

	switch (mainState)
	{
	case FADE:		//フェードインを開始

		//フェードインが終了したら処理
		if (fade.FadeIn() == true)
		{
			//完全に画面が明るくなったので
			//ステートを変えて、ゲーム開始の合図を処理する
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
			//ステートを変えてゲームを開始
			//プレイヤーの操作を受け付けるように
			mainState = MAIN;
		}

		break;
	case MAIN:		//メインゲーム

		player.Update();
		//enemy.Update();
		bullet.Update();

		blueEnemy.Update();
		redEnemy.Update();
		greenEnemy.Update();

		//BGMを再生開始
		sound.MainSoundPlay();

		//弾の発射位置を設定
		bullet.BulletSet(player.PlayerPos, player.PlayerAngle);

		//弾の発射　操作はスペースキーで行う
		if (pDi->KeyJustPressed(DIK_SPACE))
		{
			//弾を発射していなければ発射される
			if (bullet.BulletShotFlag == false)
			{
				//弾の発射フラグをtrueにして
				//弾が描画されるようにする
				bullet.BulletShotFlag = true;
				//弾の発射音を再生
				se.ShotSEPlay();
			}
		}

		//敵と弾の当たり判定の処理を行う
		//弾が発射されているフラグがtrueの場合のみ
		//当たり判定を行って、弾を消滅させる
		if (bullet.BulletShotFlag == true)
		{
			//発射してから自動で弾を消すための処理
			//弾発射からカウントを加算する
			BulletCount++;
			//カウントが60を超えたらフラグを
			//falseにして弾を消しておく
			//カウントも0にしておく
			if (BulletCount >= 60)
			{
				bullet.BulletShotFlag = false;
				BulletCount = 0;
			}

			//青色の敵と弾の衝突した際に行う処理
			if (blueEnemy.BlueEnemyCollision(bullet.bulletObb))
			{
				//弾の描画フラグをfalseにして
				//画面上から弾を消しておく
				bullet.BulletShotFlag = false;
				//敵を倒したのでスコアを加算
				Score += ScorePulsNum;

				//青色の敵に当たったので時間を回復させる
				//時間管理用のフレームの数値を0に変更
				TimeFrame = 0;
				//一秒だけ時間を加算して、時間を回復
				Time++;

				//弾が消えたのでカウントを0にしておく
				BulletCount = 0;
			}

			//赤色の敵と弾の衝突した際に行う処理
			if (redEnemy.RedEnemyCollision(bullet.bulletObb))
			{
				//処理としては上記と変わらないので
				//コメントはそちらを参考に
				bullet.BulletShotFlag = false;
				//赤色の敵は他の敵より早く動くので
				//加算するスコアは多めにする
				Score += RedEnemy_ScorePulsNum;

				BulletCount = 0;
			}

			//青色の敵と弾の衝突した際に行う処理
			if (greenEnemy.GreenEnemyCollision(bullet.bulletObb))
			{
				//処理としては上記と変わらないので
				//コメントはそちらを参考に
				bullet.BulletShotFlag = false;
				Score += ScorePulsNum;

				BulletCount = 0;
			}
		}

		//敵が指定した位置まで進行してきた場合に処理
		//リザルト画面への遷移を開始させる
		if (enemy.EnemyBorderlineReaching() == true)
		{
			//メインゲームのBGMの再生を終了
			sound.MainSoundStop();
			//リザルト画面へと遷移開始
			mSceneChanger->ChangeScene(STATE_RESULT);
		}

		//スタートのテクスチャを画面外に移動
		if (StartTexPosX != Screen_Out)
		{
			StartTexPosX -= StartTex_Move;
		}



		//--残り時間を管理する処理-----------------------------
		//残り時間を管理するフレームを加算
		TimeFrame++;
		//フレームが60を超えたなら一秒経過となるので
		//残り時間から1引いて、フレームをリセットする
		if (TimeFrame >= 60)
		{
			Time--;
			TimeFrame = 0;
		}

		break;
	}
	
}
