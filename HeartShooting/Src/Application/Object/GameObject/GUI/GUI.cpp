#include "GUI.h"

void GUI::Init()
{
	m_spTimerTex = std::make_shared<KdTexture>();
	m_spTimerTex->Load("Asset/Textures/GUI/Font.png");
}

void GUI::Update()
{
	ComboUpdate();
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
	DrawTime();
	DrawCombo();
}

void GUI::ComboUpdate()
{
	m_comboTimer++;
	if (m_comboTimer/60 > m_ComboStop)
	{
		m_combo = 0;
		m_comboTimer = 0;
	}

	int combo = 0;
	combo = m_combo;
	for (int i = m_ComboDigits - 1; i >= 0; --i)
	{
		m_comboDis[i] = combo % 10;
		combo /= 10;
	}
}

void GUI::DrawCombo()
{
	KdDebugGUI::Instance().AddLog("%d\n", m_combo);
	
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

void GUI::DrawTime()
{
	//タイマー表示(2ケタ:2ケタ)
	for (int i = 0; i < m_MaxDigits; ++i)
	{
		Math::Rectangle rc;
		if (i != 2)
		{
			rc = { 9 * m_time[i],31,9,15 };
		}
		else
		{
			rc = { 27,46,9,15 };
		}
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