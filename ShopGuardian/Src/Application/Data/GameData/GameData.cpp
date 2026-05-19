#include "GameData.h"

void GameData::Init()
{
}

void GameData::Update()
{
	KdDebugGUI::Instance().AddLog("%d\n", m_wave);
	ComboUpdate();
}

void GameData::IncCombo()
{
	m_combo++;
}

void GameData::ResetCombo()
{
	m_combo = 0;
}

void GameData::DecShopComfort()
{
	m_comfort--;
	if (m_comfort <= 0)
	{
		m_comfort = 0;
	}
}

void GameData::Release()
{
}

void GameData::ComboUpdate()
{
	//最高コンボ数更新
	if (m_combo > m_maxCombo)
	{
		m_maxCombo = m_combo;
	}
}