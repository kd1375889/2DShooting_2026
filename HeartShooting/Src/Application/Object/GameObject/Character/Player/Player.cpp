#include "Player.h"

void Player::Init()
{
	//テクスチャ
	m_spTex = std::make_shared<KdTexture>();
	m_spTex->Load("Asset/Textures/Game/Player.png");
	m_rect = { 96,35,16,35};
	SetScale(0.5f);
}

void Player::Update()
{
}

void Player::Release()
{
	m_curPos = {};
	m_curAng = 0.0f;
}

void Player::Action()
{

}