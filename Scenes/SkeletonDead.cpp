#include "pch.h"
#include "SkeletonDead.h"

SkeletonDead::SkeletonDead(const std::string& name)
	:SpriteGo(name)
{
}

SkeletonDead::~SkeletonDead()
{
}

void SkeletonDead::Init()
{
	SpriteGo::Init();
	animator.SetTarget(&sprite);
}

void SkeletonDead::Reset()
{
	SpriteGo::Reset();
	animator.Play("Tables/skeleton_Dead.csv");
	animator.AddEvent("Tables/skeleton_Dead.csv", 9, std::bind(&SkeletonDead::OnDestroy,this));

	SetOrigin(Origins::MC);
}

void SkeletonDead::Update(float dt)
{
	SpriteGo::Update(dt);
	animator.Update(dt);
}

void SkeletonDead::OnDestroy()
{
	SCENE_MGR.GetCurrentScene()->RemoveGo(this); //마지막프레임에 호출
}