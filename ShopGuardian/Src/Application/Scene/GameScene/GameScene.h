#pragma once
#include "../BaseScene/BaseScene.h"

class WaveManager;
class GameData;

class GameScene :public BaseScene,public std::enable_shared_from_this<GameScene>
{
public:

	GameScene() {}
	~GameScene() {}

	void PreUpdate()	override;
	void Update()		override;
	
	//ゲッター
	const std::shared_ptr<WaveManager>& GetWave()
	{
		return m_spWaveManager;
	}
	const std::shared_ptr<GameData>& GetGameData()
	{
		return m_spGameData;
	}

private:

	void Event()	override;
	void Init()		override;
	void Release()	override;

	std::shared_ptr<WaveManager>	 m_spWaveManager = nullptr;
	std::shared_ptr<GameData>		 m_spGameData = nullptr;
};
