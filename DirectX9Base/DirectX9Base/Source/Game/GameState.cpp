#include "GameState.h"

//ゲームのスコア
//敵を倒す度に加算される
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
	bullet.Initialize();
	sound.Initialize();
	se.Initialize();
	fade.Initialize();
	backGround.Initialize();

	blueEnemy.Initialize();
	redEnemy.Initialize();
	greenEnemy.Initialize();
	purpleEnemy.Initialize();

	Score = 0;

	numDisplay.LoadTexture("Texture/number.png");
	numDisplay.SetPosition(400, 50);
	numDisplay.SetSize(50);

	ScoreTex.Load("Texture/score.png");
	ScoreSprite.SetPos(100, 50);
	ScoreSprite.SetSize(160, 110);

	StartTex.Load("Texture/start.png");
	StartSprite.SetPos(StartTexPosX, 300);
	StartSprite.SetSize(400, 200);

	StartTexPosX = 1500;
	StartCount = 0;

	mainState = FADE;

	Time = 30;
	TimeFrame = 0;

	timeDisplay.LoadTexture("Texture/number.png");
	timeDisplay.SetPosition(1260, 50);
	timeDisplay.SetSize(50);

	TimeTex.Load("Texture/time.png");
	TimeSprite.SetPos(1100,50);
	TimeSprite.SetSize(160,110);

	NumPlusTex[0].Load("Texture/plus20.png");
	NumPlusTex[1].Load("Texture/plus50.png");
	NumPlusTex[2].Load("Texture/plus3.png");
	NumPlusSprite[0].SetPos(360,100);
	NumPlusSprite[1].SetPos(360, 100);
	NumPlusSprite[2].SetPos(1225, 100);

	for (int i = 0; i < 3; i++)
	{
		NumPlusSprite[i].SetSize(80, 50);
		NumPlusSprite[i].SetAlpha(0);
	}

	PlayerCollisionFlag = false;
	PlayerDrawFlag = true;
	PlayerCollisionCount = 0;

	BulletNum = 0;
}

