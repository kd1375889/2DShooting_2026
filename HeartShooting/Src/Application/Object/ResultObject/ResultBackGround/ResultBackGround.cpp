#include "ResultBackGround.h"

void ResultBackGround::Init()
{
	//背景
	m_spTex = std::make_shared<KdTexture>();
	m_spTex->Load("Asset/Textures/ResultScene/Night.png");
	m_rect = { 0,0,(long)m_ScreenSize.x,(long)m_ScreenSize.y };
	//ウィンドウ
	m_spWinTex = std::make_shared<KdTexture>();
	m_spWinTex->Load("Asset/Textures/GameScene/GUI/UIWindow.png");
	m_winSize = { 700,600 };

	//オブジェクトタイプ
	m_objType = ObjectType::None;
}

void ResultBackGround::DrawSprite()
{
	//背景
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_spTex, m_pos.x, m_pos.y, &m_rect);
	//ウィンドウ
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_spWinTex, m_pos.x, m_pos.y, m_winSize.x, m_winSize.y);
}

void ResultBackGround::Release()
{
	BaseObject::Release();

	if (m_spWinTex)
	{
		m_spWinTex = nullptr;
	}
}
