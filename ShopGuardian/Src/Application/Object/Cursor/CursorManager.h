#pragma once

class CursorManager
{
public:

	void DrawSprite();

	//カーソル座標計算(main.cppのExecute()で呼び出し中)
	void CalcMousePos(HWND a_hWnd);

	//カーソルへの角度計算
	const float CalcToCurAng(Math::Vector2 a_pos);

	//カーソルがホバー状態ならTrue
	bool CalcHoverChack(Math::Vector2& a_pos, Math::Vector2& a_rad);

	//セッター
	//ロックオンできる状態かどうか
	void SetLockOKFlg(bool a_lockOKFlg)
	{
		m_lockOKFlg = a_lockOKFlg;
	}
	//ロックオン状態かどうか
	void SetLockFlg(bool a_lockFlg)
	{
		m_lockFlg = a_lockFlg;
	}

	//ゲッター
	//カーソル座標取得
	const Math::Vector2& GetCurPos();

private:

	void Init();
	void Release();

	std::shared_ptr<KdTexture>	m_spTex[3] = {};				//テクスチャ
	POINT						m_curPos = {};					//座標
	Math::Vector2				m_curSize = { 24,24 };			//描画サイズ
	const Math::Vector2			m_ScreenSize = { 1280,720 };	//ゲームウィンドウサイズ

	bool						m_lockOKFlg = false;
	bool						m_lockFlg = false;

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