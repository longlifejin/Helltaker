#include "pch.h"
#include "Player.h"
#include "Chapter1.h"

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

	chapter = dynamic_cast<Chapter1*>(SCENE_MGR.GetCurrentScene());

	if (InputMgr::GetKeyDown(sf::Keyboard::W)) //╩С
	{
		chapter->prevIndex = chapter->currentIndex;
		chapter->currentIndex -= chapter->GetCurrentCol();
		if (chapter->checkCollision(chapter->currentIndex))
		{
			SetPosition(chapter->IndexToPos(chapter->currentIndex));
		}
		else
		{
			chapter->currentIndex = chapter->prevIndex;
		}
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::S)) //го
	{
		chapter->prevIndex = chapter->currentIndex;
		chapter->currentIndex += chapter->GetCurrentCol();
		if(chapter->checkCollision(chapter->currentIndex))
		{
			SetPosition(chapter->IndexToPos(chapter->currentIndex));
		}
		else
		{
			chapter->currentIndex = chapter->prevIndex;
		}
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::A)) //аб
	{
		chapter->prevIndex = chapter->currentIndex;
		SetFlipX(true);
		chapter->currentIndex -= 1;
		if (chapter->checkCollision(chapter->currentIndex))
		{
			SetPosition(chapter->IndexToPos(chapter->currentIndex));
		}
		else
		{
			chapter->currentIndex = chapter->prevIndex;
		}
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::D)) //©Л
	{
		chapter->prevIndex = chapter->currentIndex;
		SetFlipX(false);
		chapter->currentIndex += 1;
		if (chapter->checkCollision(chapter->currentIndex))
		{
			SetPosition(chapter->IndexToPos(chapter->currentIndex));
		}
		else
		{
			chapter->currentIndex = chapter->prevIndex;
		}
	}

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