//描画
void GameState::Draw()
{
	//RenderStateをRENDER_POINTSPRITEに設定
	//背景と敵を描画するまで継続
	Direct3D::SetRenderState(RENDER_POINTSPRITE);
	backGround.Draw();
	blueEnemy.Draw();
	blueEnemy.DestroyEffectDraw();
	redEnemy.Draw();
	redEnemy.DestroyEffectDraw();
	greenEnemy.Draw();
	greenEnemy.DestroyEffectDraw();
	purpleEnemy.Draw();
	purpleEnemy.DestroyEffectDraw();

	player.EffectDraw();

	//ポイントスプライトを描画し終わったので
	//RenderStateをRENDER_ALPHABLENDに変更
	Direct3D::SetRenderState(RENDER_ALPHABLEND);

	if (PlayerDrawFlag == true)
	{
		player.Draw();
	}
	bullet.Draw();
	numDisplay.Draw(Score);
	timeDisplay.Draw(Time);

	Direct3D::DrawSprite(TimeSprite, TimeTex);
	Direct3D::DrawSprite(ScoreSprite, ScoreTex);

	for (int i = 0; i < 3; i++)
	{
		Direct3D::DrawSprite(NumPlusSprite[i], NumPlusTex[i]);
	}

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

		if (player.PlayerAliveFlag == true)
		{
			player.Update();
		}

		bullet.Update();

		blueEnemy.Update();
		redEnemy.Update();
		greenEnemy.Update();
		purpleEnemy.Update();

		//BGMを再生開始
		sound.MainSoundPlay();

		//弾の発射位置を設定
		bullet.BulletSet(player.PlayerPos, player.PlayerAngle);

		//残り時間の制御
		TimeCount();


		for (int i = 0; i < BulletMax; i++)
		{
			//自機や敵を囲っている当たり判定から抜けた場合に処理
			if (backGround.StageObbCollision(bullet.bulletObb[i]) == false)
			{
				//当たり判定から抜けた弾のフラグをfalseにする
				bullet.BulletShotFlag[i] = false;
			}

			//敵と弾の当たり判定の処理を行う
			//弾が発射されているフラグがtrueの場合のみ
			//当たり判定を行って、弾を消滅させる
			if (bullet.BulletShotFlag[i] == true)
			{

				//青色の敵と弾の衝突した際に行う処理
				if (blueEnemy.BlueEnemyCollision(bullet.bulletObb[i]))
				{
					//弾の描画フラグをfalseにして
					//画面上から弾を消しておく
					bullet.BulletShotFlag[i] = false;
					//敵を倒したのでスコアを加算
					Score += ScoreAddNum;

					//青色の敵に当たったので時間を回復させる
					//時間管理用のフレームの数値を0に変更
					TimeFrame = 0;
					//三秒だけ時間を加算して、時間を回復
					Time += TimeAddNum;

					//スコアに加算される得点のテクスチャのα値を1にして表示
					NumPlusSprite[0].SetAlpha(1);
					//残り時間に加算される数値のテクスチャのα値を1にして表示
					NumPlusSprite[2].SetAlpha(1);
				}

				//赤色の敵と弾の衝突した際に行う処理
				if (redEnemy.RedEnemyCollision(bullet.bulletObb[i]))
				{
					//処理としては上記と変わらないので
					//コメントはそちらを参考に
					bullet.BulletShotFlag[i] = false;
					//赤色の敵を倒した際の得点は他の敵より多い
					Score += RedEnemy_ScoreAddNum;

					NumPlusSprite[1].SetAlpha(1);
				}

				//緑色の敵と弾の衝突した際に行う処理
				if (greenEnemy.GreenEnemyCollision(bullet.bulletObb[i]))
				{
					//処理としては上記と変わらないので
					//コメントはそちらを参考に
					bullet.BulletShotFlag[i] = false;
					Score += ScoreAddNum;

					NumPlusSprite[0].SetAlpha(1);
				}

				//紫色の敵と弾の衝突した際に行う処理
				if (purpleEnemy.PurpleEnemyCollision(bullet.bulletObb[i], &bullet.BulletShotFlag[i]))
				{
					//紫色の敵はHPがあるのでHPが0になった場合に処理が行われる
					//それ以外は他の敵と変わらない
					Score += ScoreAddNum;
					NumPlusSprite[0].SetAlpha(1);
				}
			}
		}

		for (int i = 0; i < 3; i++)
		{
			//得点や時間の追加を示すテクスチャのα値が0以上だったら処理
			if (NumPlusSprite[i].GetAlpha() > 0)
			{
				//α値を減らして透明にする
				NumPlusSprite[i].SetAlpha(NumPlusSprite[i].GetAlpha() + (0.01f*-1));
			}
		}

		if (PlayerCollisionFlag == false)
		{
			//敵の弾との衝突判定を処理
			if (greenEnemy.EnemyBulletCollision(player.GetPlayerObb()) == true)
			{
				//衝突したかのフラグをtrueにする
				PlayerCollisionFlag = true;
				//自機の残り体力を減らす
				player.PlayerHp--;
				//プレイヤーが弾に衝突したので効果音を鳴らす
				se.PlayerHitSEPlay();
			}
		}

		player.EffecMove();


		for (int i = 0; i < DestroyEffectNum; i++)
		{
			//自機の残り体力が0になって生存フラグがfalseになったら処理
			if (player.PlayerHp == 0 && player.PlayerAliveFlag == true)
			{
				player.PlayerAliveFlag = false;
				player.EffectSet();
				se.PlayerDestroySEPlay();
			}

			if (player.PlayerAliveFlag == false && player.destroyEffect[i].count >= 60)
			{
				//リザルト画面へと遷移開始
				mSceneChanger->ChangeScene(STATE_RESULT);
			}
		}


		//敵の弾に衝突している場合に処理
		if (PlayerCollisionFlag == true)
		{
			//自機が敵の弾と衝突してからのカウント
			//自機の表示非表示を切り替えるためにも使用する
			PlayerCollisionCount++;

			//フラグのtrueとfalseを切り替えるための処理
			if (PlayerDrawFlag == false)
			{
				//カウントが5の倍数になったらフラグを切り替える
				//フラグがtrueになっていれば時期は表示される
				if (PlayerCollisionCount % Player_Draw_Speed == Player_Draw_Timing)
				{
					PlayerDrawFlag = true;
				}
			}
			else
			{
				//上記と同じようにカウントが5の倍数になれば
				//フラグをfalseにして自機の表示を消す
				if (PlayerCollisionCount % Player_Draw_Speed == Player_Draw_Timing)
				{
					PlayerDrawFlag = false;
				}
			}

			//カウントの数値が120（2秒）を超えた場合に処理
			if (PlayerCollisionCount >= PlayerRigorTime)
			{
				//フラグをfalse戻しておく
				PlayerCollisionFlag = false;
				PlayerDrawFlag = true;
				PlayerCollisionCount = 0;
			}
		}

		//弾の発射　操作はスペースキーで行う
		if (pDi->KeyJustPressed(DIK_SPACE))
		{
			//弾を発射していなければ発射される
			if (bullet.BulletShotFlag[BulletNum] == false && player.PlayerAliveFlag == true)
			{
				//弾の発射フラグをtrueにして
				//弾が描画されるようにする
				bullet.BulletShotFlag[BulletNum] = true;
				BulletNum++;
				//弾の発射音を再生
				se.ShotSEPlay();
			}
		}

		if (BulletNum >= BulletMax)
		{
			BulletNum = 0;
		}


		//どれかの敵が移動可能範囲外に行ったかの
		//フラグが返されたら処理
		if (EnemyMoveMax() == true)
		{
			//敵の位置や、生存フラグをリセットして仕切り直し
			blueEnemy.BlueEnemyReset();
			redEnemy.RedEnemyReset();
			greenEnemy.GreenEnemyReset();
			purpleEnemy.PurpleEnemyReset();
		}


		//敵が全滅した場合の処理
		if (blueEnemy.GetBlueEnemyOllDown() && redEnemy.GetRedEnemyOllDown() && greenEnemy.GetGreenEnemyOllDown())
		{
			//敵の位置や、生存フラグをリセットして仕切り直し
			blueEnemy.BlueEnemyReset();
			redEnemy.RedEnemyReset();
			greenEnemy.GreenEnemyReset();
			purpleEnemy.PurpleEnemyReset();
		}


		//スタートのテクスチャを画面外に移動
		if (StartTexPosX != Screen_Out)
		{
			StartTexPosX -= StartTex_Move;
		}


		break;
	}

}

