#pragma once
#include "../BaseEnemy.h"

class RegularEnemy :public BaseEnemy
{
public:

	RegularEnemy() {}
	~RegularEnemy()		override { Release(); }

	void Init()			override;
	void Update()		override;

private:

	void Release()	override;

	EnemyType m_type = EnemyType::Regular;
};