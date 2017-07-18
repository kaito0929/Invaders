#include "SoundEffect.h"

SoundEffect::SoundEffect()
{

}

SoundEffect::~SoundEffect()
{
	
}

void SoundEffect::Initialize()
{

	//���肵�����̌��ʉ�
	DecisionSE.Load("Sound/decision.wav");


	//���ˉ�
	ShotSE.Load("Sound/shot.wav");

	//���e��
	ShotHitSE.Load("Sound/shotHit.wav");

	//���@�̏Փˉ�
	PlayerHitSE.Load("Sound/playerHit.wav");
	sb_PlayerHitSE.Create(PlayerHitSE);

	StartSE.Load("Sound/start.wav");
	sb_StartSE.Create(StartSE);

	for (int i = 0; i < 10; i++)
	{
		sb_DicisionSE[i].Create(DecisionSE);
		sb_ShotSE[i].Create(ShotSE);
		sb_ShotHitSE[i].Create(ShotHitSE);
	}

}

void SoundEffect::Update()
{

}

//���艹��炷�֐�
void SoundEffect::DecisionSEPlay()
{
	for (int i = 0; i < 10; i++)
	{
		if (sb_DicisionSE[i].Playing() == false)
		{
			sb_DicisionSE[i].Play(false);
			break;
		}
	}
}

//���ˉ���炷�֐�
void SoundEffect::ShotSEPlay()
{
	for (int i = 0; i < 10; i++)
	{
		if (sb_ShotSE[i].Playing() == false)
		{
			sb_ShotSE[i].Play(false);
			break;
		}
	}
}

//���e����炷�֐�
void SoundEffect::ShotHitSEPlay()
{
	for (int i = 0; i < 10; i++)
	{
		if (sb_ShotHitSE[i].Playing() == false)
		{
			sb_ShotHitSE[i].Play(false);
			break;
		}
	}
}

void SoundEffect::PlayerHitSEPlay()
{
	sb_PlayerHitSE.Play(false);
}

void SoundEffect::StartSEPlay()
{
	sb_StartSE.Play(false);
}