#include "SoundEffect.h"

SoundEffect::SoundEffect()
{

}

SoundEffect::~SoundEffect()
{
	
}

void SoundEffect::Initialize()
{

	//決定した時の効果音
	DecisionSE.Load("Sound/decision.wav");

	//発射音
	ShotSE.Load("Sound/shot.wav");

	//着弾音
	ShotHitSE.Load("Sound/shotHit.wav");

	//自機消滅音
	PlayerDestroySE.Load("Sound/bomb.wav");
	sb_PlayerDestroySE.Create(PlayerDestroySE);

	//自機の衝突音
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

//決定音を鳴らす関数
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

//発射音を鳴らす関数
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

//着弾音を鳴らす関数
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

void SoundEffect::PlayerDestroySEPlay()
{
	sb_PlayerDestroySE.Play(false);
}

void SoundEffect::PlayerHitSEPlay()
{
	sb_PlayerHitSE.Play(false);
}

void SoundEffect::StartSEPlay()
{
	sb_StartSE.Play(false);
}