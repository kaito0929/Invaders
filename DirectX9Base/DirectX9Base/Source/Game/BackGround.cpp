#include "BackGround.h"

//コンストラクタ
BackGround::BackGround()
{

}

//デストラクタ
BackGround::~BackGround()
{
	delete tex;
	delete[] vertex;
}

//初期化
void BackGround::Initialize()
{
	for (int i = 0; i < NumStars; i++)
	{
		//描画する座標をランダムで取得
		pos[i] = D3DXVECTOR3(random.GetRandom_Int(-250, 250), 
							 random.GetRandom_Int(-400, 100), 
							 random.GetRandom_Int(100, 1100));
	}

	tex = new Texture;
	tex->Load("Texture/effect0.png");

	vertex = new VERTEX[NumStars];
}

//描画
void BackGround::Draw()
{
	for (int i = 0; i < NumStars; i++)
	{
		//座標を代入
		vertex[i].pos = pos[i];
		//大きさを決定
		vertex[i].size = 5.0f;
		//色を決定
		vertex[i].color = (DWORD)D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	}

	//ポイントスプライトの描画
	Direct3D::GetInstance()->DrawPointSprite(vertex, NumStars, *tex);

}

