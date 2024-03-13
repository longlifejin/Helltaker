#include "pch.h"
#include "Demon.h"
#include "Animator.h"

Demon::Demon(const std::string& name)
	: SpriteGo(name)
{
}

Demon::~Demon()
{
}

void Demon::Init()
{
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
	animator.Play(demonIdle);
	SetOrigin(Origins::MC);
}

void Demon::Update(float dt)
{
	SpriteGo::Update(dt);
	animator.Update(dt);
}