void GameState::TimeCount()
{
	//--残り時間を管理する処理-----------------------------
	//残り時間を管理するフレームを加算
	TimeFrame++;
	//フレームが60を超えたなら一秒経過となるので
	//残り時間から1引いて、フレームをリセットする
	if (TimeFrame >= OneSecond)
	{
		Time--;
		TimeFrame = 0;
	}

	//制限時間が0になった場合にリザルト画面へ遷移
	if (Time == 0)
	{
		//メインゲームのBGMの再生を終了
		sound.MainSoundStop();
		//リザルト画面へと遷移開始
		mSceneChanger->ChangeScene(STATE_RESULT);
	}


}

//敵が移動可能範囲から抜けたかの判定を行う関数
bool GameState::EnemyMoveMax()
{
	for (int i = 0; i < BlueEnemyNum; i++)
	{
		//青色の敵が当たり判定から抜けた時の処理
		if (backGround.StageObbCollision(blueEnemy.enemyObb[i]) == false)
		{
			return true;
		}
	}

	for (int i = 0; i < GreenEnemyNum; i++)
	{
		//緑色の敵が当たり判定から抜けた時の処理
		if (backGround.StageObbCollision(greenEnemy.enemyObb[i]) == false)
		{
			return true;
		}
	}

	for (int i = 0; i < PurpleEnemyNum; i++)
	{
		//赤色の敵が当たり判定から抜けた時の処理
		if (backGround.StageObbCollision(purpleEnemy.enemyObb[i]) == false)
		{
			return true;
		}
	}

	return false;
}
