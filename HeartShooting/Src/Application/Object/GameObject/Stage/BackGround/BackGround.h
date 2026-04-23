#pragma once
#include "../../../BaseObject.h"

class BackGround : public BaseObject
{
public:

	BackGround() {}
	~BackGround()		override { Release(); }

	void Init()			override;
	void Update()		override;
	void DrawSprite()	override;

private:

	void Release()		override;

	std::shared_ptr<KdTexture>	m_spBackTex[2] = {};
	float						m_backMove = 0.0f;
};