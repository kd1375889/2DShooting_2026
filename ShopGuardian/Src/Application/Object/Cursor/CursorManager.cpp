#include "CursorManager.h"

void CursorManager::DrawSprite()
{
	//デバッグ
	KdDebugGUI::Instance().AddLog("x:%d y:%d\n", m_curPos.x, m_curPos.y);
	
	if (m_lockFlg)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_spTex[2], m_curPos.x, m_curPos.y,m_curSize.x,m_curSize.y);
	}
	else if (m_lockOKFlg)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_spTex[1], m_curPos.x, m_curPos.y, m_curSize.x, m_curSize.y);
	}
	else
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_spTex[0], m_curPos.x, m_curPos.y, m_curSize.x, m_curSize.y);
	}
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
	float disX, disY;

	disX = m_curPos.x - a_pos.x;
	disY = m_curPos.y - a_pos.y;

	return atan2(disY, disX);
}

bool CursorManager::CalcHoverChack(Math::Vector2& a_pos, Math::Vector2& a_rad)
{
	Math::Vector2 min, max;
	min.x = a_pos.x - a_rad.x;
	min.y = a_pos.y - a_rad.y;
	max.x = a_pos.x + a_rad.x;
	max.y = a_pos.y + a_rad.y;

	if (m_curPos.x >= min.x && m_curPos.x <= max.x &&
		m_curPos.y >= min.y && m_curPos.y <= max.y)
	{
		return true;
	}
	else
	{
		return false;
	}
}

const Math::Vector2& CursorManager::GetCurPos()
{
	float x, y;
	x = m_curPos.x;
	y = m_curPos.y;
	return Math::Vector2(x, y);
}

void CursorManager::Init()
{
	//テクスチャ
	m_spTex[0] = std::make_shared<KdTexture>();
	m_spTex[0]->Load("Asset/Textures/GameScene/GUI/Cursor.png");

	m_spTex[1] = std::make_shared<KdTexture>();
	m_spTex[1]->Load("Asset/Textures/GameScene/GUI/LockOKCursor.png");

	m_spTex[2] = std::make_shared<KdTexture>();
	m_spTex[2]->Load("Asset/Textures/GameScene/GUI/LockCursor.png");

	//初期座標
	m_curPos = {};
}

void CursorManager::Release()
{
	if (m_spTex[0])
	{
		m_spTex[0] = nullptr;
	}
	if (m_spTex[1])
	{
		m_spTex[1] = nullptr;
	}
	if (m_spTex[2])
	{
		m_spTex[2] = nullptr;
	}
	m_curPos = {};
}