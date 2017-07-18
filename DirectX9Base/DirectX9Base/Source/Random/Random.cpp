#include "Random.h"

Random::Random()
{

}

Random::~Random()
{

}

//int型の数値を返す関数
int Random::GetRandom_Int(int min, int max)
{
	//ランダム関数を初期化するためのフラグ
	//何度も初期化を実行すると重くなってしまうので
	//一度だけ実行するようにする
	static bool InitializeFlag;

	if (InitializeFlag == false)
	{
		//ランダム関数を初期化
		srand((unsigned int)time(NULL));
		//フラグをtrueにしておいて初期化を二度行わないように
		InitializeFlag = true;
	}

	return min + (int)(rand()*(max - min + 1.0) / (1.0 + RAND_MAX));
}

//float型の数値を返す関数
float Random::GetRandom_Float(float min, float max)
{
	//ランダム関数を初期化するためのフラグ
	//上記と同じなのでコメントはそちらを参照
	static bool InitializeFlag;

	if (InitializeFlag == false)
	{
		srand((unsigned int)time(NULL));
		InitializeFlag = true;
	}

	return min + (int)(rand()*(max - min + 1.0) / (1.0 + RAND_MAX));
}