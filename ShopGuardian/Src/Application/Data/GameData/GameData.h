#pragma once

class GameData
{
public:
	
	GameData() {};
	~GameData() { Release(); }

	void Init();
	void Update();

	//コンボ
	void IncCombo();
	void ResetCombo();
	//Comfort
	void DecShopComfort();

	//セッター
	void SetCurrentWave(int a_wave)
	{
		m_wave = a_wave;
	}
	void SetTimer(int a_timer)
	{
		m_timer = a_timer;
	}
	void SetPlayerHP(int a_playerHP)
	{
		m_playerHP = a_playerHP;
	}

	//ゲッター
	int GetCurrentWave()
	{
		return m_wave;
	}
	int GetTimer()
	{
		return m_timer;
	}
	int GetNowCombo()
	{
		return m_combo;
	}
	int GetPlayerHP()
	{
		return m_playerHP;
	}
	int GetShopComfort()
	{
		return m_comfort;
	}
	//リザルト用
	int GetMaxCombo()
	{
		return m_maxCombo;
	}


private:

	void Release();

	//コンボ
	void ComboUpdate();

	//ウェーブ
	int					m_wave = 0;

	//タイマー
	unsigned int		m_timer = 0;

	//コンボ
	int					m_combo = 0;
	int					m_maxCombo = 0;
	
	//プレイヤーHP
	int					m_playerHP = 5;

	//Comfort
	const int			m_MaxComfort = 10;
	int					m_comfort = m_MaxComfort;
};