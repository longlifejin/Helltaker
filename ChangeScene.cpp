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

void ChangeScene::Reset()
{
	SpriteGo::Reset();
	SetPosition({1920.f * 0.5f, 1080.f});

	animator.SetOrigin(Origins::BC);
	animator.Play("tables/sceneChange.csv");
	animator.AddEvent("Tables/sceneChange.csv", 28, std::bind(&ChangeScene::RemoveChangeSceneImage, this));
}

void ChangeScene::Update(float dt)
{
	SpriteGo::Update(dt);
	animator.Update(dt);



}

