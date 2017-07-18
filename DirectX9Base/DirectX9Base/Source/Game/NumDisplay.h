#pragma once

#include "../Direct3D/Direct3D.h"
#include "../Direct3D/Sprite.h"
#include "../Direct3D/Texture.h"

class NumDisplay
{
private:

	int NumPositionX;
	int NumPositionY;

	int SpriteSize;

	float alpha;

	Sprite sprite;
	Texture texture;

public:
	NumDisplay();
	~NumDisplay();

	void LoadTexture(TCHAR*FileName);

	void SetPosition(int x, int y);
	void SetSize(int size);

	void Draw(int num);
};