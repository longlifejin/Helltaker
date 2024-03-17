#include "pch.h"
#include "SceneMgr.h"
#include "TitleScene.h"
#include "Chapter.h"
#include "CollectDemon.h"

SceneMgr::~SceneMgr()
{
	Release();
}

void SceneMgr::Init()
{
	Release();

	scenes.push_back(new TitleScene(SceneIds::TITLESCENE));
	scenes.push_back(new Chapter(SceneIds::CHAPTER));

	for (auto scene : scenes)
	{
		scene->Init();
	}

	currentScene = startScene;
	scenes[(int)currentScene]->Enter();
}

void SceneMgr::Release()
{
	for (auto scene : scenes)
	{
		scene->Release();
		delete scene;
	}
	scenes.clear();
}

void SceneMgr::ChangeScene(SceneIds id)
{
	prevScene = currentScene;
	nextScene = id;
}

bool SceneMgr::Update(float dt)
{
	scenes[(int)currentScene]->Update(dt);

	if (nextScene != SceneIds::NONE)
	{
		scenes[(int)currentScene]->Exit();
		currentScene = nextScene;
		scenes[(int)currentScene]->Enter();

		nextScene = SceneIds::NONE;
		return false;
	}
	return true;
}

void SceneMgr::LateUpdate(float dt)
{
	scenes[(int)currentScene]->LateUpdate(dt);
}

void SceneMgr::FixedUpdate(float dt)
{
	scenes[(int)currentScene]->FixedUpdate(dt);
}

void SceneMgr::Draw(sf::RenderWindow& window)
{
	scenes[(int)currentScene]->Draw(window);
}