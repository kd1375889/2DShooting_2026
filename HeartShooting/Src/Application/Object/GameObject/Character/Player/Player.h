#pragma once
#include "../BaseCharacter.h"

class Player : public BaseCharacter
{
public:

	Player(){}
	~Player()			override { Release(); }

	void Init()			override;
	void Update()		override;
	void DrawSprite()	override;

private:

	void Release()		override;
	void Action();					//プレイヤー操作
};