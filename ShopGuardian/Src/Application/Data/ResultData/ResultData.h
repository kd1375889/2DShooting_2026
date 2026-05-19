#pragma once

class ResultData
{
public:
	
	ResultData(){}
	~ResultData() { Release(); }

	void Init();
	void SetData(int a_maxCombo,int a_playerHP,int a_comfort);

	//テスト
	int GetMaxCombo()
	{
		return m_maxCombo;
	}
	int GetPlayerHP()
	{
		return m_playerHP;
	}
	int GetComfort()
	{
		return m_comfort;
	}

private:

	void Release();

	int			m_maxCombo = 0;
	int			m_playerHP = 0;
	int			m_comfort = 0;
};