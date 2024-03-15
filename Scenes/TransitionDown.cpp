#include "pch.h"
#include "TransitionDown.h"
#include "Transition.h"

TransitionDown::TransitionDown(const std::string& name)
	:SpriteGo(name)
{
}

TransitionDown::~TransitionDown()
{
}

void TransitionDown::Init()
{
	SpriteGo::Init();
	SetOrigin(Origins::BC);
	animator.SetTarget(&sprite);
}

void TransitionDown::RemoveChangeSceneImage()
{
	SCENE_MGR.GetCurrentScene()->RemoveGo(this);
}

void TransitionDown::Reset()
{
	animator.ClearEvent();

	SetPosition({ 1920.f * 0.5f, 1080.f });

	animator.SetOrigin(Origins::BC);
	//animator.AddEvent("Tables/transition_Down.csv", 16, std::bind(&TransitionDown::RemoveChangeSceneImage, this));
	animator.Play("Tables/transition_Down.csv");
}

void TransitionDown::Update(float dt)
{
	SpriteGo::Update(dt);
	animator.Update(dt);
}