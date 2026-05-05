#include "WaveManager.h"
#include "../../Object/GameObject/Character/Enemy/Enemy.h"
#include "../../Scene/GameScene/GameScene.h"
#include "GUI/GUI.h"

void WaveManager::Init()
{

}

void WaveManager::Update()
{
	//タイマーカウント
	m_timer++;

	//ウェーブ変更
	if (m_timer / 60 > m_waveChangeTime)
	{
		ChangeWave();

		std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>();
		enemy->Init();
		enemy->Spawn(Enemy::EnemyType::Normal, Math::Vector2(0, 200));
		m_spOwner->AddObjList(enemy);
	}

	//タイマー表示
	m_spOwner->GetGUI()->CalcDisTime(m_timer / 60);
}

void WaveManager::Release()
{
}

void WaveManager::ChangeWave()
{
	//ウェーブ変更
	switch (m_currentWave)
	{
		case WaveType::Morning:
			m_currentWave = WaveType::Noon;
			break;
		case WaveType::Noon:
			m_currentWave = WaveType::Night;
			break;
		case WaveType::Night:
			m_currentWave = WaveType::Finish;
			break;
	}
	
	m_timer = 0;
}
