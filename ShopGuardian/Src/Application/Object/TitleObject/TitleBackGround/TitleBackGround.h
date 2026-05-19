#pragma once
#include "../../BaseObject.h"

class TitleBackGround : public BaseObject
{
public:

	//背景の入り口位置情報(クリックでゲームシーンに遷移)
	struct DoorInfo
	{
		Math::Vector2 pos;	//座標
		Math::Vector2 rad;	//半径
	};

	TitleBackGround() {}
	~TitleBackGround()		override { Release(); }

	void Init()				override;

	//ゲッター
	DoorInfo GetDoorInfo()
	{
		return m_doorInfo;
	}

private:
	
	DoorInfo	m_doorInfo;
};