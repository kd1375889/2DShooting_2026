#include "ResultData.h"

void ResultData::Init()
{
	m_maxCombo = 0;
	m_playerHP = 0;
	m_comfort = 0;
}

void ResultData::SetData(int a_maxCombo, int a_playerHP, int a_comfort)
{
	m_maxCombo = a_maxCombo;
	m_playerHP = a_playerHP;
	m_comfort = a_comfort;
}

void ResultData::Release()
{
	m_maxCombo = 0;
	m_playerHP = 0;
	m_comfort = 0;
}