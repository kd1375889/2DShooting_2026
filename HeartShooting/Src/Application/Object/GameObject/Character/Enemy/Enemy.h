#pragma once
#include "../BaseCharacter.h"

class Enemy : public BaseCharacter
{
public:

	enum class EnemyType
	{
		None,		//0:なし
		Normal,		//1:普通の敵
		Family,		//2:団体の敵
		Regular,	//3:特定の武器でしか倒せない敵
		Boss		//4:見られている間は攻撃したら被弾
	};

	//ウェーブ
	struct SpawnData
	{
		EnemyType		type;		//敵の種類
		int				spawnTime;	//出現時間
		Math::Vector2	pos;		//初期座標
	};

	struct SpawnInfo
	{
		std::vector<SpawnData> spawns;
	};

	Enemy() {}
	~Enemy()			override { Release(); }

	void Init()			override;
	void Update()		override;
	void PostUpdate()	override;
	void DrawSprite()	override;
	void Hit()			override;

	//ウェーブ
	void Spawn(EnemyType a_type, Math::Vector2 a_pos);
	void SetSpawnInfo();

private:

	EnemyType	m_type = EnemyType::None;

	//ウェーブ
	SpawnInfo m_waveMorning;
};