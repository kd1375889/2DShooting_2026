#include "SceneManager.h"
#include "TitleScene/TitleScene.h"
#include "GameScene/GameScene.h"
#include "ResultScene/ResultScene.h"
#include "../Data/ResultData/ResultData.h"

void SceneManager::PreUpdate()
{
	if (m_currentSceneType != m_nextSceneType)
	{
		ChangeScene(m_nextSceneType);
	}

	m_currentScene->PreUpdate();
}

void SceneManager::Update()
{
	m_currentScene->Update();
}

void SceneManager::PostUpdate()
{
	m_currentScene->PostUpdate();
}

void SceneManager::PreDraw()
{
	m_currentScene->PreDraw();
}

void SceneManager::Draw()
{
	m_currentScene->Draw();
}

void SceneManager::DrawSprite()
{
	m_currentScene->DrawSprite();
}

void SceneManager::DrawDebug()
{
	m_currentScene->DrawDebug();
}

std::list<std::shared_ptr<BaseObject>> SceneManager::GetObjList() const
{
	return m_currentScene->GetObjList();
}

void SceneManager::AddObject(const std::shared_ptr<BaseObject>& a_obj)
{
	m_currentScene->AddObjList(a_obj);
}

void SceneManager::Init()
{
	ChangeScene(m_currentSceneType);
	m_resultData = std::make_shared<ResultData>();
	m_resultData->Init();
}

void SceneManager::Release()
{
	if (m_currentScene)
	{
		m_currentScene = nullptr;
	}
}

void SceneManager::ChangeScene(SceneType a_sceneType)
{
	switch (a_sceneType)
	{
	case SceneType::Title:
		m_currentScene = std::make_shared<TitleScene>();
		break;
	case SceneType::Game:
		m_currentScene = std::make_shared<GameScene>();
		break;
	case SceneType::Result:
		m_currentScene = std::make_shared<ResultScene>();
		break;
	}

	m_currentScene->Init();
	m_currentSceneType = a_sceneType;
}