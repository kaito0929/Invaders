#pragma once
#include "../Direct3D/Texture.h"
#include "../Direct3D/Sprite.h"
#include "../Direct3D/Direct3D.h"

class Time
{
private:

	Texture TimeTex;
	Sprite TenTimeSprite;
	Sprite OneTimeSprite;

	int TenSec;
	int OneSec;

public:
	Time();
	~Time();

	//������
	void Initialize();
	//�`��
	void Draw(const int& Sec);
};