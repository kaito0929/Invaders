#include "GameState.h"

//�Q�[���̃X�R�A
//�G��|���x�ɉ��Z�����
int Score;

//�R���X�g���N�^
GameState::GameState(ISceneChanger* changer) : BaseScene(changer)
{
	
}

//�f�X�g���N�^
GameState::~GameState()
{
	
}

//������
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

//�`��
void GameState::Draw()
{
	//RenderState��RENDER_POINTSPRITE�ɐݒ�
	//�w�i�ƓG��`�悷��܂Ōp��
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

	//�|�C���g�X�v���C�g��`�悵�I������̂�
	//RenderState��RENDER_ALPHABLEND�ɕύX
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
	case FADE:		//�t�F�[�h�C�����J�n

		//�t�F�[�h�C�����I�������珈��
		if (fade.FadeIn() == true)
		{
			//���S�ɉ�ʂ����邭�Ȃ����̂�
			//�X�e�[�g��ς��āA�Q�[���J�n�̍��}����������
			mainState = SIGNAL;
		}

		break;
	case SIGNAL:	//�J�n�̍��}���o��

		//�X�^�[�g�̃e�N�X�`������ʒ����܂ňړ�
		if (StartTexPosX != Screen_CenterX)
		{
			StartTexPosX -= StartTex_Move;
		}
		else
		{
			//��ʒ����Ɉړ�������SE���Đ�
			se.StartSEPlay();
			//�v���C���[�̑��삪�\�ɂȂ�܂ł̃J�E���g�����Z
			StartCount++;
		}

		//�J�E���g��10�𒴂�����v���C���[�̑�����\��
		if (StartCount >= Start_Count_Max)
		{
			//�X�e�[�g��ς��ăQ�[�����J�n
			//�v���C���[�̑�����󂯕t����悤��
			mainState = MAIN;
		}

		break;
	case MAIN:		//���C���Q�[��

		if (player.PlayerAliveFlag == true)
		{
			player.Update();
		}

		bullet.Update();

		blueEnemy.Update();
		redEnemy.Update();
		greenEnemy.Update();
		purpleEnemy.Update();

		//BGM���Đ��J�n
		sound.MainSoundPlay();

		//�e�̔��ˈʒu��ݒ�
		bullet.BulletSet(player.PlayerPos, player.PlayerAngle);

		//�c�莞�Ԃ̐���
		TimeCount();


		for (int i = 0; i < BulletMax; i++)
		{
			//���@��G���͂��Ă��铖���蔻�肩�甲�����ꍇ�ɏ���
			if (backGround.StageObbCollision(bullet.bulletObb[i]) == false)
			{
				//�����蔻�肩�甲�����e�̃t���O��false�ɂ���
				bullet.BulletShotFlag[i] = false;
			}

			//�G�ƒe�̓����蔻��̏������s��
			//�e�����˂���Ă���t���O��true�̏ꍇ�̂�
			//�����蔻����s���āA�e�����ł�����
			if (bullet.BulletShotFlag[i] == true)
			{

				//�F�̓G�ƒe�̏Փ˂����ۂɍs������
				if (blueEnemy.BlueEnemyCollision(bullet.bulletObb[i]))
				{
					//�e�̕`��t���O��false�ɂ���
					//��ʏォ��e�������Ă���
					bullet.BulletShotFlag[i] = false;
					//�G��|�����̂ŃX�R�A�����Z
					Score += ScoreAddNum;

					//�F�̓G�ɓ��������̂Ŏ��Ԃ��񕜂�����
					//���ԊǗ��p�̃t���[���̐��l��0�ɕύX
					TimeFrame = 0;
					//�O�b�������Ԃ����Z���āA���Ԃ���
					Time += TimeAddNum;

					//�X�R�A�ɉ��Z����链�_�̃e�N�X�`���̃��l��1�ɂ��ĕ\��
					NumPlusSprite[0].SetAlpha(1);
					//�c�莞�Ԃɉ��Z����鐔�l�̃e�N�X�`���̃��l��1�ɂ��ĕ\��
					NumPlusSprite[2].SetAlpha(1);
				}

				//�ԐF�̓G�ƒe�̏Փ˂����ۂɍs������
				if (redEnemy.RedEnemyCollision(bullet.bulletObb[i]))
				{
					//�����Ƃ��Ă͏�L�ƕς��Ȃ��̂�
					//�R�����g�͂�������Q�l��
					bullet.BulletShotFlag[i] = false;
					//�ԐF�̓G��|�����ۂ̓��_�͑��̓G��葽��
					Score += RedEnemy_ScoreAddNum;

					NumPlusSprite[1].SetAlpha(1);
				}

				//�ΐF�̓G�ƒe�̏Փ˂����ۂɍs������
				if (greenEnemy.GreenEnemyCollision(bullet.bulletObb[i]))
				{
					//�����Ƃ��Ă͏�L�ƕς��Ȃ��̂�
					//�R�����g�͂�������Q�l��
					bullet.BulletShotFlag[i] = false;
					Score += ScoreAddNum;

					NumPlusSprite[0].SetAlpha(1);
				}

				//���F�̓G�ƒe�̏Փ˂����ۂɍs������
				if (purpleEnemy.PurpleEnemyCollision(bullet.bulletObb[i], &bullet.BulletShotFlag[i]))
				{
					//���F�̓G��HP������̂�HP��0�ɂȂ����ꍇ�ɏ������s����
					//����ȊO�͑��̓G�ƕς��Ȃ�
					Score += ScoreAddNum;
					NumPlusSprite[0].SetAlpha(1);
				}
			}
		}

		for (int i = 0; i < 3; i++)
		{
			//���_�⎞�Ԃ̒ǉ��������e�N�X�`���̃��l��0�ȏゾ�����珈��
			if (NumPlusSprite[i].GetAlpha() > 0)
			{
				//���l�����炵�ē����ɂ���
				NumPlusSprite[i].SetAlpha(NumPlusSprite[i].GetAlpha() + (0.01f*-1));
			}
		}

		if (PlayerCollisionFlag == false)
		{
			//�G�̒e�Ƃ̏Փ˔��������
			if (greenEnemy.EnemyBulletCollision(player.GetPlayerObb()) == true)
			{
				//�Փ˂������̃t���O��true�ɂ���
				PlayerCollisionFlag = true;
				//���@�̎c��̗͂����炷
				player.PlayerHp--;
				//�v���C���[���e�ɏՓ˂����̂Ō��ʉ���炷
				se.PlayerHitSEPlay();
			}
		}

		player.EffecMove();


		for (int i = 0; i < DestroyEffectNum; i++)
		{
			//���@�̎c��̗͂�0�ɂȂ��Đ����t���O��false�ɂȂ����珈��
			if (player.PlayerHp == 0 && player.PlayerAliveFlag == true)
			{
				player.PlayerAliveFlag = false;
				player.EffectSet();
				se.PlayerDestroySEPlay();
			}

			if (player.PlayerAliveFlag == false && player.destroyEffect[i].count >= 60)
			{
				//���U���g��ʂւƑJ�ڊJ�n
				mSceneChanger->ChangeScene(STATE_RESULT);
			}
		}


		//�G�̒e�ɏՓ˂��Ă���ꍇ�ɏ���
		if (PlayerCollisionFlag == true)
		{
			//���@���G�̒e�ƏՓ˂��Ă���̃J�E���g
			//���@�̕\����\����؂�ւ��邽�߂ɂ��g�p����
			PlayerCollisionCount++;

			//�t���O��true��false��؂�ւ��邽�߂̏���
			if (PlayerDrawFlag == false)
			{
				//�J�E���g��5�̔{���ɂȂ�����t���O��؂�ւ���
				//�t���O��true�ɂȂ��Ă���Ύ����͕\�������
				if (PlayerCollisionCount % Player_Draw_Speed == Player_Draw_Timing)
				{
					PlayerDrawFlag = true;
				}
			}
			else
			{
				//��L�Ɠ����悤�ɃJ�E���g��5�̔{���ɂȂ��
				//�t���O��false�ɂ��Ď��@�̕\��������
				if (PlayerCollisionCount % Player_Draw_Speed == Player_Draw_Timing)
				{
					PlayerDrawFlag = false;
				}
			}

			//�J�E���g�̐��l��120�i2�b�j�𒴂����ꍇ�ɏ���
			if (PlayerCollisionCount >= PlayerRigorTime)
			{
				//�t���O��false�߂��Ă���
				PlayerCollisionFlag = false;
				PlayerDrawFlag = true;
				PlayerCollisionCount = 0;
			}
		}

		//�e�̔��ˁ@����̓X�y�[�X�L�[�ōs��
		if (pDi->KeyJustPressed(DIK_SPACE))
		{
			//�e�𔭎˂��Ă��Ȃ���Δ��˂����
			if (bullet.BulletShotFlag[BulletNum] == false && player.PlayerAliveFlag == true)
			{
				//�e�̔��˃t���O��true�ɂ���
				//�e���`�悳���悤�ɂ���
				bullet.BulletShotFlag[BulletNum] = true;
				BulletNum++;
				//�e�̔��ˉ����Đ�
				se.ShotSEPlay();
			}
		}

		if (BulletNum >= BulletMax)
		{
			BulletNum = 0;
		}


		//�ǂꂩ�̓G���ړ��\�͈͊O�ɍs��������
		//�t���O���Ԃ��ꂽ�珈��
		if (EnemyMoveMax() == true)
		{
			//�G�̈ʒu��A�����t���O�����Z�b�g���Ďd�؂蒼��
			blueEnemy.BlueEnemyReset();
			redEnemy.RedEnemyReset();
			greenEnemy.GreenEnemyReset();
			purpleEnemy.PurpleEnemyReset();
		}


		//�G���S�ł����ꍇ�̏���
		if (blueEnemy.GetBlueEnemyOllDown() && redEnemy.GetRedEnemyOllDown() && greenEnemy.GetGreenEnemyOllDown())
		{
			//�G�̈ʒu��A�����t���O�����Z�b�g���Ďd�؂蒼��
			blueEnemy.BlueEnemyReset();
			redEnemy.RedEnemyReset();
			greenEnemy.GreenEnemyReset();
			purpleEnemy.PurpleEnemyReset();
		}


		//�X�^�[�g�̃e�N�X�`������ʊO�Ɉړ�
		if (StartTexPosX != Screen_Out)
		{
			StartTexPosX -= StartTex_Move;
		}


		break;
	}

}

