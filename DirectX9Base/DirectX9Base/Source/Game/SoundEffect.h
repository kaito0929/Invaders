#pragma once

#include "../Direct3D/Direct3D.h"
#include "../DirectSound/Wave.h"
#include "../DirectSound/DirectSound.h"
#include "../DirectSound/SoundBuffer.h"

class SoundEffect
{
private:

	//決定した時の効果音
	WaveFile DecisionSE;
	SoundBuffer sb_DicisionSE[10];

	//攻撃した時の効果音
	WaveFile ShotSE;
	SoundBuffer sb_ShotSE[10];

	//発射した弾が何かに当たった音
	WaveFile ShotHitSE;
	SoundBuffer sb_ShotHitSE[10];

	//自機の体力がなくなった時の音
	WaveFile PlayerDestroySE;
	SoundBuffer sb_PlayerDestroySE;

	//自機が何かに当たった時の音
	WaveFile PlayerHitSE;
	SoundBuffer sb_PlayerHitSE;

	//ゲームスタートの合図
	WaveFile StartSE;
	SoundBuffer sb_StartSE;

public:
	SoundEffect();
	~SoundEffect();

	void Initialize();
	void Update();

	//決定音を鳴らす関数
	void DecisionSEPlay();
	//攻撃音を鳴らす関数
	void ShotSEPlay();
	//着弾した時の効果音を鳴らす関数
	void ShotHitSEPlay();
	//自機の体力がなくなった時の音を鳴らす関数
	void PlayerDestroySEPlay();
	//自機が何かと衝突した時に効果音を鳴らす関数
	void PlayerHitSEPlay();
	//ゲームスタートの合図の音を鳴らす関数
	void StartSEPlay();
};