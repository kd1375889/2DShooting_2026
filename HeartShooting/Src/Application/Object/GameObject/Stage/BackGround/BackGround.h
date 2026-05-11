#pragma once
#include "../../../BaseObject.h"

class BackGround : public BaseObject
{
public:

	BackGround() {}
	~BackGround()		override { Release(); }

	void Init()			override;
	void DrawSprite()	override;

private:

};