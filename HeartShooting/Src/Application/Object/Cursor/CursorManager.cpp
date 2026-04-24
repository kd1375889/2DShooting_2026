#include "CursorManager.h"

void CursorManager::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_spTex, m_curPos.x, m_curPos.y);
}

void CursorManager::CalcMousePos(HWND a_hWnd)
{
	//ディスプレイ上のマウス座標を取得(ディスプレイの左上が(0,0))
	GetCursorPos(&m_curPos);
	//指定のウィンドウ基準のマウス座標に変換(ウィンドウの左上が(0,0))
	ScreenToClient(a_hWnd, &m_curPos);
	//マウス座標を実行ウィンドウの座標(中心が(0,0))に補正
	m_curPos.x -= m_ScreenSize.x / 2;
	m_curPos.y -= m_ScreenSize.y / 2;
	m_curPos.y *= -1;
}

const float CursorManager::CalcToCurAng(Math::Vector2 a_pos)
{
	float disX, disY, dis;

	disX = m_curPos.x - a_pos.x;
	disY = m_curPos.y - a_pos.y;
	dis = sqrt(disX * disX + disY * disY);

	return atan2(disY, disX);
}

void CursorManager::Init()
{
	//テクスチャ
	m_spTex = std::make_shared<KdTexture>();
	m_spTex->Load("Asset/Textures/GUI/Cursor.png");

	//初期座標
	m_curPos = {};
}

void CursorManager::Release()
{
	m_curPos = {};
}