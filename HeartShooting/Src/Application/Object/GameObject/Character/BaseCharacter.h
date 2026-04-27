#pragma once
#include "../../BaseObject.h"

class BaseCharacter :public BaseObject
{
public:

	BaseCharacter() {};
	~BaseCharacter()			override{};

protected:

	int		m_hp = 1;				//体力
	bool	m_alive = false;		//生存フラグ
	int		m_shotCount = 30;		//弾発射間隔
};