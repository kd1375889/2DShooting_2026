#pragma once
#include "../BaseCharacter.h"

class Enemy : public BaseCharacter
{
public:

	Enemy() {}
	~Enemy()			override { Release(); }

	void Init()			override;
	void Update()		override;
	void PostUpdate()	override;
	void DrawSprite()	override;
	void Hit()			override;

private:

};