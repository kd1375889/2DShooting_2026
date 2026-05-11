#pragma once
#include "../BaseScene/BaseScene.h"

class TitleScene :public BaseScene
{
public:

	TitleScene(){}
	~TitleScene() {}

private:

	void Event()	override;
	void Init()		override;
	void Release()	override;

	//仮
	Math::Vector2 m_startPos = {};
	Math::Vector2 m_startRad = {};
};
