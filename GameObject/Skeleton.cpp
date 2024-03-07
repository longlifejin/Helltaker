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
}

void Skeleton::Release()
{
	SpriteGo::Release();

}

void Skeleton::Reset()
{
	SpriteGo::Reset();

}

void Skeleton::Update(float dt)
{
	SpriteGo::Update(dt);

}

void Skeleton::OnDie()
{
}
