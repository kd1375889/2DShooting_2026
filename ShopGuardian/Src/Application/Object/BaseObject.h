#pragma once

class BaseObject :public KdGameObject
{
public:

	BaseObject() {}
	virtual ~BaseObject()		override { Release(); }

	//オブジェクトの種類
	enum class ObjectType
	{
		None,		//0:なし
		Player,		//1:プレイヤー
		Enemy,		//2:敵
		Bullet,		//3:弾
		Item,		//4:アイテム
		Stage,		//5:ステージ
		GUI			//6:GUI
	};

	//弾の種類
	enum class BulletType
	{
		None,		//0:無し
		Rice,		//1:おむすび
		Udon		//2:うどん
	};

	//アニメーション
	struct AnimetionInfo
	{
		int		start;			//開始コマ
		int		end;			//終了コマ
		float	count;			//コマ数カウント
		float	speed;			//アニメーション速度
	};

	virtual void Update()		override;	//更新	
	virtual void PostUpdate()	override;	//後更新
	virtual void DrawSprite()	override;	//描画
	virtual void Hit();						//当たり判定時処理
	virtual void Animetion();				//アニメーション管理

	//ゲッター
	ObjectType		GetObjType() { return m_objType; }	//オブジェクトタイプ
	BulletType		GetBulletType()	{return m_bullet;}			//弾/有効弾タイプ
	Math::Vector2	GetPos() { return m_pos; }			//座標
	Math::Vector2	GetRadius() { return m_rad; }		//半径
	bool GetAliveFlg() { return m_alive; }				//生死フラグ

protected:

	virtual void Init()			override {};
	virtual void Release()		override;

	//アニメーション
	virtual void ChangeAnimetion() {};			//アニメーションの種類変更時に呼び出し
	void SetSplit(int a_splitX, int a_splitY);	//テクスチャ分割数セッター
	void CalcAnimeFrame(int frame);				//切り取り範囲計算

	//ゲーム画面サイズ
	const Math::Vector2	m_ScreenSize = { 1280,720 };		//ウィンドウサイズ
	const Math::Vector2 m_UIWindowSize = { 340,720 };		//UIウィンドウサイズ
	const float			m_GameScrMinX = -m_ScreenSize.x / 2;					//左端
	const float			m_GameScrMaxX = m_ScreenSize.x / 2 - m_UIWindowSize.x;	//右端
	const float			m_GameScrMinY = -m_ScreenSize.y / 2;					//下端
	const float			m_GameScrMaxY = m_ScreenSize.y / 2;						//上端
	
	ObjectType		m_objType = ObjectType::None;	//オブジェクトの種類
	BulletType		m_bullet = BulletType::None;

	std::shared_ptr<KdTexture>	m_spTex = nullptr;	//テクスチャ

	Math::Rectangle m_rect = {};					//切り取り範囲
	Math::Vector2	m_rad = {};						//半径
	
	Math::Vector2	m_pos = {};						//座標
	Math::Vector2	m_move = {};					//移動量
	float			m_moveSpd = 0.0f;				//移動スピード
	bool			m_alive = true;					//生存フラグ

	//アニメーション
	AnimetionInfo	m_animeInfo = {};	//アニメーション管理
	int				m_splitX = 1;		//分割数X
	int				m_splitY = 1;		//分割数Y
	Math::Vector2	m_rectMin = {};		//切り取り最小値
};
