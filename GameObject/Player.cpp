#include "pch.h"
#include "Player.h"

Player::Player(const std::string& name)
	:SpriteGo(name)
{
}

Player::~Player()
{
}

void Player::Init()
{
	SpriteGo::Init();
	//SetTexture("PlusSprite/whiteCircle.png");
	//SetOrigin(Origins::TL);
}

void Player::Release()
{
	SpriteGo::Release();
}

void Player::Reset()
{
	SpriteGo::Reset();
}

void Player::Update(float dt)
{
	SpriteGo::Update(dt);

}

void Player::FixedUpdate(float dt)
{
	SpriteGo::FixedUpdate(dt);

}

void Player::LateUpdate(float dt)
{
	SpriteGo::LateUpdate(dt);

}

void Player::OnDamage(int damage)
{
	

}

void Player::OnDie()
{
	

}

