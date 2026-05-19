#include "BackGround.h"

void BackGround::Init()
{
	//テクスチャ
	m_spTex = std::make_shared<KdTexture>();
	m_spTex->Load("Asset/Textures/GameScene/Stage/Stage01.png");
	m_rect = { 0,0,(long)m_ScreenSize.x,(long)m_ScreenSize.y };

	//オブジェクトタイプ
	m_objType = ObjectType::Stage;
}

void BackGround::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_spTex, m_pos.x, m_pos.y, &m_rect);
}