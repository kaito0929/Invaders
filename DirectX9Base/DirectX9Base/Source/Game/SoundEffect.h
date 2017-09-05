#pragma once

#include "../Direct3D/Direct3D.h"
#include "../DirectSound/Wave.h"
#include "../DirectSound/DirectSound.h"
#include "../DirectSound/SoundBuffer.h"

class SoundEffect
{
private:

	//���肵�����̌��ʉ�
	WaveFile DecisionSE;
	SoundBuffer sb_DicisionSE[10];

	//�U���������̌��ʉ�
	WaveFile ShotSE;
	SoundBuffer sb_ShotSE[10];

	//���˂����e�������ɓ���������
	WaveFile ShotHitSE;
	SoundBuffer sb_ShotHitSE[10];

	//���@�̗̑͂��Ȃ��Ȃ������̉�
	WaveFile PlayerDestroySE;
	SoundBuffer sb_PlayerDestroySE;

	//���@�������ɓ����������̉�
	WaveFile PlayerHitSE;
	SoundBuffer sb_PlayerHitSE;

	//�Q�[���X�^�[�g�̍��}
	WaveFile StartSE;
	SoundBuffer sb_StartSE;

public:
	SoundEffect();
	~SoundEffect();

	void Initialize();
	void Update();

	//���艹��炷�֐�
	void DecisionSEPlay();
	//�U������炷�֐�
	void ShotSEPlay();
	//���e�������̌��ʉ���炷�֐�
	void ShotHitSEPlay();
	//���@�̗̑͂��Ȃ��Ȃ������̉���炷�֐�
	void PlayerDestroySEPlay();
	//���@�������ƏՓ˂������Ɍ��ʉ���炷�֐�
	void PlayerHitSEPlay();
	//�Q�[���X�^�[�g�̍��}�̉���炷�֐�
	void StartSEPlay();
};