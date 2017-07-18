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
	//RenderState��RENDER_POINTSPRITE�ɐݒ�
	//�w�i�ƓG��`�悷��܂Ōp��
	Direct3D::SetRenderState(RENDER_POINTSPRITE);
	backGround.Draw();
	enemy.Draw();

	//�|�C���g�X�v���C�g��`�悵�I������̂�
	//RenderState��RENDER_ALPHABLEND�ɕύX
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
	case FADE:	//�t�F�[�h�C�����J�n

		//�t�F�[�h�C�����I�������珈��
		if (fade.FadeIn() == true)
		{
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
			mainState = MAIN;
		}


		break;
	case MAIN:		//���C���Q�[��

		player.Update();
		enemy.Update();
		bullet.Update();
		sound.MainSoundPlay();

		//�e�̔��ˈʒu��ݒ�
		bullet.BulletPosSet(player.PlayerPos);

		//�e�̔��ˁ@����̓X�y�[�X�L�[�ōs��
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
			//�e�ƓG�̓����蔻�������
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

		//�X�^�[�g�̃e�N�X�`������ʊO�Ɉړ�
		if (StartTexPosX != Screen_Out)
		{
			StartTexPosX -= StartTex_Move;
		}

		break;
	}
	
}
