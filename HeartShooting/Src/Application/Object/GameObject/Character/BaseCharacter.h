#pragma once
#include "../../BaseObject.h"

class BaseCharacter :public BaseObject
{
public:

	BaseCharacter() {};
	~BaseCharacter()			override{};

	virtual void Update()		override;
	virtual void PostUpdate()	override;

protected:

	virtual void Init()			override;
	virtual void Release()		override;

	int		m_hp = 1;				//体力
	bool	m_alive = false;		//生存フラグ

};