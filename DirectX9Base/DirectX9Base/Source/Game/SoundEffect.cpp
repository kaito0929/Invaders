#include "SoundEffect.h"

SoundEffect::SoundEffect()
{

}

SoundEffect::~SoundEffect()
{
	
}

void SoundEffect::Initialize()
{

	//Œˆ’è‚µ‚½‚ÌŒø‰Ê‰¹
	DecisionSE.Load("Sound/decision.wav");


	//”­Ë‰¹
	ShotSE.Load("Sound/shot.wav");

	//’…’e‰¹
	ShotHitSE.Load("Sound/shotHit.wav");

	//©‹@‚ÌÕ“Ë‰¹
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

//Œˆ’è‰¹‚ğ–Â‚ç‚·ŠÖ”
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

//”­Ë‰¹‚ğ–Â‚ç‚·ŠÖ”
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

//’…’e‰¹‚ğ–Â‚ç‚·ŠÖ”
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