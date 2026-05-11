#include "TitleScene.h"
#include "../SceneManager.h"
#include "../../Object/Cursor/CursorManager.h"
#include "../../Object/TitleObject/TitleBackGround/TitleBackGround.h"
#include "../../Object/TitleObject/TitleText/TitleText.h"

void TitleScene::Event()
{
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (CursorManager::Instance().CalcHoverChack(m_startPos, m_startRad))
		{
			SceneManager::Instance().SetNextScene(SceneManager::SceneType::Game);
		}
	}
}

void TitleScene::Init()
{
	//メンバ変数
	m_startPos = {-10,-125};
	m_startRad = { 150,125 };

	//背景
	std::shared_ptr<TitleBackGround> backGround = std::make_shared<TitleBackGround>();
	backGround->Init();
	m_objList.push_back(backGround);

	//テキスト
	std::shared_ptr<TitleText> text = std::make_shared<TitleText>();
	text->Init();
	m_objList.push_back(text);
}

void TitleScene::Release()
{
	BaseScene::Release();
}
