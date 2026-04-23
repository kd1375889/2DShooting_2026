#pragma once

class BaseScene;

class SceneManager
{
public:

	//シーン情報
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

	const std::list<std::shared_ptr<KdGameObject>>& GetObjList();

	void AddObject(const std::shared_ptr<KdGameObject>& a_obj);

private:

	void Init()
	{
		ChangeScene(m_currentSceneType);
	}

	void ChangeScene(SceneType a_sceneType);

	std::shared_ptr<BaseScene> m_currentScene = nullptr;
	SceneType m_currentSceneType = SceneType::Game;
	SceneType m_nextSceneType = m_currentSceneType;

private:
	SceneManager() { Init(); }
	~SceneManager() {}

public:

	static SceneManager& Instance()
	{
		static SceneManager instance;
		return instance;
	}
};