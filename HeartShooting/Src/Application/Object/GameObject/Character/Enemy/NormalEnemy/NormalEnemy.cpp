#include "NormalEnemy.h"

void NormalEnemy::Init()
{
	//テクスチャ
	m_spTex = std::make_shared<KdTexture>();
	m_spTex->Load("Asset/Textures/GameScene/Character/Enemy/Normal.png");
	SetSplit(24, 1);

	BaseEnemy::Init();
}

void NormalEnemy::Update()
{
	BaseEnemy::Update();
}

void NormalEnemy::Release()
{
}
