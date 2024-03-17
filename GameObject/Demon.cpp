#include "pch.h"
#include "Demon.h"
#include "Animator.h"
#include "Chapter.h"

Demon::Demon(const std::string& name)
	: SpriteGo(name)
{
}

Demon::~Demon()
{
}

void Demon::Init()
{
	chapter = dynamic_cast<Chapter*>(SCENE_MGR.GetCurrentScene());
	SpriteGo::Init();
	animator.SetTarget(&sprite);
}

void Demon::Release()
{
	SpriteGo::Release();
}

void Demon::Reset()
{
	SpriteGo::Reset();
	switch (chapter->GetCurrentStage())
	{
	case 1:
		demonIdle = "Tables/pand_Idle.csv";
		break;
	case 2:
		demonIdle = "Tables/mode_Idle.csv";
		break;
	case 3:
		demonIdle = "Tables/cerb_Idle.csv";
		break;
	case 4:
		demonIdle = "Tables/mali_Idle.csv";
		break;
	case 5:
		demonIdle = "Tables/zdra_Idle.csv";
		break;
	case 6:
		demonIdle = "Tables/azaz_Idle.csv";
		break;
	case 7:
		demonIdle = "Tables/just_Idle.csv";
		break;
	default:
		demonIdle = "Tables/mode_Idle.csv";
		break;
	}
	animator.Play(demonIdle);
	SetOrigin(Origins::SELF);
}

void Demon::SetdemonIdle(std::string Id)
{
	demonIdle = Id;
}

void Demon::Update(float dt)
{
	SpriteGo::Update(dt);
	animator.Update(dt);
}
