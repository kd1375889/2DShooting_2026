#pragma once
#include "../../BaseObject.h"

class GUI:public BaseObject
{
public:

	GUI(){}
	~GUI() { Release(); }

	void Init()			override;
	void Update()		override;
	void DrawSprite()	override;

	void CalcDisTime(unsigned int a_time);			//表示時間計算
	void IncCombo()
	{
		m_combo++;
		m_comboTimer = 0;
	}
	void ResetCombo()
	{
		m_combo = 0;
		m_comboTimer = 0;
	}
	void SetPlayerHP(int& a_playerHP)
	{
		m_playerHP = a_playerHP;
	}
	void SetComfort(int  a_comfort)
	{
		m_comfort = a_comfort;
	}
	void SetNowWave(int a_wave)
	{
		m_wave = a_wave;
	}

	//仮
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

	void Release()	override;
	void ComboUpdate();

	void DrawUIText();
	void DrawNowWave();
	void DrawTime();
	void DrawCombo();
	void DrawPlayerHP();
	void DrawComfort();

	//UI表示テクスチャ
	std::shared_ptr<KdTexture> m_spWinTex = nullptr;		//UIウィンドウ
	std::shared_ptr<KdTexture> m_spTextTex = nullptr;		//テキスト

	//ウェーブ表示
	std::shared_ptr<KdTexture>	m_spWaveTex = nullptr;		//ウェーブ表示
	Math::Vector2				m_wavePos = {};
	int							m_wave;

	//ウェーブタイマー
	std::shared_ptr<KdTexture> m_spTimerTex = nullptr;
	static const int	m_MaxDigits = 3;			//表示桁数
	int					m_time[m_MaxDigits] = {};	//表示用のタイム格納配列
	Math::Vector2		m_timePos = { 400,80 };		//タイマー座標

	//コンボ
	int					m_combo = 0;
	int					m_maxCombo = 0;
	const int			m_ComboStop = 8;
	int					m_comboTimer = 0;
	static const int	m_ComboDigits = 2;
	int					m_comboDis[m_ComboDigits] = {};
	Math::Vector2		m_comboPos = { 410 , -30 };

	//HP
	std::shared_ptr<KdTexture>	m_spHPTex = nullptr;
	int							m_playerHP = 5;
	Math::Vector2				m_playerHPPos = { 380,-130 };

	//Shop Comfort
	std::shared_ptr<KdTexture>	m_spComTex = nullptr;
	const int					m_MaxComfort = 10;
	int							m_comfort = m_MaxComfort;
	Math::Vector2				m_comPos = { 370,-260 };
};
