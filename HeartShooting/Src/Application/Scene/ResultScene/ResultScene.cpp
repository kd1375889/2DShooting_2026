#include "ResultScene.h"
#include "../SceneManager.h"
#include "../../Object/ResultObject/ResultBackGround/ResultBackGround.h"
#include "../../Object/ResultObject/ResultText/ResultText.h"

void ResultScene::Event()
{
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		SceneManager::Instance().SetNextScene(SceneManager::SceneType::Title);
	}
}

void ResultScene::Init()
{
	//背景
	std::shared_ptr<ResultBackGround> backGround = std::make_shared<ResultBackGround>();
	backGround->Init();
	m_objList.push_back(backGround);

	//テキスト
	std::shared_ptr<ResultText> text = std::make_shared<ResultText>();
	text->Init();
	m_objList.push_back(text);
}

void ResultScene::Release()
{

}