#include "BackGround.h"

void BackGround::Init()
{
	//テクスチャ
	for (int i = 0; i < 2; i++)
	{
		m_spBackTex[i] = std::make_shared<KdTexture>();
		m_spBackTex[i]->Load("Asset/Textures/Game/Stage01.png");
	}
	m_rect = { 0,0,(long)m_ScreenSize.x,(long)m_ScreenSize.y };

	//スクロール速度
	m_backMove = 3.0f;
}

void BackGround::Update()
{
	//スクロール
	m_pos.y -=m_backMove;
	if (m_pos.y < -720)
	{
		m_pos.y = 0;
	}
}

void BackGround::DrawSprite()
{
	for (int i = 0; i < 2; i++)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_spBackTex[i], m_pos.x, m_pos.y + i * m_ScreenSize.y, &m_rect);
	}
}

void BackGround::Release()
{
}
