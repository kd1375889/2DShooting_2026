#pragma once
#include "../BaseScene/BaseScene.h"

class WaveManager;
class GUI;

class GameScene :public BaseScene,public std::enable_shared_from_this<GameScene>
{
public:

	GameScene() {}
	~GameScene() {}

	void PreUpdate()	override;
	void Update()		override;
	//ゲッター
	const std::shared_ptr<GUI>& GetGUI()
	{
		return m_spGUI;
	}

private:

	void Event()	override;
	void Init()		override;
	void Release()	override;

	std::shared_ptr<WaveManager> m_spWaveManager;
	std::shared_ptr<GUI>		 m_spGUI;
};
