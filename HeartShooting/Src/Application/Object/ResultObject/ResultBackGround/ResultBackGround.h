#pragma once
#include "../../BaseObject.h"

class ResultBackGround : public BaseObject
{
public:

	ResultBackGround() {}
	~ResultBackGround()		override { Release(); }

	void Init()				override;
	void DrawSprite()		override;

private:

	void Release()			override;

	std::shared_ptr<KdTexture>	m_spWinTex = nullptr;
	Math::Vector2				m_winSize = {};

};