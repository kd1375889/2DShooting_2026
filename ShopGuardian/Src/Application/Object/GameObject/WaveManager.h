#pragma once

class BaseEnemy;
class GameScene;
class GameData;

//ゲーム内ウェーブ管理用クラス(GameSceneでインスタンス化、m_objList外)
class WaveManager
{
public:
	
	WaveManager(){}
	~WaveManager() { Release(); }

	enum class WaveType
	{
		Start = 0,	//0:スタート
		Morning,	//1:第一ウェーブ(朝)
		Noon,		//2:第二ウェーブ(昼)
		Night,		//3:第三ウェーブ(夜)
		Finish		//4:ゲーム終了
	};

	void Init();
	void PreUpdate();
	void Update();

	//セッター
	void SetEnemy(std::shared_ptr<BaseEnemy>  a_spEnemy)
	{
		m_spEnemy = a_spEnemy;
	}
	void SetGameScene(std::shared_ptr<GameScene>  a_spGameScene)
	{
		m_spGameScene = a_spGameScene;
	}

	//ゲッター
	const std::list<std::shared_ptr<BaseEnemy>>& GetEnemyList()
	{
		return m_eneList;
	}

	void ChackEnemy();

private:

	void Release();
	void ChangeWave();
	//仮
	void SetResultData();
	void ChackFinFlg();

	std::shared_ptr<BaseEnemy>	m_spEnemy = nullptr;
	std::shared_ptr<GameScene>	m_spGameScene = nullptr;

	std::list<std::shared_ptr<BaseEnemy>> m_eneList = {};

	WaveType			m_currentWave	= WaveType::Start;		//今のウェーブ

	const unsigned int	m_waveChangeTime = 40;		//ウェーブチェンジ間隔
	unsigned int		m_waveTimer = 0;			//ウェーブチェンジタイマー
	unsigned int		m_timer = 0;				//タイマー
	int					m_spawnIndex = 0;			//敵スポーン管理

	bool m_finFlg = false;

	//デバッグ
	bool m_keyFlg = false;
};