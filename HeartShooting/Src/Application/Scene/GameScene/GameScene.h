#pragma once
#include "../BaseScene/BaseScene.h"

class GameScene :public BaseScene
{
public:

	GameScene() {}
	~GameScene() {}

	bool m_text = true;

private:

	void Event() override;
	void Init() override;
};
