#pragma once
#include "../../BaseObject.h"

class GameData;

class GUI:public BaseObject
{
public:

	GUI(){}
	~GUI() { Release(); }

	void Init()			override;
	void Update()		override;
	void DrawSprite()	override;

	//セッター
	//データ保持クラス
	void SetGameData(std::shared_ptr<GameData> a_spGameData)
	{
		m_spGameData = a_spGameData;
	}

private:

	void Release()	override;

	//表示用コンボ計算
	void CalcDisCombo();
	//表示用時間計算
	void CalcDisTime(unsigned int a_time);

	//描画
	void DrawUIText();
	void DrawNowWave();
	void DrawTime();
	void DrawCombo();
	void DrawPlayerHP();
	void DrawComfort();

	//データクラス
	std::shared_ptr<GameData>	m_spGameData = nullptr;

	//テクスチャ
	std::shared_ptr<KdTexture> m_spWinTex = nullptr;		//UIウィンドウ
	std::shared_ptr<KdTexture> m_spTextTex = nullptr;		//テキスト

	//ウェーブ
	std::shared_ptr<KdTexture>	m_spWaveTex = nullptr;		//ウェーブ
	Math::Vector2				m_wavePos = { 460, 180 };

	//ウェーブタイマー
	std::shared_ptr<KdTexture> m_spTimerTex = nullptr;
	static const int	m_MaxDigits = 3;			//表示桁数
	int					m_time[m_MaxDigits] = {};	//表示用のタイム格納配列
	Math::Vector2		m_timePos = { 400,80 };		//タイマー座標

	//コンボ
	static const int	m_ComboDigits = 2;
	int					m_comboDis[m_ComboDigits] = {};
	Math::Vector2		m_comboPos = { 410 , -30 };

	//HP
	std::shared_ptr<KdTexture>	m_spHPTex = nullptr;
	Math::Vector2				m_playerHPPos = { 380,-130 };

	//Shop Comfort
	std::shared_ptr<KdTexture>	m_spComTex = nullptr;
	const int					m_MaxComfort = 10;
	int							m_comfort = m_MaxComfort;
	Math::Vector2				m_comPos = { 370,-260 };
};
