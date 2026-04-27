#pragma once

class BaseObject :public KdGameObject
{
public:

	//オブジェクトの種類
	enum class ObjectType
	{
		None,		//0:なし(当たり判定なし)
		Player,		//1:プレイヤー
		Enemy,		//2:敵
		Bullet,		//3:弾
		Item,		//4:アイテム
		Stage		//5:ステージ(当たり判定あり)
	};

	//アニメーション
	struct AnimetionInfo
	{
		int		start;			//開始コマ
		int		end;			//終了コマ
		float	count;			//コマ数カウント
		float	speed;			//アニメーション速度
	};

	BaseObject() {};
	virtual ~BaseObject()		override { Release(); }

	virtual void Update()		override;
	virtual void PostUpdate()	override;
	virtual void DrawSprite()	override;
	virtual void Hit();						//当たり判定時処理
	virtual void Animetion();				//アニメーション管理

	//ゲッター
	ObjectType		GetObjType() { return m_objType; }
	Math::Vector2	GetPos() { return m_pos; }
	Math::Vector2	GetRadius() { return m_rad; }

protected:

	virtual void Init()			override;
	virtual void Release()		override;

	//アニメーション
	void ChangeAnimetion();						//アニメーションの種類変更時に呼び出し
	void SetSplit(int a_splitX, int a_splitY);	//テクスチャ分割数セッター
	void CalcAnimeFrame(int frame);				//切り取り範囲計算

	//ゲーム画面サイズ
	const Math::Vector2	m_ScreenSize = { 1280,720 };
	const float			m_ScreenMinX = -m_ScreenSize.x / 2;
	const float			m_ScreenMaxX = m_ScreenSize.x / 2;
	const float			m_ScreenMinY = -m_ScreenSize.y / 2;
	const float			m_ScreenMaxY = m_ScreenSize.y / 2;
	
	ObjectType		m_objType = ObjectType::None;	//オブジェクトの種類

	std::shared_ptr<KdTexture>	m_spTex = nullptr;	//テクスチャ

	Math::Rectangle m_rect = {};					//切り取り範囲
	Math::Vector2	m_rad = {};						//半径
	Math::Vector2	m_pos = {};						//座標
	Math::Vector2	m_move = {};					//移動量
	float			m_moveSpd = 0.0f;				//移動スピード
		
	AnimetionInfo	m_animeInfo;					//アニメーション管理

	//アニメーション
	int m_splitX;				//分割数X
	int m_splitY;				//分割数Y
	Math::Vector2 m_rectMin;	//切り取り最小値
};
