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
};