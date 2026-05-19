#pragma once
#include "../BaseEnemy.h"

class GroupEnemy :public BaseEnemy
{
public:

	GroupEnemy() {}
	~GroupEnemy()		override { Release(); }

	void Init()			override;
	void Update()		override;

private:

	void Release()	override;
};