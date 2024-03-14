#include "pch.h"
#include "ChangeScene.h"

ChangeScene::ChangeScene(const std::string& name)
	:SpriteGo(name)
{
}

ChangeScene::~ChangeScene()
{
}

void ChangeScene::Init()
{
	SpriteGo::Init();
	animator.SetTarget(&sprite);
	SetOrigin(Origins::BC);
}

void ChangeScene::RemoveChangeSceneImage()
{
	SCENE_MGR.GetCurrentScene()->RemoveGo(this);
}

void ChangeScene::SceneChange()
{
	SCENE_MGR.ChangeScene(SceneIds::CHAPTER1);
}

void ChangeScene::Reset()
{
	animator.ClearEvent();

	//SpriteGo::Reset();
	SetPosition({1920.f * 0.5f, 1080.f});

	animator.SetOrigin(Origins::BC);
	std::function<void()> goChapter = std::bind(&ChangeScene::SceneChange);
	animator.AddEvent("Tables/sceneChange.csv", 28, std::bind(&ChangeScene::RemoveChangeSceneImage, this)); //이미지 지워주는거
	animator.AddEvent("Tables/sceneChange.csv", 28, goChapter); //씬 이동하는거

	animator.Play("Tables/sceneChange.csv");
}

void ChangeScene::Update(float dt)
{
	SpriteGo::Update(dt);
	animator.Update(dt);
}