#include "GameScene.h"
#include "../../Object/GameObject/Stage/BackGround/BackGround.h"
#include "../../Object/GameObject/Character/Player/Player.h"
#include "../../Object/GameObject/Character/Enemy/Enemy.h"

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

}

void GameScene::Release()
{
	if (m_objList.size())
	{
		m_objList.clear();
	}
}