void GameState::TimeCount()
{
	//--�c�莞�Ԃ��Ǘ����鏈��-----------------------------
	//�c�莞�Ԃ��Ǘ�����t���[�������Z
	TimeFrame++;
	//�t���[����60�𒴂����Ȃ��b�o�߂ƂȂ�̂�
	//�c�莞�Ԃ���1�����āA�t���[�������Z�b�g����
	if (TimeFrame >= OneSecond)
	{
		Time--;
		TimeFrame = 0;
	}

	//�������Ԃ�0�ɂȂ����ꍇ�Ƀ��U���g��ʂ֑J��
	if (Time == 0)
	{
		//���C���Q�[����BGM�̍Đ����I��
		sound.MainSoundStop();
		//���U���g��ʂւƑJ�ڊJ�n
		mSceneChanger->ChangeScene(STATE_RESULT);
	}


}

//�G���ړ��\�͈͂��甲�������̔�����s���֐�
bool GameState::EnemyMoveMax()
{
	for (int i = 0; i < BlueEnemyNum; i++)
	{
		//�F�̓G�������蔻�肩�甲�������̏���
		if (backGround.StageObbCollision(blueEnemy.enemyObb[i]) == false)
		{
			return true;
		}
	}

	for (int i = 0; i < GreenEnemyNum; i++)
	{
		//�ΐF�̓G�������蔻�肩�甲�������̏���
		if (backGround.StageObbCollision(greenEnemy.enemyObb[i]) == false)
		{
			return true;
		}
	}

	for (int i = 0; i < PurpleEnemyNum; i++)
	{
		//�ԐF�̓G�������蔻�肩�甲�������̏���
		if (backGround.StageObbCollision(purpleEnemy.enemyObb[i]) == false)
		{
			return true;
		}
	}

	return false;
}
