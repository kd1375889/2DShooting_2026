#include "Bullet.h"
#include "../../../Scene/SceneManager.h"
#include "../../../Scene/GameScene/GameScene.h"
#include "../../../Data/GameData/GameData.h"

void Bullet::Init()
{
	//オブジェクトタイプ
	m_objType = ObjectType::Bullet;

	//初期値
	m_moveSpd = 10.0f;
	m_rect = { 0,0,32,32 };
	m_rad = { 16,16 };
	m_angle = 0.0f;
	m_alive = true;
}

void Bullet::Update()
{
	switch (m_shot)
	{
	case ShotType::Normal:
		NormalBulletUpdate();
		break;
	case ShotType::Lock:
		LockOnBulletUpdate();
		break;
	}

	//座標確定
	m_pos += m_move;

	if (m_pos.x < m_GameScrMinX - m_rad.x ||
		m_pos.x > m_GameScrMaxX - m_rad.x ||
		m_pos.y < m_GameScrMinY - m_rad.y ||
		m_pos.y > m_GameScrMaxY + m_rad.y)
	{
		m_isExpired = true;
	}

	HitEnemy();
}

void Bullet::PostUpdate()
{
	if (!m_alive)
	{
		m_isExpired = true;
	}
}

void Bullet::Hit()
{
	m_alive = false;
}

void Bullet::Shot(BulletType a_bullet, ShotType a_shot,Math::Vector2 a_pos, float a_angle)
{
	m_bullet = a_bullet;
	m_shot = a_shot;
	m_pos = a_pos;
	m_angle = a_angle;
	m_alive = true;

	LoadTex();
}

void Bullet::Release()
{
	if (m_spTex)
	{
		m_spTex = nullptr;
	}
	if (m_spGameScene)
	{
		m_spGameScene = nullptr;
	}
}

void Bullet::LoadTex()
{
	switch (m_bullet)
	{
	case BulletType::Rice:
		m_spTex = std::make_shared<KdTexture>();
		m_spTex->Load("Asset/Textures/GameScene/Bullet/BulletRice.png");
		break;
	case BulletType::Udon:
		m_spTex = std::make_shared<KdTexture>();
		m_spTex->Load("Asset/Textures/GameScene/Bullet/BulletUdon.png");
		break;
	}
}

void Bullet::HitEnemy()
{
	if (!m_alive)return;

	//弾と敵
	std::list<std::shared_ptr<BaseObject>> objList;
	std::list<std::shared_ptr<BaseObject>>::iterator itr;
	objList = SceneManager::Instance().GetObjList();
	itr = objList.begin();

	while (itr != objList.end())
	{
		if ((*itr)->GetObjType() == ObjectType::Enemy)
		{
			Math::Vector2 dis = (*itr)->GetPos() - m_pos;

			if (dis.Length() < m_rad.y + (*itr)->GetRadius().y)
			{
				if ((*itr)->GetAliveFlg() && (*itr)->GetBulletType() == m_bullet)
				{
					(*itr)->Hit();
					Hit();
					m_spGameScene->GetGameData()->IncCombo();
					return;
				}
			}
		}
		itr++;
	}
}

void Bullet::NormalBulletUpdate()
{
	//カーソルへの角度を使用して移動量計算
	m_move.x = cos(m_angle) * m_moveSpd;
	m_move.y = sin(m_angle) * m_moveSpd;
}

void Bullet::LockOnBulletUpdate()
{
	//敵に向かって高速で移動
	m_move.x = cos(m_angle) * m_moveSpd * 5;
	m_move.y = sin(m_angle) * m_moveSpd * 5;
}