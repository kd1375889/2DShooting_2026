#include "TitleText.h"

void TitleText::Init()
{
	//タイトルロゴ
	m_spLogoTex = std::make_shared<KdTexture>();
	m_spLogoTex->Load("Asset/Textures/TitleScene/TitleLogo.png");
	//操作ガイド
	m_spGuideTex = std::make_shared<KdTexture>();
	m_spGuideTex->Load("Asset/Textures/TitleScene/Guide.png");

	//座標
	m_logoPos = { 0,170 };
	m_guidePos = { 280,-120 };

	//オブジェクトタイプ
	m_objType = ObjectType::None;
}

void TitleText::Update()
{
	//ガイド透明度変化
	m_alpha += m_alphaAdd;
	if (m_alpha > m_MaxAlpha)
	{
		m_alpha = m_MaxAlpha;
		m_alphaAdd *= -1;
	}
	else if (m_alpha < m_MinAlpha)
	{
		m_alpha = m_MinAlpha;
		m_alphaAdd *= -1;
	}
}

void TitleText::DrawSprite()
{
	//タイトルロゴ
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_spLogoTex, m_logoPos.x, m_logoPos.y);

	//クリック位置ガイド
	Math::Color color = { 1.0f,1.0f,1.0f,m_alpha };
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_spGuideTex, m_guidePos.x, m_guidePos.y, nullptr, &color);
}

void TitleText::Release()
{
	BaseObject::Release();
	if (m_spLogoTex)
	{
		m_spLogoTex = nullptr;
	}
	if (m_spGuideTex)
	{
		m_spGuideTex = nullptr;
	}
}