#include "GUI.h"
#include "../../../Data/GameData/GameData.h"

void GUI::Init()
{
	//UIウィンドウ
	m_spWinTex= std::make_shared<KdTexture>();
	m_spWinTex->Load("Asset/Textures/GameScene/GUI/UIWindow.png");

	//テキスト
	m_spTextTex = std::make_shared<KdTexture>();
	m_spTextTex->Load("Asset/Textures/GameScene/GUI/Text.png");

	//ウェーブ表示
	m_spWaveTex = std::make_shared<KdTexture>();
	m_spWaveTex->Load("Asset/Textures/GameScene/GUI/NowWave.png");

	//数字
	m_spTimerTex = std::make_shared<KdTexture>();
	m_spTimerTex->Load("Asset/Textures/GameScene/GUI/Font.png");

	//HP
	m_spHPTex = std::make_shared<KdTexture>();
	m_spHPTex->Load("Asset/Textures/GameScene/GUI/HP.png");

	//Comfort
	m_spComTex = std::make_shared<KdTexture>();
	m_spComTex->Load("Asset/Textures/GameScene/GUI/Comfort.png");
}

void GUI::Update()
{
	CalcDisCombo();
	CalcDisTime(m_spGameData->GetTimer());
}

void GUI::CalcDisCombo()
{
	//コンボ表示用計算
	int combo = m_spGameData->GetNowCombo();
	for (int i = m_ComboDigits - 1; i >= 0; --i)
	{
		m_comboDis[i] = combo % 10;
		combo /= 10;
	}
}

void GUI::CalcDisTime(unsigned int a_time)
{
	//表示時間を計算し格納
	unsigned int time = 0;
	time = a_time;
	for (int i = m_MaxDigits - 1; i >= 0; --i)
	{
		m_time[i] = time % 10;
		time /= 10;
	}
}

void GUI::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_spWinTex,470,0,m_UIWindowSize.x, m_UIWindowSize.y);

	DrawUIText();
	DrawNowWave();
	DrawTime();
	DrawCombo();
	DrawPlayerHP();
	DrawComfort();
}

void GUI::Release()
{
	if (m_spTimerTex)
	{
		m_spTimerTex = nullptr;
	}
	if (m_spWinTex)
	{
		m_spWinTex = nullptr;
	}
}

void GUI::DrawUIText()
{
	Math::Rectangle rc;
	//Time
	rc = { 0,0,9 * 4,15 };
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_spTextTex, 400, 130, 27*4, 45, &rc);
	//Combo
	rc = { 27,30,9 * 5,15 };
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_spTextTex, 410, 20, 27*5, 45, &rc);
	//HP
	rc = { 0,45,9 * 2,15 };
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_spTextTex, 377, -80, 27 * 2, 45, &rc);
	//Comfort
	rc = { 0,60,9 * 7,15 };
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_spTextTex, 460, -190, 27 * 8, 45, &rc);

}

void GUI::DrawNowWave()
{
	Math::Rectangle rc;
	//NowWave
	rc = { 0,0,9 * 7,17 };
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_spWaveTex,430, 230,27*7,45, &rc);

	switch (m_spGameData->GetCurrentWave())
	{
	case 1:
		rc = { 0,16,9 * 7,16 };
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_spWaveTex, m_wavePos.x, m_wavePos.y, 27 * 7, 45, &rc);
		break;
	case 2:
		rc = { 0,32,9 * 4,15 };
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_spWaveTex, m_wavePos.x, m_wavePos.y, 27 * 4, 45, &rc);
		break;
	case 3:
		rc = { 0,48,9 * 5,15 };
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_spWaveTex, m_wavePos.x, m_wavePos.y, 27 * 5, 45, &rc);
		break;
	}
}

void GUI::DrawTime()
{
	//タイマー表示(2ケタ:2ケタ)
	for (int i = 0; i < m_MaxDigits; ++i)
	{
		Math::Rectangle rc;

		rc = { 9 * m_time[i],31,9,15 };
		KdShaderManager::Instance().m_spriteShader.DrawTex(
			m_spTimerTex,
			m_timePos.x + i * 27,
			m_timePos.y,
			27,
			45,
			&rc
		);
	}
}

void GUI::DrawCombo()
{
	for (int i = 0; i < m_ComboDigits; ++i)
	{
		Math::Rectangle rc;
		rc = { 9 * m_comboDis[i],31,9,15 };

		KdShaderManager::Instance().m_spriteShader.DrawTex(
			m_spTimerTex,
			m_comboPos.x + i * 27,
			m_comboPos.y,
			27,
			45,
			&rc
		);
	}
}

void GUI::DrawPlayerHP()
{
	for (int i = 0; i < m_spGameData->GetPlayerHP(); i++)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_spHPTex, m_playerHPPos.x + 35 * i, m_playerHPPos.y);
	}
}

void GUI::DrawComfort()
{
	Math::Rectangle rc;
	for (int i = 0; i < m_MaxComfort; i++)
	{
		rc = { 0,0,16,32 };
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_spComTex, m_comPos.x + 16 * i, m_comPos.y, 16, 32, &rc);
	}
	for (int i = 0; i < m_spGameData->GetShopComfort(); i++)
	{
		rc = { 16,0,16,32 };
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_spComTex, m_comPos.x + 16 * i, m_comPos.y,16,32, &rc);
	}
}
