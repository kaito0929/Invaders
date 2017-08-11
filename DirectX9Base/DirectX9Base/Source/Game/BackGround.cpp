#include "BackGround.h"

//�R���X�g���N�^
BackGround::BackGround()
{

}

//�f�X�g���N�^
BackGround::~BackGround()
{
	delete tex;
	delete[] vertex;
}

//������
void BackGround::Initialize()
{
	for (int i = 0; i < NumStars; i++)
	{
		//�`�悷����W�������_���Ŏ擾
		pos[i] = D3DXVECTOR3(random.GetRandom_Int(-250, 250), 
							 random.GetRandom_Int(-400, 100), 
							 random.GetRandom_Int(100, 1100));
	}

	tex = new Texture;
	tex->Load("Texture/effect0.png");

	vertex = new VERTEX[NumStars];
}

//�`��
void BackGround::Draw()
{
	for (int i = 0; i < NumStars; i++)
	{
		//���W����
		vertex[i].pos = pos[i];
		//�傫��������
		vertex[i].size = 5.0f;
		//�F������
		vertex[i].color = (DWORD)D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	}

	//�|�C���g�X�v���C�g�̕`��
	Direct3D::GetInstance()->DrawPointSprite(vertex, NumStars, *tex);

}

