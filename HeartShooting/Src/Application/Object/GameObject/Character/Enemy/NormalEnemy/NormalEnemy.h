#pragma once
#include "../BaseEnemy.h"

class NormalEnemy :public BaseEnemy
{
public:

	NormalEnemy(){}
	~NormalEnemy()	override { Release(); }

	void Init()		override;
	void Update()	override;

private:

	void Release()	override;

	EnemyType m_type = EnemyType::Normal;
};