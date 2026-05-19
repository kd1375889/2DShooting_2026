#include "BaseEnemy.h"
#include "../../../../Scene/GameScene/GameScene.h"
#include "../../../../Data/GameData/GameData.h"

void BaseEnemy::Init()
{
	//HPテクスチャ
	m_spHPTex = std::make_shared<KdTexture>();
	m_spHPTex->Load("Asset/Textures/GameScene/GUI/HP.png");
	//吹き出しテクスチャ
	m_spThinkTex = std::make_shared<KdTexture>();
	m_spThinkTex->Load("Asset/Textures/GameScene/Character/Enemy/Think.png");

	//オブジェクトタイプ
	m_objType = ObjectType::Enemy;

	//初期値
	m_rad = { 8,16 };
	m_moveSpd = 3.0f;

	//アニメーション値
	m_animeInfo.start = 19;
	m_animeInfo.end = 24;
	m_animeInfo.count = 0.0f;
	m_animeInfo.speed = 0.1f;
}

void BaseEnemy::Update()
{
	if (m_alive)
	{
		m_move.y = -m_moveSpd;
	}

	m_pos += m_move;

	if (m_pos.y < m_GameScrMinY)
	{
		m_spGameScene->GetGameData()->DecShopComfort();
		m_spGameScene->GetGameData()->ResetCombo();
		m_isExpired = true;
	}
	else if (m_pos.y > m_GameScrMaxY)
	{
		m_isExpired=true;
	}
}

void BaseEnemy::PostUpdate()
{
	BaseObject::Animetion();
}

void BaseEnemy::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_spTex, (int)m_pos.x, (int)m_pos.y, 64, 64, &m_rect);

	for (int i = 0; i < m_hp; i++)
	{
		Math::Vector2 pos;
		pos.x = (m_pos.x - 16 * m_hp) + 16 * i;
		pos.y = m_pos.y + 32;
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_spHPTex, (int)pos.x, (int)pos.y, 16, 16);
	}

	if (m_alive)
	{
		Math::Vector2 pos;
		pos.x = m_pos.x + 32;
		pos.y = m_pos.y + 32;
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_spThinkTex, (int)pos.x, (int)pos.y, 48, 48);	
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_spRequTex, (int)pos.x, (int)pos.y, 32, 32);
	}
}

void BaseEnemy::Hit()
{
	if (!m_alive) return;

	m_hp--;
	if (m_hp <= 0)
	{
		BaseEnemy::ChangeAnimetion();
		m_move.y = m_moveSpd;
		m_alive = false;
	}
	m_lockFlg = false;
}

bool BaseEnemy::LoadSpawnInfo()
{
	std::string fileName = "Asset/Data/EnemySpawnData.csv";
	std::ifstream ifs(fileName);
	if (ifs.fail())
	{
		return false;
	}

	std::string text;
	std::vector<std::string> info = {};
	BulletType request;
	for (int i = 0; i < m_TotalWave; i++)
	{
		while (std::getline(ifs, text))
		{
			std::istringstream iss(text);
			while (std::getline(iss, text, ','))
			{
				info.push_back(text);
			}

			//敵タイプ判定
			if (info[1] == "N")
			{
				m_type = EnemyType::Normal;
			}
			else if (info[1] == "G")
			{
				m_type = EnemyType::Group;
			}
			else
			{
				m_type = EnemyType::None;
			}

			//有効弾判定
			if (info[2] == "R")
			{
				m_bullet = BulletType::Rice;
			}
			else if (info[2] == "U")
			{
				m_bullet = BulletType::Udon;
			}
			else
			{
				m_bullet = BulletType::None;
			}

			m_wave[i].spawns.push_back({ m_type,m_bullet, stoi(info[3]), Math::Vector2(stof(info[4]), stof(info[5])) });

			if (info[0] == "Finish")
			{
				info.clear();
				break;
			}
			info.clear();
		}
	}
	ifs.close();
	return true;
}

void BaseEnemy::LoadRequTex()
{
	switch (m_bullet)
	{
	case BulletType::Rice:
		m_spRequTex = std::make_shared<KdTexture>();
		m_spRequTex->Load("Asset/Textures/GameScene/Bullet/BulletRice.png");
		break;
	case BulletType::Udon:
		m_spRequTex = std::make_shared<KdTexture>();
		m_spRequTex->Load("Asset/Textures/GameScene/Bullet/BulletUdon.png");
		break;
	}
}

