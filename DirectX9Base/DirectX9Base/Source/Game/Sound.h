#pragma once

#include "../Direct3D/Direct3D.h"
#include "../DirectSound/Wave.h"
#include "../DirectSound/DirectSound.h"
#include "../DirectSound/SoundBuffer.h"

class Sound
{
private:

	//�^�C�g���̉��y
	WaveFile TitleMusic;
	SoundBuffer sb_TitleMusic;

	//���C���Q�[���̉��y
	WaveFile MainMusic;
	SoundBuffer sb_MainMusic;

	//�N���A��ʂ̉��y
	WaveFile ResultMusic;
	SoundBuffer sb_ResultMusic;

public:

	Sound();
	~Sound();

	void Initialize();
	void Update();

	//�^�C�g����ʂ̉��y�𗬂��֐�
	void TitleSoundPlay();
	//�^�C�g���̉��y���~�߂�֐�
	void TitleSoundStop();

	//���C���Q�[���̉��y�𗬂��֐�
	void MainSoundPlay();
	//���C���Q�[���̉��y���~�߂�֐�
	void MainSoundStop();

	//���U���g��ʂ̉��y�𗬂��֐�
	void ResultSoundPlay();
	//���U���g��ʂ̉��y���~�߂�֐�
	void ResultSoundStop();


};