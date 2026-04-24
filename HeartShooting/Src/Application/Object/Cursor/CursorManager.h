#pragma once

class CursorManager
{
public:

	void DrawSprite();

	//カーソル座標計算(mainで呼び出し中)
	void CalcMousePos(HWND a_hWnd);

	//カーソルへの角度計算
	const float CalcToCurAng(Math::Vector2 a_pos);

	//ゲッター
	//カーソル座標取得
	const POINT& GetCurPos() const
	{
		return m_curPos;
	}

private:

	void Init();
	void Release();

	std::shared_ptr<KdTexture>	m_spTex = nullptr;				//カーソルテクスチャ
	POINT						m_curPos = {};					//カーソル座標
	const Math::Vector2			m_ScreenSize = { 1280,720 };	//ゲーム画面サイズ

//シングルトンパターン
private:

	CursorManager() { Init(); }
	~CursorManager() { Release(); }

public:

	static CursorManager& Instance()
	{
		static CursorManager instance;
		return instance;
	}
};