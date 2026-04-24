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
	const float			m_ScreenMinX = -m_ScreenSize.x / 2;
	const float			m_ScreenMaxX = m_ScreenSize.x / 2;
	const float			m_ScreenMinY = -m_ScreenSize.y / 2;
	const float			m_ScreenMaxY = m_ScreenSize.y / 2;
	
	std::shared_ptr<KdTexture>	m_spTex = nullptr;	//テクスチャ

	Math::Rectangle m_rect = {0,0,0,0};				//切り取り範囲
	Math::Vector2	m_rad = {};						//半径
	Math::Vector2	m_pos = {};						//座標
	Math::Vector2	m_move = {};					//移動量
	float			m_moveSpd = 0.0f;				//移動スピード
		
	//アニメーション
	float			m_animeMove = 0.0f;
	float			m_animeSpd = 0.1f;

};
