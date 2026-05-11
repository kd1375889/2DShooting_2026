#pragma once
#include "../../BaseObject.h"

class BaseCharacter :public BaseObject
{
public:

	BaseCharacter() {};
	virtual ~BaseCharacter()	override { Release(); }

protected:

	void Release()		override {}

	int			m_hp = 1;					//体力

	const int	m_shotInter = 30;			//弾発射インターバル
	int			m_shotCount = m_shotInter;	//弾発射間隔
};