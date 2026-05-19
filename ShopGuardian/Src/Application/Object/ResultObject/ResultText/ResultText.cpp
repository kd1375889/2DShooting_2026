#include "ResultText.h"
#include "../../../Scene/SceneManager.h"
#include "../../../Data/ResultData/ResultData.h"

void ResultText::Init()
{
	m_resultData = SceneManager::Instance().GetResultData();

	//ガイド
	m_spGuideTex = std::make_shared<KdTexture>();
	m_spGuideTex->Load("Asset/Textures/ResultScene/Guide.png");

	//テキスト
	m_spTextTex = std::make_shared<KdTexture>();
	m_spTextTex->Load("Asset/Textures/GameScene/GUI/Text.png");

	//Combo
	m_spComboTex = std::make_shared<KdTexture>();
	m_spComboTex->Load("Asset/Textures/GameScene/GUI/Font.png");

	//HP
	m_spHPTex = std::make_shared<KdTexture>();
	m_spHPTex->Load("Asset/Textures/GameScene/GUI/HP.png");

	//HP
	m_spComTex = std::make_shared<KdTexture>();
	m_spComTex->Load("Asset/Textures/GameScene/GUI/Comfort.png");
}

void ResultText::Update()
{
	//コンボ表示用計算
	int combo = m_resultData->GetMaxCombo();
	for (int i = m_ComboDigits - 1; i >= 0; --i)
	{
		m_comboDis[i] = combo % 10;
		combo /= 10;
	}

	//ガイド透明度変化
	m_alpha += m_alphaAdd;
	if (m_alpha > 1.0f)
	{
		m_alpha = 1.0f;
		m_alphaAdd *= -1;
	}
	else if (m_alpha < 0.4f)
	{
		m_alpha = 0.4f;
		m_alphaAdd *= -1;
	}
}

void ResultText::DrawSprite()
{
	DrawGuide();
	DrawUIText();
	DrawMaxCombo();
	DrawPlayerHP();
	DrawComfort();
}

void ResultText::DrawGuide()
{
	Math::Color color = { 1.0f,1.0f,1.0f,m_alpha };
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_spGuideTex, 500, -200,nullptr,&color);
}

void ResultText::DrawUIText()
{
	Math::Rectangle rc;
	//MaxCombo
	rc = { 0,30,9 * 8,15 };
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_spTextTex, -150, 140, 27 * 8, 45, &rc);
	//HP
	rc = { 0,45,9 * 2,15 };
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_spTextTex, -230, 0, 27 * 2, 45, &rc);
	//Comfort
	rc = { 0,60,9 * 7,15 };
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_spTextTex, -150, -140, 27 * 8, 45, &rc);
}

void ResultText::DrawMaxCombo()
{
	for (int i = 0; i < m_ComboDigits; ++i)
	{
		Math::Rectangle rc;
		rc = { 9 * m_comboDis[i],31,9,15 };

		KdShaderManager::Instance().m_spriteShader.DrawTex(
			m_spComboTex,
			-220 + i * 27,
			75,
			27,
			45,
			&rc
		);
	}
}

void ResultText::DrawPlayerHP()
{
	int hp = m_resultData->GetPlayerHP();
	for (int i = 0; i < hp; i++)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_spHPTex, -230 + 35 * i, -70);
	}
}

void ResultText::DrawComfort()
{
	int comfort = m_resultData->GetComfort();
	Math::Rectangle rc;
	for (int i = 0; i < 10; i++)
	{
		rc = { 0,0,16,32 };
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_spComTex, -230 + 16 * i, -200, 16, 32, &rc);
	}
	for (int i = 0; i < comfort; i++)
	{
		rc = { 16,0,16,32 };
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_spComTex, -230 + 16 * i, -200, 16, 32, &rc);
	}
}
