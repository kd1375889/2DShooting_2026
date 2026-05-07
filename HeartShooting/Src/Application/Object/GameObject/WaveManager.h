#pragma once

class BaseEnemy;
class GameScene;

//ゲーム内ウェーブ管理用クラス(GameSceneでインスタンス化、m_objList外)
class WaveManager
{
public:
	
	WaveManager(){}
	~WaveManager() { Release(); }

	enum class WaveType
	{
		None,		//0:無し
		Start,		//1:ゲーム開始時
		Morning,	//2:第一ウェーブ(朝)
		Noon,		//3:第二ウェーブ(昼)
		Night,		//4:第三ウェーブ(夜)
		Finish		//5:ゲーム終了
	};

	void Init();
	void PreUpdate();
	void Update();

	void SetEnemy(std::shared_ptr<BaseEnemy>  a_spEnemy)
	{
		m_spEnemy = a_spEnemy;
	}
	void SetGameScene(std::shared_ptr<GameScene>  a_spGameScene)
	{
		m_spGameScene = a_spGameScene;
	}

	const std::list<std::shared_ptr<BaseEnemy>>& GetEnemyList()
	{
		return m_eneList;
	}

	void ChackEnemy();

private:

	void Release();
	void ChangeWave();

	std::shared_ptr<BaseEnemy>	m_spEnemy = nullptr;
	std::shared_ptr<GameScene>	m_spGameScene = nullptr;

	std::list<std::shared_ptr<BaseEnemy>> m_eneList = {};

	WaveType			m_currentWave	= WaveType::Start;		//今のウェーブ

	const unsigned int	m_waveChangeTime = 30;		//ウェーブチェンジ間隔
	unsigned int		m_timer = 0;				//タイマー
	int					m_spawnIndex = 0;			//敵スポーン管理
};