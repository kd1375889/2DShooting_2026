#include "WaveManager.h"
#include "../../Object/GameObject/Character/Enemy/BaseEnemy.h"
#include "../../Object/GameObject/Character/Enemy/NormalEnemy/NormalEnemy.h"
#include "../../Object/GameObject/Character/Enemy/GroupEnemy/GroupEnemy.h"
#include "../../Scene/GameScene/GameScene.h"
#include "GUI/GUI.h"
#include "../../Scene/SceneManager.h"

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
	//デバッグキー
	if (GetAsyncKeyState('I') & 0x8000)
	{
		SetResultData();
		SceneManager::Instance().SetNextScene(SceneManager::SceneType::Result);
	}
	if (GetAsyncKeyState('C') & 0x8000)
	{
		if (!m_keyFlg)
		{
			ChangeWave();
			m_keyFlg = true;
		}
	}
	else
	{
		m_keyFlg = false;
	}

	//タイマーカウント
	m_waveTimer++;
	m_timer++;

	//ウェーブ変更
	if (m_waveTimer / 60 > m_waveChangeTime &&
		!m_eneList.size())
	{
		ChangeWave();
	}

	ChackEnemy();

	//タイマー表示
	m_spGameScene->GetGUI()->CalcDisTime(m_timer / 60);
	m_spGameScene->GetGUI()->SetComfort(m_comfort);

	//ゲーム終了フラグチェック
	ChackFinFlg();
	if (m_finFlg)
	{
		SetResultData();
		SceneManager::Instance().SetNextScene(SceneManager::SceneType::Result);
	}
}

void WaveManager::ChackEnemy()
{
	std::vector<BaseEnemy::SpawnData> spawns;
	switch (m_currentWave)
	{
		case WaveType::Morning:
			spawns = m_spEnemy->GetSpawnInfoMorning().spawns;
			KdDebugGUI::Instance().AddLog("Morning\n");
			break;
		case WaveType::Noon:
			spawns = m_spEnemy->GetSpawnInfoNoon().spawns;
			KdDebugGUI::Instance().AddLog("Noon\n");
			break;
		case WaveType::Night:
			spawns = m_spEnemy->GetSpawnInfoNight().spawns;
			KdDebugGUI::Instance().AddLog("Night\n");
			break;
	}

	while(m_spawnIndex < spawns.size() &&
		spawns[m_spawnIndex].time <= m_waveTimer / 60)
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
		enemy->SetGameScene(m_spGameScene);
		m_spGameScene->AddObjList(enemy);
		m_eneList.push_back(enemy);
		m_spawnIndex++;
	}
}

void WaveManager::CalcShopComfort(int a_damage)
{
	m_comfort -= a_damage;
	if (m_comfort <= 0)
	{
		m_comfort = 0;
	}
}

void WaveManager::Release()
{
	if (m_spEnemy)
	{
		m_spEnemy = nullptr;
	}
	if (m_spGameScene)
	{
		m_spGameScene = nullptr;
	}
	if (m_eneList.size())
	{
		m_eneList.clear();
	}
}

void WaveManager::ChangeWave()
{
	//リセット
	if (m_eneList.size())
	{
		m_eneList.clear();
	}

	//ウェーブ変更
	switch (m_currentWave)
	{
		case WaveType::Start:
			m_currentWave = WaveType::Morning;
			m_spGameScene->GetGUI()->SetNowWave(1);
			break;
		case WaveType::Morning:
			m_currentWave = WaveType::Noon;
			m_spGameScene->GetGUI()->SetNowWave(2);
			break;
		case WaveType::Noon:
			m_currentWave = WaveType::Night;
			m_spGameScene->GetGUI()->SetNowWave(3);
			break;
		case WaveType::Night:
			m_currentWave = WaveType::Finish;
			SetResultData();
			SceneManager::Instance().SetNextScene(SceneManager::SceneType::Result);
			break;
	}
	
	m_waveTimer = 0;
	m_spawnIndex = 0;
}

void WaveManager::SetResultData()
{
	SceneManager::Instance().SetResultData(
		m_spGameScene->GetGUI()->GetMaxCombo(), m_spGameScene->GetGUI()->GetPlayerHP(), m_spGameScene->GetGUI()->GetComfort());
}

void WaveManager::ChackFinFlg()
{
	if (m_spGameScene->GetGUI()->GetPlayerHP() <= 0 ||
		m_comfort <= 0)
	{
		m_finFlg = true;
	}
}