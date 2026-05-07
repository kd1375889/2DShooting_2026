#pragma once
#include "../../BaseObject.h"

class BaseCharacter :public BaseObject
{
public:

	BaseCharacter() {};
	~BaseCharacter()			override{};

	bool& GetAliveFlg()
	{
		return m_alive;
	}

protected:

	int			m_hp = 1;					//体力
	bool		m_alive = true;				//生存フラグ

	const int	m_shotInter = 30;			//弾発射インターバル
	int			m_shotCount = m_shotInter;	//弾発射間隔
};