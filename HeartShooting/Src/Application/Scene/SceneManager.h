#pragma once

class BaseScene;
class BaseObject;

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

	std::list<std::shared_ptr<BaseObject>> GetObjList() const;

	void AddObject(const std::shared_ptr<BaseObject>& a_obj);

	//リザルト用データ保持(仮)
	void SetResultData(int a_combo, int a_hp, int a_comfort)
	{
		m_maxCombo = a_combo;
		m_playerHP = a_hp;
		m_comfort = a_comfort;
	}
	int GetMaxCombo()
	{
		return m_maxCombo;
	}
	int GetPlayerHP()
	{
		return m_playerHP;
	}
	int GetComfort()
	{
		return m_comfort;
	}

private:

	void Init()
	{
		ChangeScene(m_currentSceneType);
	}

	void ChangeScene(SceneType a_sceneType);

	std::shared_ptr<BaseScene> m_currentScene = nullptr;
	SceneType m_currentSceneType = SceneType::Title;
	SceneType m_nextSceneType = m_currentSceneType;

	//リザルト用データ保持(仮)
	int			m_maxCombo = 0;
	int			m_playerHP = 0;
	int			m_comfort = 0;

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