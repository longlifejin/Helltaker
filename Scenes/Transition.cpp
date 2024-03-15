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
	SCENE_MGR.GetCurrentScene()->RemoveGo(this); //�����Ҷ����� �����ִ� �����ϱ� ���ʿ��� �� ����. �̰� ���ֱ�
}

void Transition::SceneChange()
{
	SCENE_MGR.ChangeScene(scene); //TO-DO : ���ϴ� â���� �̵��� �� �ֵ��� ��� ���� �α�
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
	//animator.AddEvent("Tables/transition_Up.csv", 13, std::bind(&Transition::SceneChange, this)); //�� �̵��ϴ°�
	//animator.Play("Tables/transition_Up.csv");
}

void Transition::Update(float dt)
{
	SpriteGo::Update(dt);
	animator.Update(dt);
}