void BaseEnemy::Spawn(EnemyType a_type, BulletType a_request, Math::Vector2 a_pos)
{
	m_type = a_type;
	m_bullet = a_request;
	m_pos = a_pos;
	m_alive = true;

	//有効弾テクスチャ
	LoadRequTex();
}

void BaseEnemy::SetSpawnInfo()
{
	//m_wave[0].spawns = {{EnemyType::Normal,4,{0,360}},
	//				{ EnemyType::Normal,6,{0,360} },
	//				{ EnemyType::Normal,8,{200,360} },
	//				{ EnemyType::Normal,10,{250,360} },
	//				{ EnemyType::Normal,10,{-100,360} },
	//				{ EnemyType::Normal,12,{-250,360} },
	//				{ EnemyType::Normal,14,{-100,360}},
	//				{ EnemyType::Normal,17,{0,360} },
	//				{ EnemyType::Normal,19,{200,360} },
	//				{ EnemyType::Normal,20,{0,360} },
	//				{ EnemyType::Group,22,{-100,360} },
	//				{ EnemyType::Normal,24,{-50,360} },
	//				{ EnemyType::Normal,27,{200,360} },
	//				{ EnemyType::Normal,29,{-300,360} },
	//				{ EnemyType::Normal,30,{0,360} },
	//				{ EnemyType::Normal,32,{-200,360} },
	//				{ EnemyType::Group,33,{230,360} },
	//				{ EnemyType::Normal,37,{180,360} },
	//				{ EnemyType::Normal,40,{200,360} },
	//			   };

	//m_wave[1].spawns = { {EnemyType::Normal,4,{0,360}},
	//				{ EnemyType::Normal,5,{-200,360} },
	//				{ EnemyType::Normal,5,{200,360} },
	//				{ EnemyType::Group,8,{0,360} },
	//				{ EnemyType::Normal,15,{-100,360} },
	//				{ EnemyType::Normal,15,{-150,360} },
	//				{ EnemyType::Normal,16,{100,360}},
	//				{ EnemyType::Group,18,{-100,360} },
	//				{ EnemyType::Normal,18,{-200,360} },
	//				{ EnemyType::Normal,21,{-400,360} },
	//				{ EnemyType::Normal,21,{100,360} },
	//				{ EnemyType::Group,23,{50,360}},
	//				{ EnemyType::Normal,25,{-50,360} },
	//				{ EnemyType::Group,25,{-300,360} },
	//				{ EnemyType::Normal,30,{-100,360} },
	//				{ EnemyType::Group,30,{0,360} },
	//				{ EnemyType::Normal,30,{100,360} },
	//				{ EnemyType::Normal,35,{-300,360} },
	//				{ EnemyType::Normal,36,{250,360} },
	//				{ EnemyType::Normal,36,{0,360} },
	//				{ EnemyType::Normal,38,{0,360} },
	//};

	//m_wave[2].spawns = { {EnemyType::Normal,3,{100,360}},
	//				{ EnemyType::Normal,4,{-100,360} },
	//				{ EnemyType::Normal,5,{100,360} },
	//				{ EnemyType::Group,8,{100,360} },
	//				{ EnemyType::Normal,8,{200,360} },
	//				{ EnemyType::Group,8,{250,360} },
	//				{ EnemyType::Normal,11,{-150,360}},
	//				{ EnemyType::Normal,12,{-200,360} },
	//				{ EnemyType::Group,14,{0,360} },
	//				{ EnemyType::Normal,15,{200,360} },
	//				{ EnemyType::Normal,16,{250,360} },
	//				{ EnemyType::Group,17,{-50,360}},
	//				{ EnemyType::Normal,18,{-150,360} },
	//				{ EnemyType::Normal,19,{-250,360} },
	//				{ EnemyType::Normal,23,{230,360} },
	//				{ EnemyType::Normal,25,{-100,360} },
	//				{ EnemyType::Group,27,{50,360}},
	//				{ EnemyType::Normal,29,{-50,360} },
	//				{ EnemyType::Group,32,{-300,360} },
	//				{ EnemyType::Normal,35,{50,360}},
	//				{ EnemyType::Group,35,{200,360} },
	//				{ EnemyType::Normal,37,{0,360} }
	//};
};

void BaseEnemy::Release()
{
	for (int i = 0; i < m_TotalWave; i++)
	{
		if (m_wave[i].spawns.size())
		{
			m_wave[i].spawns.clear();
		}
	}
}

void BaseEnemy::ChangeAnimetion()
{
	m_animeInfo.start = 7;
	m_animeInfo.end = 12;
	m_animeInfo.count = 0.0f;
	m_animeInfo.speed = 0.1f;
}