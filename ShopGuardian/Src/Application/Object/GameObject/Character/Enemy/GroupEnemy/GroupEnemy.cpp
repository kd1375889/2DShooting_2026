#include "GroupEnemy.h"

void GroupEnemy::Init()
{
	//テクスチャ
	m_spTex = std::make_shared<KdTexture>();
	m_spTex->Load("Asset/Textures/GameScene/Character/Enemy/Group.png");
	SetSplit(24, 1);

	//ステータス
	m_type = EnemyType::Group;
	m_moveSpd = 2.5f;
	m_hp = 3;

	BaseEnemy::Init();
}

void GroupEnemy::Update()
{
	BaseEnemy::Update();
}

void GroupEnemy::Release()
{
}