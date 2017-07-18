#pragma once

#include "../Direct3D/mesh.h"
#include "../Direct3D/Direct3D.h"
#include "../Direct3D/Texture.h"
#include "../Direct3D/Sprite.h"
#include "../Direct3D/camera.h"
#include "../BoundingBox/BoundingBox.h"
#include "../Input/directInput.h"

#include "../Random/Random.h"

//�`�悷��|�C���g�X�v���C�g�̐�
#define NumStars 5000

//�w�i�p�̃G�t�F�N�g��`�悷��N���X
class BackGround
{
private:

	//�|�C���g�X�v���C�g�̍��W
	D3DXVECTOR3 pos[NumStars];
	//�|�C���g�X�v���C�g�̃e�N�X�`�����擾����ϐ�
	Texture *tex;
	//�|�C���g�X�v���C�g�`��p�̕ϐ�
	VERTEX *vertex;

	//�G�t�F�N�g�̍��W�����肷�邽�߂�
	//�����_���Ő��l���擾���邽�߂ɐ錾
	Random random;

public:

	BackGround();
	~BackGround();

	//������
	void Initialize();
	//�`��
	void Draw();

};