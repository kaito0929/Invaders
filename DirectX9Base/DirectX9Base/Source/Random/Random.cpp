#include "Random.h"

Random::Random()
{

}

Random::~Random()
{

}

//int�^�̐��l��Ԃ��֐�
int Random::GetRandom_Int(int min, int max)
{
	//�����_���֐������������邽�߂̃t���O
	//���x�������������s����Əd���Ȃ��Ă��܂��̂�
	//��x�������s����悤�ɂ���
	static bool InitializeFlag;

	if (InitializeFlag == false)
	{
		//�����_���֐���������
		srand((unsigned int)time(NULL));
		//�t���O��true�ɂ��Ă����ď��������x�s��Ȃ��悤��
		InitializeFlag = true;
	}

	return min + (int)(rand()*(max - min + 1.0) / (1.0 + RAND_MAX));
}

//float�^�̐��l��Ԃ��֐�
float Random::GetRandom_Float(float min, float max)
{
	//�����_���֐������������邽�߂̃t���O
	//��L�Ɠ����Ȃ̂ŃR�����g�͂�������Q��
	static bool InitializeFlag;

	if (InitializeFlag == false)
	{
		srand((unsigned int)time(NULL));
		InitializeFlag = true;
	}

	return min + (int)(rand()*(max - min + 1.0) / (1.0 + RAND_MAX));
}