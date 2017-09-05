#pragma once

#include "../Direct3D/Direct3D.h"
#include "../Direct3D/Texture.h"
#include "../Direct3D/Sprite.h"


//���@���G���|���ꂽ���̃G�t�F�N�g
struct DestroyEffect
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 angle;		//����
	float speed;			//����
	int count;				//�`�悷�鎞��
	bool used;				//�g�p����
};


class Effect
{
private:


	VERTEX *vertex;

public:
	Effect();
	~Effect();

	//������
	void Initialize();
	//���ۂ̓���
	void Update();
	//�`��
	void Draw();

	void EffectSet(D3DXVECTOR3 pos);
	void EffectMove();
};