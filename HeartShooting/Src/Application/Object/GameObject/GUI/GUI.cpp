#include "GUI.h"

void GUI::Init()
{
	m_spTimerTex = std::make_shared<KdTexture>();
	m_spTimerTex->Load("Asset/Textures/GUI/Font.png");
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