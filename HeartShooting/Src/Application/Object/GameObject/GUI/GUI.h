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
		m_combo += 1;
		m_comboTimer = 0;
	}

private:

	void ComboUpdate();
	void DrawCombo();
	void DrawTime();

	//ウェーブタイマー
	std::shared_ptr<KdTexture> m_spTimerTex;

	static const int	m_MaxDigits = 5;			//表示桁数
	int					m_time[m_MaxDigits] = {};	//表示用のタイム格納配列
	Math::Vector2		m_timePos = { -30,300 };	//タイマー座標

	//コンボ
	int					m_combo = 0;
	const int			m_ComboStop = 5;
	int					m_comboTimer = 0;

	static const int	m_ComboDigits = 2;
	int					m_comboDis[m_ComboDigits] = {};
	Math::Vector2		m_comboPos = { 200,300 };

};
