#pragma once
#include "../../BaseObject.h"

class ResultText : public BaseObject
{
public:

	ResultText() {}
	~ResultText()		override { Release(); }

	void Init()			override;
	void Update()		override;
	void DrawSprite()	override;

private:

	void DrawGuide();
	void DrawUIText();
	void DrawMaxCombo();
	void DrawPlayerHP();
	void DrawComfort();

	//ガイド
	std::shared_ptr<KdTexture> m_spGuideTex = nullptr;
	float						m_alphaAdd = 0.008f;
	float						m_alpha = 0.0f;

	//テキスト
	std::shared_ptr<KdTexture> m_spTextTex = nullptr;

	//MaxCombo
	std::shared_ptr<KdTexture> m_spComboTex = nullptr;
	static const int	m_ComboDigits = 2;
	int					m_comboDis[m_ComboDigits] = {};

	//HP
	std::shared_ptr<KdTexture> m_spHPTex = nullptr;

	//Comfort
	std::shared_ptr<KdTexture> m_spComTex = nullptr;

};