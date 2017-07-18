#include "NumDisplay.h"

NumDisplay::NumDisplay()
{
	texture.SetDivide(10, 1);
	alpha = 1.0f;
}

NumDisplay::~NumDisplay()
{

}

void NumDisplay::LoadTexture(TCHAR*FileName)
{
	texture.Load(FileName);
}

void NumDisplay::SetPosition(int x, int y)
{
	NumPositionX = x;
	NumPositionY = y;
}

void NumDisplay::SetSize(int size)
{
	SpriteSize = size;
	sprite.SetSize(size, size);
}

void NumDisplay::Draw(int num)
{
	int beamWidth = 0;
	int i = 1;

	if (num == 0)
	{
		beamWidth = 1;
	}
	else
	{
		if (num > 0)
		{
			while (num >= i)
			{
				beamWidth += 1;
				i *= 10;
			}
		}
	}

	if (num >= 0)
	{
		for (int i = 0; i < beamWidth; i++)
		{
			int n = 1;
			for (int j = 0; j < i; j++)
			{
				n *= 10;
			}
			int m = num / n;
			m = m % 10;

			texture.SetUVNum(m, 0);
			sprite.SetPos(NumPositionX - (SpriteSize / 2) - (SpriteSize*i), NumPositionY);
			Direct3D::DrawSprite(sprite, texture);
		}
	}
}
