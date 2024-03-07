#include "pch.h"
#include "Demon.h"

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
}

void Demon::Release()
{
	SpriteGo::Release();
}

void Demon::Reset()
{
	SpriteGo::Reset();
}

void Demon::Update(float dt)
{
	SpriteGo::Update(dt);
}

void Demon::FixedUpdate(float dt)
{
	SpriteGo::FixedUpdate(dt);
}

void Demon::LateUpdate(float dt)
{
	SpriteGo::LateUpdate(dt);
}

void Demon::OnDie()
{
}
