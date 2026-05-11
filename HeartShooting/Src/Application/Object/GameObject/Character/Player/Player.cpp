#include "Player.h"
#include "../../../../Scene/GameScene/GameScene.h"
#include "../../../Cursor/CursorManager.h"
#include "../../WaveManager.h"
#include "../../Bullet/Bullet.h"
#include "../../Character/Enemy/BaseEnemy.h"
#include "../../GUI/GUI.h"

void Player::Init()
{
	//テクスチャ
	m_spTex = std::make_shared<KdTexture>();
	m_spTex->Load("Asset/Textures/GameScene/Character/Player/Player2.png");
	SetSplit(9, 3);

	//オブジェクトタイプ
	m_objType = ObjectType::Player;

	//初期値
	m_rad = { 9,13 };
	m_pos = { -170,-200 };
	m_moveSpd = 3.0f;
	m_alive = true;
	m_hp = 5;

	//アニメーション値
	m_animeInfo.start = 10;
	m_animeInfo.end = 15;
	m_animeInfo.count = 0.0f;
	m_animeInfo.speed = 0.1f;
}

void Player::Update()
{
	//移動量とクールタイムリセット
	m_move = {};
	m_coolTimer--;
	if (m_coolTimer <= 0)
	{
		m_coolTimer = 0;
	}

	//弾発射間隔
	m_shotCount--;
	if (m_shotCount < 0) m_shotCount = 0;
	//ロックオン間隔
	m_lockCount--;
	if (m_lockCount < 0)
	{
		m_lockCount = 0;
		CursorManager::Instance().SetLockOKFlg(true);	//ロックオン可能カーソル
	}
	else
	{
		CursorManager::Instance().SetLockOKFlg(false);
	}

	//操作
	Action();

	//移動範囲制限
	if (m_pos.x < m_GameScrMinX + 32)
	{
		m_pos.x = m_GameScrMinX + 32;
	}
	else if (m_pos.x > m_GameScrMaxX - 32)
	{
		m_pos.x = m_GameScrMaxX - 32;
	}
	else if (m_pos.y < m_GameScrMinY + 32)
	{
		m_pos.y = m_GameScrMinY + 32;
	}
	else if (m_pos.y > m_GameScrMaxY - 32)
	{
		m_pos.y = m_GameScrMaxY - 32;
	}

	//座標確定
	m_pos += m_move;
}

void Player::PostUpdate()
{
	//敵との当たり判定
	HitEnemy();

	//アニメーション
	BaseObject::Animetion();

	//GUI管理者にプレイヤーHPを渡す
	m_spGameScene->GetGUI()->SetPlayerHP(m_hp);
}

void Player::DrawSprite()
{
	KdDebugGUI::Instance().AddLog("hp:%d\n", m_hp);
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_spTex, m_pos.x, m_pos.y,64,64,&m_rect);
}

void Player::Hit()
{
	m_hp--;
	if (m_hp <= 0)
	{
		m_alive = false;
	}
	m_coolTimer = m_CoolTime * 60;
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

				//リセット
				m_lockCount = m_lockInter * 60;
				m_lockFlg = false;
				m_lockEnemy.clear();
			}
		}

		CursorManager::Instance().SetLockFlg(m_lockFlg);	//ロックオンカーソル
	}
}

void Player::HitEnemy()
{
	if (m_alive && m_coolTimer <= 0)
	{
		//ウェーブマネージャーから敵リスト取得
		std::list<std::shared_ptr<BaseEnemy>> eneList = m_wave->GetEnemyList();
		std::list<std::shared_ptr<BaseEnemy>>::iterator itr = eneList.begin();

		Math::Vector2 enePos, dis;

		while (itr != eneList.end())
		{
			if ((*itr)->GetAliveFlg())
			{
				enePos = (*itr)->GetPos();
				dis = enePos - m_pos;
				if (dis.Length() < (m_rad + (*itr)->GetRadius()).Length())
				{
					Hit();
					return;
				}
			}
			itr++;
		}
	}

}

void Player::Release()
{
	if (m_spGameScene)
	{
		m_spGameScene = nullptr;
	}
	if (m_wave)
	{
		m_wave = nullptr;
	}
	if (m_lockEnemy.size())
	{
		m_lockEnemy={};
	}
}
