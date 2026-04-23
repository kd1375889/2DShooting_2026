#pragma once

class BaseObject :public KdGameObject
{
public:

	BaseObject(){}
	virtual ~BaseObject()		override { Release(); }

	virtual void Update()		override;
	virtual void PostUpdate()	override;
	virtual void DrawSprite()	override;
	virtual void Hit();

protected:

	virtual void Init()			override;
	virtual void Release()		override;

	const Math::Vector2	m_ScreenSize = { 1280,720 };
	
	std::shared_ptr<KdTexture>	m_spTex = nullptr;	//テクスチャ

	Math::Rectangle m_rect = {0,0,0,0};				//切り取り範囲
	Math::Vector2	m_rad = {};						//半径
	Math::Vector2	m_pos = {};						//座標
	Math::Vector2	m_move = {};					//移動量

	//スクロール処理
	float			m_scrollX = 0.0f;				//スクロール値
	float			m_scrollMin = 0.0f;				//スクロール最小値
	float			m_scrollMax = 0.0f;				//スクロール最大値
};
