#pragma once
#include "../BaseCharacter.h"

class GameScene;

class BaseEnemy : public BaseCharacter
{
public:

	//敵種類
	enum class EnemyType
	{
		None,		//0:なし
		Normal,		//1:普通の敵
		Group,		//2:団体の敵
		Regular,	//3:特定の武器でしか倒せない敵
		Boss		//4:見られている間は攻撃したら被弾
	};

	//敵スポーンデータ
	struct SpawnData
	{
		EnemyType		type;		//敵の種類
		BulletType		request;	//有効な弾
		int				time;		//出現時間
		Math::Vector2	pos;		//初期座標
	};

	//敵スポーンデータ全て
	struct SpawnInfo
	{
		std::vector<SpawnData> spawns;
	};

	BaseEnemy() {}
	virtual ~BaseEnemy()		override { Release(); }

	virtual void Init()			override;
	virtual void Update()		override;
	void		 PostUpdate()	override;
	void		 DrawSprite()	override;
	virtual void Hit()			override;

	//スポーンデータ読み込み
	bool LoadSpawnInfo();

	//セッター
	void SetSpawnInfo();
	void Spawn(EnemyType a_type, BulletType a_request, Math::Vector2 a_pos);
	void SetLockFlg(bool a_lockFlg)
	{
		m_lockFlg = a_lockFlg;
	}

	void SetGameScene(std::shared_ptr<GameScene>  a_spGameScene)
	{
		m_spGameScene = a_spGameScene;
	}

	//ゲッター
	SpawnInfo& GetSpawnInfoMorning()
	{
		return m_wave[0];
	}
	SpawnInfo& GetSpawnInfoNoon()
	{
		return m_wave[1];
	}
	SpawnInfo& GetSpawnInfoNight()
	{
		return m_wave[2];
	}
	bool& GetLockFlg()
	{
		return m_lockFlg;
	}

protected:

	void Release()			override;
	void ChangeAnimetion()	override;
	void LoadRequTex();

	std::shared_ptr<GameScene>	m_spGameScene = nullptr;

	std::shared_ptr<KdTexture>	m_spHPTex = nullptr;
	std::shared_ptr<KdTexture>	m_spThinkTex = nullptr;
	std::shared_ptr<KdTexture>	m_spRequTex = nullptr;

	EnemyType					m_type = EnemyType::None;

	//敵スポーンデータ
	static const int	m_TotalWave = 3;
	SpawnInfo			m_wave[m_TotalWave];

	//ロックオン済みか
	bool				m_lockFlg = false;

	int count = 0;

};