#include "WaveManager.h"
#include "../../Object/GameObject/Character/Enemy/BaseEnemy.h"
#include "../../Object/GameObject/Character/Enemy/NormalEnemy/NormalEnemy.h"
#include "../../Object/GameObject/Character/Enemy/GroupEnemy/GroupEnemy.h"
#include "../../Scene/GameScene/GameScene.h"
#include "GUI/GUI.h"

void WaveManager::Init()
{
	ChangeWave();
}

void WaveManager::PreUpdate()
{
	std::list<std::shared_ptr<BaseEnemy>>::iterator itr;
	itr = m_eneList.begin();

	while (itr != m_eneList.end())
	{
		if ((*itr)->IsExpired())
		{
			itr = m_eneList.erase(itr);
		}
		else
		{
			itr++;
		}
	}
}

void WaveManager::Update()
{
	//タイマーカウント
	m_timer++;

	//ウェーブ変更
	if (m_timer / 60 > m_waveChangeTime)
	{
		ChangeWave();
	}

	ChackEnemy();

	//タイマー表示
	m_spGameScene->GetGUI()->CalcDisTime(m_timer / 60);
}

void WaveManager::ChackEnemy()
{
	std::vector<BaseEnemy::SpawnData> spawns = m_spEnemy->GetSpawnInfo().spawns;
	while(m_spawnIndex < spawns.size() &&
		spawns[m_spawnIndex].time <= m_timer / 60)
	{
		//敵スポーン
		std::shared_ptr<BaseEnemy> enemy;
		switch (spawns[m_spawnIndex].type)
		{
		case BaseEnemy::EnemyType::Normal:
			enemy = std::make_shared<NormalEnemy>();
			break;
		case BaseEnemy::EnemyType::Group:
			enemy = std::make_shared<GroupEnemy>();
			break;
		}
		enemy->Init();
		enemy->Spawn(
			spawns[m_spawnIndex].type,
			spawns[m_spawnIndex].pos
		);
		m_spGameScene->AddObjList(enemy);
		m_eneList.push_back(enemy);
		m_spawnIndex++;
	}
}

void WaveManager::Release()
{
}

void WaveManager::ChangeWave()
{
	//ウェーブ変更
	switch (m_currentWave)
	{
		case WaveType::Start:
			m_currentWave = WaveType::Morning;
			m_spEnemy->SetSpawnInfo();
			break;
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
	m_spawnIndex = 0;
}
