#pragma once
#include "Singleton.h"

class Scene;

class SceneMgr : public Singleton<SceneMgr>
{
	friend class Singleton <SceneMgr>;
protected:
	std::vector<Scene*> scenes;

	SceneIds startScene = SceneIds::COLLECT;
	SceneIds currentScene = startScene;

	SceneMgr() = default;
	virtual ~SceneMgr();

public:

	void Init();
	void Release();
	//내가 원하는 타이밍에 할당과 해제를 하려고 만들어준다.

	void ChangeScene(SceneIds id);

	Scene* GetCurrentScene() { return scenes[(int)currentScene]; }

	void Update(float dt);
	void LateUpdate(float dt);
	void FixedUpdate(float dt);
	void Draw(sf::RenderWindow& window);


	SceneMgr(const SceneMgr&) = delete;
	SceneMgr(SceneMgr&&) = delete;
	SceneMgr& operator=(const SceneMgr&) = delete;
	SceneMgr& operator=(SceneMgr&&) = delete;

};
#define SCENE_MGR (SceneMgr::Instance())