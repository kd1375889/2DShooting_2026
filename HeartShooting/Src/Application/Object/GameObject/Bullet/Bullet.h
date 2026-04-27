#pragma once
#include "../../BaseObject.h"

class Bullet: public BaseObject
{
public:

	Bullet() {}
	~Bullet()			override { Release(); }

	void Init()			override;
	void Update()		override;
	void PostUpdate()	override;
	void Hit()			override;

	//セッター
	void Shot(Math::Vector2 a_pos,float a_angle);

private:

	void Release()		override;

	float	m_angle = 0.0f;		//発射位置からカーソルへの角度
	bool	m_alive = false;
};