#pragma once
#include "../BaseScene/BaseScene.h"

class TitleScene :public BaseScene
{
public:

	TitleScene(){}
	~TitleScene() { Release(); }

private:

	void Event()	override;
	void Init()		override;

	Math::Vector2 m_doorPos = {};	//背景の入り口の位置
	Math::Vector2 m_doorRad = {};	//入り口半径
};