#include "GameScene.h"
#include "../../Object/GameObject/Stage/BackGround/BackGround.h"
#include "../../Object/GameObject/Character/Player/Player.h"
#include "../../Object/GameObject/Character/Enemy/BaseEnemy.h"
#include "../../Object/GameObject/WaveManager.h"
#include "../../Object/GameObject/GUI/GUI.h"

void GameScene::PreUpdate()
{
	BaseScene::PreUpdate();

	m_spWaveManager->PreUpdate();
}

void GameScene::Update()
{
	BaseScene::Update();

	m_spWaveManager->Update();
}

void GameScene::Event()
{
	KdDebugGUI::Instance().AddLog("GameScene");
}

void GameScene::Init()
{
	//背景
	std::shared_ptr<BackGround> backGround = std::make_shared<BackGround>();
	backGround->Init();
	m_objList.push_back(backGround);

	//敵
	std::shared_ptr<BaseEnemy> enemy = std::make_shared<BaseEnemy>();
	enemy->Init();

	//ウェーブ管理
	m_spWaveManager = std::make_shared<WaveManager>();
	m_spWaveManager->SetGameScene(shared_from_this());
	m_spWaveManager->SetEnemy(enemy);
	m_spWaveManager->Init();

	//プレイヤー
	std::shared_ptr<Player> player = std::make_shared<Player>();
	player->Init();
	player->SetWaveManager(m_spWaveManager);
	player->SetGameScene(shared_from_this());
	m_objList.push_back(player);

	//GUI
	m_spGUI = std::make_shared<GUI>();
	m_spGUI->Init();
	m_objList.push_back(m_spGUI);
}

void GameScene::Release()
{
	if (m_spWaveManager)
	{
		m_spWaveManager = nullptr;
	}
	if (m_spGUI)
	{
		m_spGUI = nullptr;
	}
	if (m_objList.size())
	{
		m_objList.clear();
	}
}
