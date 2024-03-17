#include "pch.h"
#include "Key.h"

Key::Key(const std::string& name)
{
}

Key::~Key()
{
}

void Key::Init()
{
	animator.SetTarget(&sprite);
}

void Key::Release()
{
}

void Key::Reset()
{
	SetOrigin(Origins::KEY);
	animator.Play(keyIdle);
}

void Key::Update(float dt)
{
	SpriteGo::Update(dt);
	animator.Update(dt);
}
