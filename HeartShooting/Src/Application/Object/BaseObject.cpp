#include "BaseObject.h"

void BaseObject::Update()
{
}

void BaseObject::PostUpdate()
{
}

void BaseObject::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_spTex,m_pos.x, m_pos.y,&m_rect);
}

void BaseObject::Hit()
{
}

void BaseObject::Init()
{
	m_rect = { 0,0,0,0 };
	m_rad = {};
	m_pos = {};
	m_move = {};
	m_moveSpd = 0.0f;

	m_animeMove = 0.0f;
	m_animeSpd = 0.1f;
}

void BaseObject::Release()
{
	if (m_spTex)
	{
		m_spTex = nullptr;
	}
}
