#include "Bullet.h"
#include "../../../Scene/SceneManager.h"

void Bullet::Init()
{
	//テクスチャ
	m_spTex = std::make_shared<KdTexture>();
	m_spTex->Load("Asset/Textures/Game/PlayerBullet.png");

	//オブジェクトタイプ
	m_objType = ObjectType::Bullet;

	//初期値
	m_moveSpd = 8.0f;
	m_rect = { 0,0,32,32 };
	m_rad = { 16,16 };
	m_angle = 0.0f;
	m_alive = false;
}

void Bullet::Update()
{
	//カーソルへの角度を使用して移動量計算
	m_move.x = cos(m_angle) * m_moveSpd;
	m_move.y = sin(m_angle) * m_moveSpd;

	//座標確定
	m_pos += m_move;

	if (m_pos.x < m_ScreenMinX - m_rad.x ||
		m_pos.x > m_ScreenMaxX + m_rad.x ||
		m_pos.y < m_ScreenMinY - m_rad.y ||
		m_pos.y > m_ScreenMaxY + m_rad.y)
	{
		m_alive = false;
	}

	Hit();
}

void Bullet::PostUpdate()
{
}

void Bullet::Hit()
{
	if (!m_alive)return;

	//プレイヤーの弾と敵
	//std::list<std::shared_ptr<BaseObject>>::iterator itr;
	//itr = SceneManager::Instance().GetObjList().begin();
	//
	//while (itr != SceneManager::Instance().GetObjList().end())
	//{
	//	//if ((*itr)->GetObjType() == ObjectType::Enemy)
	//	{
	//		//Math::Vector2 ePos = (*itr)->GetPos();
	//		//float disX, disY, dis;
	//		//disX = ePos.x - m_pos.x;
	//		//disY = ePos.y - m_pos.y;
	//		//dis = sqrt(disX * disX + disY * disY);

	//		//if (dis < m_rad.y + (*itr)->GetRadius().y)
	//		//{
	//		//	(*itr)->Hit();
	//		//	m_alive = false;
	//		//	return;
	//		//}
	//	}
	//}

	std::list<std::shared_ptr<BaseObject>> objList;
	std::list<std::shared_ptr<BaseObject>>::iterator itr;
	objList = SceneManager::Instance().GetObjList();
	itr = objList.begin();

	while (itr != objList.end())
	{
		if ((*itr)->GetObjType() == ObjectType::Enemy)
		{
			Math::Vector2 ePos = (*itr)->GetPos();
			float disX, disY, dis;
			disX = ePos.x - m_pos.x;
			disY = ePos.y - m_pos.y;
			dis = sqrt(disX * disX + disY * disY);

			if (dis < m_rad.y + (*itr)->GetRadius().y)
			{
				(*itr)->Hit();
				m_alive = false;
				return;
			}
		}
		//else if ((*itr)->GetObjType() == ObjectType::Player)
		//{
		//	Math::Vector2 ePos = (*itr)->GetPos();
		//	float disX, disY, dis;
		//	disX = ePos.x - m_pos.x;
		//	disY = ePos.y - m_pos.y;
		//	dis = sqrt(disX * disX + disY * disY);

		//	if (dis < m_rad.y + (*itr)->GetRadius().y)
		//	{
		//		(*itr)->Hit();
		//		m_alive = false;
		//		return;
		//	}
		//}
		itr++;
	}
}

void Bullet::Shot(Math::Vector2 a_pos, float a_angle)
{
	m_pos = a_pos;
	m_angle = a_angle;
	m_alive = true;
}

void Bullet::Release()
{
	if (m_spTex)
	{
		m_spTex = nullptr;
	}
}