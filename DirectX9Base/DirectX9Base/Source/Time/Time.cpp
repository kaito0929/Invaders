#include "Time.h"

Time::Time()
{

}

Time::~Time()
{

}

void Time::Initialize()
{
	TimeTex.Load("Texture/number.png");
	TimeTex.SetDivide(10, 1);

	TenTimeSprite.SetPos(1150, 50);
	TenTimeSprite.SetSize(200, 100);

	OneTimeSprite.SetPos(1200, 50);
	OneTimeSprite.SetSize(200, 100);

	TenSec = 0;
	OneSec = 0;
}

void Time::Draw(const int& Sec)
{
	if (Sec > 9)
	{
		TenSec = (Sec % 100) / 10;
	}
	else
	{
		TenSec = Sec % 10;
	}

	OneSec = Sec % 10;

	Direct3D::DrawSprite(TenTimeSprite, TimeTex);

}