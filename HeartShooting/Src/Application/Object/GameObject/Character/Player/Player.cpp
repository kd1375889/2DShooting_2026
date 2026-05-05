#include "Player.h"
#include "../../../../Scene/SceneManager.h"
#include "../../../Cursor/CursorManager.h"
#include "../../Bullet/Bullet.h"

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
			bullet->Shot(m_pos, angle);
			SceneManager::Instance().AddObject(bullet);

			m_shotCount = m_shotInter;
		}
	}
}