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

	//アニメーション値
	m_animeInfo.start = 19;
	m_animeInfo.end = 24;
	m_animeInfo.count = 0.0f;
	m_animeInfo.speed = 0.1f;
}

void Enemy::Update()
{

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