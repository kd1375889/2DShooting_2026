#include "NormalEnemy.h"

void NormalEnemy::Init()
{
	//テクスチャ
	m_spTex = std::make_shared<KdTexture>();
	m_spTex->Load("Asset/Textures/Game/Enemy.png");
	SetSplit(24, 1);

	BaseEnemy::Init();
}

void NormalEnemy::Update()
{
	BaseEnemy::Update();
}

void NormalEnemy::Hit()
{
	if (!m_alive) return;

	m_move.y = m_moveSpd;
	m_lockFlg = false;
	m_alive = false;
}

void NormalEnemy::Release()
{
}
