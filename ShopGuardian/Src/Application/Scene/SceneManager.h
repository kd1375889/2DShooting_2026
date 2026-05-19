#pragma once

class BaseScene;
class BaseObject;
class ResultData;

class SceneManager
{
public:

	//シーンタイプ
	enum class SceneType
	{
		Title,
		Game,
		Result
	};

	void PreUpdate();
	void Update();
	void PostUpdate();

	void PreDraw();
	void Draw();
	void DrawSprite();
	void DrawDebug();

	//次のシーンをセット
	void SetNextScene(SceneType a_nextSceneType)
	{
		m_nextSceneType = a_nextSceneType;
	}

	//現在のシーンのオブジェクトリストに追加
	void AddObject(const std::shared_ptr<BaseObject>& a_obj);

	//現在のシーンのオブジェクトリストを取得
	std::list<std::shared_ptr<BaseObject>> GetObjList() const;

	std::shared_ptr<ResultData> GetResultData()
	{
		return m_resultData;
	}

private:

	void Init();
	void Release();

	//シーン切り替え
	void ChangeScene(SceneType a_sceneType);

	std::shared_ptr<BaseScene> m_currentScene = nullptr;	//現在のシーン
	SceneType m_currentSceneType = SceneType::Title;		//現在のシーンタイプ
	SceneType m_nextSceneType = m_currentSceneType;			//次のシーンタイプ

	//テスト
	std::shared_ptr<ResultData>	m_resultData = nullptr;

private:

	SceneManager() { Init(); }
	~SceneManager() { Release(); }

public:

	static SceneManager& Instance()
	{
		static SceneManager instance;
		return instance;
	}
};