#include "TitleBackGround.h"

void TitleBackGround::Init()
{
	//テクスチャ
	m_spTex = std::make_shared<KdTexture>();
	m_spTex->Load("Asset/Textures/TitleScene/Morning.png");
	m_rect = { 0,0,(long)m_ScreenSize.x,(long)m_ScreenSize.y };

	//オブジェクトタイプ
	m_objType = ObjectType::Stage;
	
}