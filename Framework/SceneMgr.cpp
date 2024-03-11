#include "pch.h"
#include "SceneMgr.h"
#include "TitleScene.h"
#include "SceneDev1.h"
#include "Chapter1.h"
#include "CollectDemon.h"

SceneMgr::~SceneMgr()
{
	Release();
}

void SceneMgr::Init()
{
	Release();

	scenes.push_back(new TitleScene(SceneIds::TITLESCENE));
	scenes.push_back(new Chapter1(SceneIds::CHAPTER1));
	scenes.push_back(new CollectDemon(SceneIds::COLLECT));
	scenes.push_back(new SceneDev1(SceneIds::SCENEDVE1));

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
	//바꿀 씬을 저장해뒀다가 전 씬이 업데이트를 마치고 바꿀 수 있도록 수정


	scenes[(int)currentScene]->Exit();
	currentScene = id;
	scenes[(int)currentScene]->Enter();
}

void SceneMgr::Update(float dt)
{
	scenes[(int)currentScene]->Update(dt);
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