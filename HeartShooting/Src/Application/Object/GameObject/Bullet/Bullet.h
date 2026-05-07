#pragma once
#include "../../BaseObject.h"

class GameScene;

class Bullet: public BaseObject
{
public:

	enum class BulletType
	{
		None,		//0:無し
		Normal,		//1:通常弾
		Lock		//2:ロックオン攻撃
	};

	Bullet() {}
	~Bullet()			override { Release(); }

	void Init()			override;
	void Update()		override;
	void PostUpdate()	override;
	void Hit()			override;

	//セッター
	void Shot(BulletType a_type,Math::Vector2 a_pos,float a_angle);
	void SetGameScene(std::shared_ptr<GameScene> a_spGameScene)
	{
		m_spGameScene = a_spGameScene;
	}

private:

	void Release()		override;
	void HitEnemy();

	void NormalBulletUpdate();
	void LockOnBulletUpdate();

	std::shared_ptr<GameScene>	m_spGameScene = nullptr;

	BulletType	m_type = BulletType::None;
	float		m_angle = 0.0f;		//発射位置からカーソルへの角度
	bool		m_alive = false;
};