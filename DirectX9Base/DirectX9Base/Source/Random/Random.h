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

	//�����_���Ő��l��Ԃ��֐�
	//�ŏ��l�ƍő�l�����߂�Ƃ��̊Ԃ̐��l��n���悤�ɂȂ��Ă���
	int GetRandom_Int(int min, int max);
	float GetRandom_Float(float min, float max);

};