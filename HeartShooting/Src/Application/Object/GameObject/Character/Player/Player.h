#pragma once
#include "../BaseCharacter.h"

class Player : public BaseCharacter
{
public:

	Player(){}
	~Player()			override { Release(); }

	void Init()			override;
	void Update()		override;

private:

	void Release()		override;
	void Action();					//プレイヤー操作

	POINT		m_curPos = {};		//カーソル座標
	float		m_curAng = 0.0f;	//プレイヤーキャラからカーソルへの角度
};