#pragma once

class Enemy;
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
		Morning,	//1:第一ウェーブ(朝)
		Noon,		//2:第二ウェーブ(昼)
		Night,		//3:第三ウェーブ(夜)
		Finish		//4:ゲーム終了
	};

	void Init();
	void Update();

	void SetEnemy(std::shared_ptr<Enemy>  a_spEnemy)
	{
		m_spEnemy = a_spEnemy;
	}
	void SetOwner(std::shared_ptr<GameScene>  a_spOwner)
	{
		m_spOwner = a_spOwner;
	}

private:

	void Release();
	void ChangeWave();

	std::shared_ptr<Enemy>		m_spEnemy = nullptr;
	std::shared_ptr<GameScene>	m_spOwner = nullptr;

	WaveType			m_currentWave = WaveType::Morning;	//今のウェーブ

	const unsigned int	m_waveChangeTime = 5;		//ウェーブチェンジ間隔
	unsigned int		m_timer = 0.0f;				//タイマー
};