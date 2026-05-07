#include "GroupEnemy.h"

void GroupEnemy::Init()
{
	//テクスチャ
	m_spTex = std::make_shared<KdTexture>();
	m_spTex->Load("Asset/Textures/Game/Group.png");
	SetSplit(24, 1);

	//HP
	m_hp = 3;

	BaseEnemy::Init();
}

void GroupEnemy::Update()
{
	BaseEnemy::Update();
}

void GroupEnemy::Hit()
{
	if (!m_alive) return;

	m_hp--;
	if (m_hp <= 0)
	{
		m_move.y = m_moveSpd;
		m_alive = false;
	}
	m_lockFlg = false;

}

void GroupEnemy::Release()
{
}