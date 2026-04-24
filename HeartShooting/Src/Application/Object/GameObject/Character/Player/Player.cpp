#include "Player.h"
#include "../../../../Scene/SceneManager.h"
#include "../../../Cursor/CursorManager.h"
#include "../../Bullet/Bullet.h"

void Player::Init()
{
	//テクスチャ
	m_spTex = std::make_shared<KdTexture>();
	m_spTex->Load("Asset/Textures/Game/Player2.png");
	m_rect = { 0,35,17,35};

	//初期値
	m_rad = { 17,35 };
	m_pos = { 0,-200 };
	m_alive = true;
}

void Player::Update()
{
	//操作
	Action();

	//アニメーション
	m_animeMove += m_animeSpd;
	if (m_animeMove > 4)m_animeMove = 0;
	m_rect = { (long)m_rad.x * (int)m_animeMove,(long)m_rad.y,(long)m_rad.x,(long)m_rad.y };
}

void Player::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_spTex, m_pos.x, m_pos.y,80,100,&m_rect);
}

void Player::Release()
{

}

void Player::Action()
{
	//弾発射
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		float angle = CursorManager::Instance().CalcToCurAng(m_pos);
		std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>();
		bullet->Init();
		bullet->Shot(m_pos, angle);
		SceneManager::Instance().AddObject(bullet);
	}
}