#pragma once

#include "../Direct3D/Direct3D.h"
#include "../DirectSound/Wave.h"
#include "../DirectSound/DirectSound.h"
#include "../DirectSound/SoundBuffer.h"

class Sound
{
private:

	//タイトルの音楽
	WaveFile TitleMusic;
	SoundBuffer sb_TitleMusic;

	//メインゲームの音楽
	WaveFile MainMusic;
	SoundBuffer sb_MainMusic;

	//クリア画面の音楽
	WaveFile ClearMusic;
	SoundBuffer sb_ClearMusic;

public:

	Sound();
	~Sound();

	void Initialize();
	void Update();

	//タイトル画面の音楽を流す関数
	void TitleSoundPlay();
	//タイトルの音楽を止める関数
	void TitleSoundStop();

	//メインゲームの音楽を流す関数
	void MainSoundPlay();
	//メインゲームの音楽を止める関数
	void MainSoundStop();

	//クリア画面の音楽を流す関数
	void ClearSoundPlay();
	//クリア画面の音楽を止める関数
	void ClearSoundStop();


};