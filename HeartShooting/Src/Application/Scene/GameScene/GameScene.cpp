#include "GameScene.h"
#include "../../Object/GameObject/Stage/BackGround/BackGround.h"
#include "../../Object/GameObject/Character/Player/Player.h"
#include "../../Object/GameObject/Character/Enemy/Enemy.h"
#include "../../Object/GameObject/WaveManager.h"
#include "../../Object/GameObject/GUI/GUI.h"
#include "../../Object/Cursor/CursorManager.h"

void GameScene::Update()
{
	Event();

	m_spWaveManager->Update();

	for (auto& obj : m_objList)
	{
		obj->Update();
	}
}

void GameScene::DrawSprite()
{
	// ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== =====
	// 2Dの描画はこの間で行う
	KdShaderManager::Instance().m_spriteShader.Begin();
	{
		for (auto& obj : m_objList)
		{
			obj->DrawSprite();
		}

		//カーソル描画(全てのシーンで)
		CursorManager::Instance().DrawSprite();
	}
	KdShaderManager::Instance().m_spriteShader.End();

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

	//プレイヤー
	std::shared_ptr<Player> player = std::make_shared<Player>();
	player->Init();
	m_objList.push_back(player);

	//敵
	std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>();
	enemy->Init();
	m_objList.push_back(enemy);

	//ウェーブ管理
	m_spWaveManager = std::make_shared<WaveManager>();
	m_spWaveManager->Init();
	m_spWaveManager->SetOwner(shared_from_this());
	m_spWaveManager->SetEnemy(enemy);

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
