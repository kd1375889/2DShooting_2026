#pragma once
#include "../../BaseObject.h"

class TitleText : public BaseObject
{
public:

	TitleText() {}
	~TitleText()		override { Release(); }

	void Init()			override;
	void Update()		override;
	void DrawSprite()	override;

private:

	//タイトルロゴ
	std::shared_ptr<KdTexture>  m_spLogoTex = nullptr;
	Math::Vector2				m_logoPos = {};

	//操作ガイド
	std::shared_ptr<KdTexture>	m_spGuideTex = nullptr;
	Math::Vector2				m_guidePos = {};
	float						m_alphaAdd = 0.008f;	//点滅速度
	float						m_alpha = 0.0f;			//透明度
};