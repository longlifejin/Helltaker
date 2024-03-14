#include "pch.h"
#include "Transition.h"

Transition::Transition(const std::string& name)
	:SpriteGo(name)
{
}

Transition::~Transition()
{
}

void Transition::Init()
{
	SpriteGo::Init();
	animator.SetTarget(&sprite);
	SetOrigin(Origins::BC);
}

void Transition::RemoveChangeSceneImage()
{
	SCENE_MGR.GetCurrentScene()->RemoveGo(this);
}

void Transition::SceneChange()
{
	SCENE_MGR.ChangeScene(SceneIds::CHAPTER);
}

void Transition::Reset()
{
	animator.ClearEvent();

	//SpriteGo::Reset();
	SetPosition({1920.f * 0.5f, 1080.f});

	animator.SetOrigin(Origins::BC);
	std::function<void()> goChapter = std::bind(&Transition::SceneChange);
	animator.AddEvent("Tables/sceneChange.csv", 28, std::bind(&Transition::RemoveChangeSceneImage, this)); //이미지 지워주는거
	animator.AddEvent("Tables/sceneChange.csv", 28, goChapter); //씬 이동하는거

	animator.Play("Tables/sceneChange.csv");
}

void Transition::Update(float dt)
{
	SpriteGo::Update(dt);
	animator.Update(dt);
}