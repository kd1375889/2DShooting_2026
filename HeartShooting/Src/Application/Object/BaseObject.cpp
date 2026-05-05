#include "BaseObject.h"

void BaseObject::Update()
{
}

void BaseObject::PostUpdate()
{

}

void BaseObject::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_spTex,m_pos.x, m_pos.y,&m_rect);
}

void BaseObject::Hit()
{

}

void BaseObject::Animetion()
{
	//アニメーション
	m_animeInfo.count += m_animeInfo.speed;
	int frame = m_animeInfo.start + (int)m_animeInfo.count;
	if (frame > m_animeInfo.end)
	{
		//終了コマを超えたらリセット
		frame = m_animeInfo.start;
		m_animeInfo.count = 0.0f;
	}
	CalcAnimeFrame(frame);
}

void BaseObject::ChangeAnimetion()
{

}

void BaseObject::SetSplit(int a_splitX, int a_splitY)
{
	//分割数セット
	m_splitX = a_splitX;
	m_splitY = a_splitY;
}

void BaseObject::CalcAnimeFrame(int frame)
{
	//何コマ目かを受け取り、切り取り範囲を計算してセット
	int splitX,splitY;
	splitX = (frame - 1) % m_splitX;
	splitY = (frame - 1) / m_splitX;
	m_rectMin.x = splitX * m_rad.x * 2;
	m_rectMin.y = splitY * m_rad.y * 2;

	m_rect = { (long)m_rectMin.x,(long)m_rectMin.y,(long)m_rad.x * 2,(long)m_rad.y * 2 };
}

void BaseObject::Init()
{
	m_objType = ObjectType::None;

	m_rect = { 0,0,0,0 };
	m_rad = {};
	m_pos = {};
	m_move = {};
	m_moveSpd = 0.0f;

	m_animeInfo.start = 0;
	m_animeInfo.end = 1;
	m_animeInfo.count = 0.0f;
	m_animeInfo.speed=0.1f;

	//アニメーション
	m_splitX = 1;
	m_splitY = 1;
	m_rectMin = {};
}

void BaseObject::Release()
{
	if (m_spTex)
	{
		m_spTex = nullptr;
	}
}
