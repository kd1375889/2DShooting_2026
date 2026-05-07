#include "Player.h"
#include "../../../../Scene/GameScene/GameScene.h"
//#include "../../../../Scene/SceneManager.h"
#include "../../../Cursor/CursorManager.h"
#include "../../WaveManager.h"
#include "../../Bullet/Bullet.h"
#include "../../Character/Enemy/BaseEnemy.h"

void Player::Init()
{
	//テクスチャ
	m_spTex = std::make_shared<KdTexture>();
	m_spTex->Load("Asset/Textures/Game/Player2.png");
	SetSplit(9, 3);

	//オブジェクトタイプ
	m_objType = ObjectType::Player;

	//初期値
	m_rad = { 9,13 };
	m_pos = { 0,-200 };
	m_moveSpd = 3.0f;
	m_alive = true;

	//アニメーション値
	m_animeInfo.start = 10;
	m_animeInfo.end = 15;
	m_animeInfo.count = 0.0f;
	m_animeInfo.speed = 0.1f;
}

void Player::Update()
{
	//移動量リセット
	m_move = {};

	//弾発射間隔
	m_shotCount--;
	if (m_shotCount < 0) m_shotCount = 0;
	m_lockCount--;
	if (m_lockCount < 0) m_lockCount = 0;

	//操作
	Action();

	//座標確定
	m_pos += m_move;
}

void Player::PostUpdate()
{
	//アニメーション
	BaseObject::Animetion();
}

void Player::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_spTex, m_pos.x, m_pos.y,64,64,&m_rect);
}

void Player::Hit()
{
	m_isExpired = true;
}

void Player::Action()
{
	//移動
	if (GetAsyncKeyState('W') & 0x8000)
	{
		m_move.y = m_moveSpd;
	}
	if (GetAsyncKeyState('A') & 0x8000)
	{
		m_move.x = -m_moveSpd;
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		m_move.y = -m_moveSpd;
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		m_move.x = m_moveSpd;
	}

	//弾発射
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (m_shotCount <= 0)
		{
			float angle = CursorManager::Instance().CalcToCurAng(m_pos);
			std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>();
			bullet->Init();
			bullet->Shot(Bullet::BulletType::Normal,m_pos,angle);
			bullet->SetGameScene(m_spGameScene);
			m_spGameScene->AddObjList(bullet);
			//SceneManager::Instance().AddObject(bullet);

			m_shotCount = m_shotInter;
		}
	}

	//ロックオン攻撃
	{
		Math::Vector2 enePos;	//敵座標
		Math::Vector2 dis;		//距離

		if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
		{
			if (m_lockCount <= 0)
			{
				//カーソル座標取得
				Math::Vector2 curPos = CursorManager::Instance().GetCurPos();
				//ウェーブマネージャーから敵リスト取得
				std::list<std::shared_ptr<BaseEnemy>> eneList = m_wave->GetEnemyList();
				std::list<std::shared_ptr<BaseEnemy>>::iterator itr = eneList.begin();

				while (itr != eneList.end())
				{
					if (!(*itr)->GetLockFlg())
					{
						//カーソルと敵の距離が近い　かつ　敵が生きているならロックオン
						enePos = (*itr)->GetPos();
						dis = enePos - curPos;
						if (dis.Length() < 64 && (*itr)->GetAliveFlg())
						{
							m_lockEnemy.push_back((*itr));
							(*itr)->SetLockFlg(true);
						}
					}
					itr++;
				}

				m_lockFlg = true;
			}
		}
		else
		{
			m_lockFlg = false;
		}

		//ロックオンが終わる　かつ　敵をロックオンしていたら一斉射撃
		if (!m_lockFlg && !m_lockEnemy.empty())
		{
			//ロックオンした敵への角度を求めてショット
			for (auto& ene : m_lockEnemy)
			{
				enePos = ene->GetPos();
				dis = enePos - m_pos;

				std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>();
				bullet->Init();
				bullet->Shot(Bullet::BulletType::Lock, m_pos, atan2(dis.y, dis.x));
				bullet->SetGameScene(m_spGameScene);
				m_spGameScene->AddObjList(bullet);
				//SceneManager::Instance().AddObject(bullet);

				//リセット
				m_lockCount = m_lockInter;
				m_lockFlg = false;
				m_lockEnemy.clear();
			}
		}

		CursorManager::Instance().SetLockFlg(m_lockFlg);	//ロックオンカーソル
	}
}