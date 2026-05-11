#pragma once
#include "../../BaseObject.h"

class TitleBackGround : public BaseObject
{
public:

	TitleBackGround() {}
	~TitleBackGround()		override { Release(); }

	void Init()				override;

private:

};