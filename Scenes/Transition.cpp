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
	SetOrigin(Origins::BC);
	animator.SetTarget(&sprite);
}

void Transition::RemoveChangeSceneImage()
{
	SCENE_MGR.GetCurrentScene()->RemoveGo(this); //생성할때마다 지워주는 구조니까 불필요한 것 같다. 이거 없애기
}

void Transition::SceneChange()
{
	SCENE_MGR.ChangeScene(scene); //TO-DO : 원하는 창으로 이동할 수 있도록 멤버 변수 두기
}

void Transition::PlayTransitionUp()
{
}

void Transition::Reset()
{
	animator.ClearEvent();

	SetPosition({1920.f * 0.5f, 1080.f});
	animator.SetOrigin(Origins::BC);
	//std::function<void()> goChapter = std::bind(&Transition::SceneChange);
	//animator.AddEvent("Tables/transition_Up.csv", 11, std::bind(&Transition::PlayTransitionDown, this));
	//animator.AddEvent("Tables/transition_Up.csv", 13, std::bind(&Transition::SceneChange, this)); //씬 이동하는거
	//animator.Play("Tables/transition_Up.csv");
}

void Transition::Update(float dt)
{
	SpriteGo::Update(dt);
	animator.Update(dt);
}