#pragma once
#include "../../BaseObject.h"

class GUI:public BaseObject
{
public:

	GUI(){}
	~GUI() { Release(); }

	void Init()			override;
	void CalcDisTime(unsigned int a_time);			//表示時間計算
	void DrawSprite()	override;

private:

	//ウェーブタイマー
	std::shared_ptr<KdTexture> m_spTimerTex;

	static const int	m_MaxDigits = 5;			//表示桁数
	int					m_time[m_MaxDigits] = {};	//表示用のタイム格納配列
	Math::Vector2		m_timePos = { -30,300 };	//タイマー座標

};
