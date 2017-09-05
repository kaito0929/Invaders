#pragma once

#include "../Direct3D/mesh.h"
#include "../Direct3D/Direct3D.h"
#include "../Direct3D/Texture.h"
#include "../Direct3D/Sprite.h"
#include "../Direct3D/camera.h"
#include "../BoundingBox/BoundingBox.h"
#include "../Input/directInput.h"

//�e��z���W�̍ő�l
#define BulletPosZMax 200.0f
//�e�̈ړ����x
#define BulletMoveSpeed 3.0f 

//���˂ł���e�̍ő吔
#define BulletMax 10

class Bullet
{
private:

	//�e�̃��f��
	Mesh BulletModel;
	//���b�V���ɓn���s����쐬
	D3DXMATRIXA16 mat_transform, mat_scale, mat_rotate;
	//�e�̍��W
	D3DXVECTOR3 BulletPos[BulletMax];
	//�e�����˂����p�x
	D3DXVECTOR3 BulletShotAngle[BulletMax];

	//�e�����̃x�N�g��
	//�����蔻��Ɏg��
	D3DXVECTOR3 forward;
	D3DXVECTOR3 right;
	D3DXVECTOR3 up;

public:
	Bullet();
	~Bullet();

	//������
	void Initialize();
	//���ۂ̓���
	void Update();
	//�`��
	void Draw();

	//�e�̏ꏊ������
	void BulletSet(D3DXVECTOR3 pPos,D3DXVECTOR3 pAngle);
	//�e�𔭎˂��Ă��邩�̃t���O
	bool BulletShotFlag[BulletMax];

	//�e�̓����蔻��
	OrientedBoundingBox bulletObb[BulletMax];

};