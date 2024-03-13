#include "pch.h"
#include "Skeleton.h"

Skeleton::Skeleton(const std::string& name)
	:SpriteGo(name)
{
}

Skeleton::~Skeleton()
{
}

void Skeleton::Init()
{
	SpriteGo::Init();
	animator.SetTarget(&sprite);
}

void Skeleton::Release()
{
	SpriteGo::Release();

}

void Skeleton::Reset()
{
	SpriteGo::Reset();
	animator.Play("Tables/skeleton_Idle.csv");
	SetOrigin(Origins::BC);

}

void Skeleton::Update(float dt)
{
	SpriteGo::Update(dt);
	animator.Update(dt);

}

void Skeleton::OnDie()
{
	this->SetActive(false);

}
