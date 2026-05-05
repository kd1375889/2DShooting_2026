#include "Enemy.h"

void Enemy::Init()
{
	//テクスチャ
	m_spTex = std::make_shared<KdTexture>();
	m_spTex->Load("Asset/Textures/Game/Enemy.png");
	SetSplit(24, 1);

	//オブジェクトタイプ
	m_objType = ObjectType::Enemy;

	//初期値
	m_rad = { 8,16 };
	m_moveSpd = 4.0f;

	//アニメーション値
	m_animeInfo.start = 19;
	m_animeInfo.end = 24;
	m_animeInfo.count = 0.0f;
	m_animeInfo.speed = 0.1f;
}

void Enemy::Update()
{
	m_pos.y -= m_moveSpd;

	if (m_pos.y < -360)
	{
		m_pos.y = 360;
	}
}

void Enemy::PostUpdate()
{
	BaseObject::Animetion();
}

void Enemy::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_spTex, m_pos.x, m_pos.y, 64, 64, &m_rect);
}

void Enemy::Hit()
{
	m_hp--;
	if (m_hp <= 0)
	{
		m_isExpired = true;
	}
}

void Enemy::Spawn(EnemyType a_type, Math::Vector2 a_pos)
{
	m_type = a_type;
	m_pos = a_pos;
	m_alive = true;
}

void Enemy::SetSpawnInfo()
{
	m_waveMorning.spawns = { {EnemyType::Normal,2,{0,200}},
							{ EnemyType::Normal,2,{0,200} },
							{ EnemyType::Normal,2,{0,200} },
							{ EnemyType::Normal,2,{0,200} },
							{ EnemyType::Normal,2,{0,200} },
							{ EnemyType::Normal,2,{0,200} },
						   };





}