#pragma once
#include "../BaseCharacter.h"

class GameScene;
class BaseEnemy;
class WaveManager;

class Player : public BaseCharacter
{
public:

	Player(){}
	~Player()			override { Release(); }

	void Init()			override;
	void Update()		override;
	void PostUpdate()	override;
	void DrawSprite()	override;
	void Hit()			override;

	void SetGameScene(std::shared_ptr<GameScene> a_spGameScene)
	{
		m_spGameScene = a_spGameScene;
	}
	void SetWaveManager(std::shared_ptr<WaveManager> a_wave)
	{
		m_wave = a_wave;
	}

private:

	void Action();					//プレイヤー操作

	std::shared_ptr<GameScene>			m_spGameScene = nullptr;

	//ロックオン攻撃
	std::shared_ptr<WaveManager>		m_wave = nullptr;
	std::vector<std::shared_ptr<BaseEnemy>>	m_lockEnemy = {};
	bool								m_lockFlg = false;
	const int							m_lockInter = 3;
	int									m_lockCount = 0;
};