#include "GameState.h"

//�Q�[���̃X�R�A
//�G��|���x��20�_���Z�����
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

//�`��
void GameState::Draw()
{
	//RenderState��RENDER_POINTSPRITE�ɐݒ�
	//�w�i�ƓG��`�悷��܂Ōp��
	Direct3D::SetRenderState(RENDER_POINTSPRITE);
	backGround.Draw();
	//enemy.Draw();
	//enemy.DestroyEffectDraw();
	blueEnemy.Draw();
	redEnemy.Draw();
	greenEnemy.Draw();

	//�|�C���g�X�v���C�g��`�悵�I������̂�
	//RenderState��RENDER_ALPHABLEND�ɕύX
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

		player.Update();
		//enemy.Update();
		bullet.Update();

		blueEnemy.Update();
		redEnemy.Update();
		greenEnemy.Update();

		//BGM���Đ��J�n
		sound.MainSoundPlay();

		//�e�̔��ˈʒu��ݒ�
		bullet.BulletSet(player.PlayerPos, player.PlayerAngle);

		//�e�̔��ˁ@����̓X�y�[�X�L�[�ōs��
		if (pDi->KeyJustPressed(DIK_SPACE))
		{
			//�e�𔭎˂��Ă��Ȃ���Δ��˂����
			if (bullet.BulletShotFlag == false)
			{
				//�e�̔��˃t���O��true�ɂ���
				//�e���`�悳���悤�ɂ���
				bullet.BulletShotFlag = true;
				//�e�̔��ˉ����Đ�
				se.ShotSEPlay();
			}
		}

		//�G�ƒe�̓����蔻��̏������s��
		//�e�����˂���Ă���t���O��true�̏ꍇ�̂�
		//�����蔻����s���āA�e�����ł�����
		if (bullet.BulletShotFlag == true)
		{
			//���˂��Ă��玩���Œe���������߂̏���
			//�e���˂���J�E���g�����Z����
			BulletCount++;
			//�J�E���g��60�𒴂�����t���O��
			//false�ɂ��Ēe�������Ă���
			//�J�E���g��0�ɂ��Ă���
			if (BulletCount >= 60)
			{
				bullet.BulletShotFlag = false;
				BulletCount = 0;
			}

			//�F�̓G�ƒe�̏Փ˂����ۂɍs������
			if (blueEnemy.BlueEnemyCollision(bullet.bulletObb))
			{
				//�e�̕`��t���O��false�ɂ���
				//��ʏォ��e�������Ă���
				bullet.BulletShotFlag = false;
				//�G��|�����̂ŃX�R�A�����Z
				Score += ScorePulsNum;

				//�F�̓G�ɓ��������̂Ŏ��Ԃ��񕜂�����
				//���ԊǗ��p�̃t���[���̐��l��0�ɕύX
				TimeFrame = 0;
				//��b�������Ԃ����Z���āA���Ԃ���
				Time++;

				//�e���������̂ŃJ�E���g��0�ɂ��Ă���
				BulletCount = 0;
			}

			//�ԐF�̓G�ƒe�̏Փ˂����ۂɍs������
			if (redEnemy.RedEnemyCollision(bullet.bulletObb))
			{
				//�����Ƃ��Ă͏�L�ƕς��Ȃ��̂�
				//�R�����g�͂�������Q�l��
				bullet.BulletShotFlag = false;
				//�ԐF�̓G�͑��̓G��葁�������̂�
				//���Z����X�R�A�͑��߂ɂ���
				Score += RedEnemy_ScorePulsNum;

				BulletCount = 0;
			}

			//�F�̓G�ƒe�̏Փ˂����ۂɍs������
			if (greenEnemy.GreenEnemyCollision(bullet.bulletObb))
			{
				//�����Ƃ��Ă͏�L�ƕς��Ȃ��̂�
				//�R�����g�͂�������Q�l��
				bullet.BulletShotFlag = false;
				Score += ScorePulsNum;

				BulletCount = 0;
			}
		}

		//�G���w�肵���ʒu�܂Ői�s���Ă����ꍇ�ɏ���
		//���U���g��ʂւ̑J�ڂ��J�n������
		if (enemy.EnemyBorderlineReaching() == true)
		{
			//���C���Q�[����BGM�̍Đ����I��
			sound.MainSoundStop();
			//���U���g��ʂւƑJ�ڊJ�n
			mSceneChanger->ChangeScene(STATE_RESULT);
		}

		//�X�^�[�g�̃e�N�X�`������ʊO�Ɉړ�
		if (StartTexPosX != Screen_Out)
		{
			StartTexPosX -= StartTex_Move;
		}



		//--�c�莞�Ԃ��Ǘ����鏈��-----------------------------
		//�c�莞�Ԃ��Ǘ�����t���[�������Z
		TimeFrame++;
		//�t���[����60�𒴂����Ȃ��b�o�߂ƂȂ�̂�
		//�c�莞�Ԃ���1�����āA�t���[�������Z�b�g����
		if (TimeFrame >= 60)
		{
			Time--;
			TimeFrame = 0;
		}

		break;
	}
	
}
