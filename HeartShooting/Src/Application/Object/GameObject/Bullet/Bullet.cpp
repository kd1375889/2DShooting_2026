#include "Bullet.h"

void Bullet::Init()
{
	m_spTex = std::make_shared<KdTexture>();
	m_spTex->Load("Asset/Textures/Game/PlayerBullet.png");

	m_moveSpd = 8.0f;
	m_rect = { 0,0,64,64 };
	m_rad = { 32,32 };
	m_angle = 0.0f;
	m_alive = false;
}

void Bullet::Update()
{
	m_move.x = cos(m_angle) * m_moveSpd;
	m_move.y = sin(m_angle) * m_moveSpd;

	m_pos += m_move;
}

void Bullet::Hit()
{
}

void Bullet::Shot(Math::Vector2 a_pos, float a_angle)
{
	m_pos = a_pos;
	m_angle = a_angle;
	m_alive = true;
}

void Bullet::Release()
{
	if (m_spTex)
	{
		m_spTex = nullptr;
	}
}