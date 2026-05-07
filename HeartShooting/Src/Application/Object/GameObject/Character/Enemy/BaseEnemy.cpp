#include "BaseEnemy.h"

void BaseEnemy::Init()
{
	//オブジェクトタイプ
	m_objType = ObjectType::Enemy;

	//初期値
	m_rad = { 8,16 };
	m_moveSpd = 3.0f;

	//アニメーション値
	m_animeInfo.start = 19;
	m_animeInfo.end = 24;
	m_animeInfo.count = 0.0f;
	m_animeInfo.speed = 0.1f;
}

void BaseEnemy::Update()
{
	if (m_alive)
	{
		m_move.y = -m_moveSpd;
	}

	m_pos += m_move;

	if (m_pos.y < -360 || m_pos.y > 360)
	{
		m_isExpired = true;
	}
}

void BaseEnemy::PostUpdate()
{
	if (!m_alive)
	{
		ChangeAnimetion();
	}
	BaseObject::Animetion();
}

void BaseEnemy::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_spTex, (int)m_pos.x, (int)m_pos.y, 64, 64, &m_rect);
}

void BaseEnemy::Hit()
{
	m_lockFlg = false;
}

void BaseEnemy::Spawn(EnemyType a_type, Math::Vector2 a_pos)
{
	m_type = a_type;
	m_pos = a_pos;
	m_alive = true;
}

void BaseEnemy::SetSpawnInfo()
{
	m_wave.spawns = { {EnemyType::Normal,2,{0,360}},
					{ EnemyType::Normal,4,{100,360} },
					{ EnemyType::Normal,6,{200,360} },
					{ EnemyType::Normal,8,{-400,360} },
					{ EnemyType::Normal,8,{-250,360} },
					{ EnemyType::Group,10,{-100,360} },
					{ EnemyType::Normal,10,{0,360}},
					{ EnemyType::Normal,11,{100,360} },
					{ EnemyType::Normal,15,{200,360} },
					{ EnemyType::Group,18,{-400,360} },
					{ EnemyType::Normal,20,{-250,360} },
					{ EnemyType::Group,22,{-100,360} },
					{ EnemyType::Normal,24,{0,360}},
					{ EnemyType::Normal,24,{100,360} },
					{ EnemyType::Group,25,{200,360} },
					{ EnemyType::Normal,28,{-400,360} },
					{ EnemyType::Normal,29,{-250,360} },
					{ EnemyType::Group,30,{-100,360} },
				   };
}

void BaseEnemy::ChangeAnimetion()
{
	m_animeInfo.start = 7;
	m_animeInfo.end = 12;
	m_animeInfo.count = 0.0f;
	m_animeInfo.speed = 0.1f;
}