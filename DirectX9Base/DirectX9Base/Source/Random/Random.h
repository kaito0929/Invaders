#pragma once

#include "../Direct3D/mesh.h"
#include "../Direct3D/Direct3D.h"
#include "../Direct3D/Texture.h"
#include "../Direct3D/Sprite.h"
#include "../Direct3D/camera.h"
#include "../BoundingBox/BoundingBox.h"
#include "../Input/directInput.h"

class Random
{
private:

public:
	Random();
	~Random();

	//ランダムで数値を返す関数
	//最小値と最大値を決めるとその間の数値を渡すようになっている
	int GetRandom_Int(int min, int max);
	float GetRandom_Float(float min, float max);

};