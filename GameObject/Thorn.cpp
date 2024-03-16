#include "pch.h"
#include "Thorn.h"

Thorn::Thorn(const std::string& name)
	: SpriteGo(name)
{
}

Thorn::~Thorn()
{
}

void Thorn::Init()
{
	SpriteGo::Init();
}

void Thorn::Release()
{
	SpriteGo::Release();
}

void Thorn::Reset()
{
	SpriteGo::Reset();
}

void Thorn::Update(float dt)
{
	SpriteGo::Update(dt);
}

