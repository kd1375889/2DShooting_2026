#pragma once

class BaseObject;

class BaseScene
{
public:

	BaseScene() {};
	virtual ~BaseScene() { Release(); };

	virtual void Init();

	virtual	void	PreUpdate();
	virtual void	Update();
	void			PostUpdate();

	void			PreDraw();
	void			Draw();
	void			DrawSprite();
	void			DrawDebug();

	const std::list<std::shared_ptr<BaseObject>>& GetObjList()
	{
		return m_objList;
	}

	void AddObjList(const std::shared_ptr<BaseObject>& a_obj)
	{
		m_objList.push_back(a_obj);
	}

protected:

	virtual void Event();
	virtual void Release();

	std::list<std::shared_ptr<BaseObject>> m_objList;
};