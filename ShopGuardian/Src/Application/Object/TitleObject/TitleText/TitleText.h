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

	void Release()		override;

	//タイトルロゴ
	std::shared_ptr<KdTexture>  m_spLogoTex = nullptr;
	Math::Vector2				m_logoPos = {};

	//操作ガイド
	std::shared_ptr<KdTexture>	m_spGuideTex = nullptr;
	Math::Vector2				m_guidePos = {};
	const float					m_MaxAlpha = 1.0f;		//最高透明度
	const float					m_MinAlpha = 0.4f;		//最小透明度
	float						m_alpha = 0.0f;			//透明度
	float						m_alphaAdd = 0.008f;	//点滅速度
};