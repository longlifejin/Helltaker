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
	SetOrigin(Origins::BC);
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
		prevIndex = currentIndex;
		currentIndex -= chapter->GetCurrentCol();
		if (chapter->CheckInteraction(currentIndex, sf::Keyboard::W))
		{
			SetPosition(chapter->IndexToPos(currentIndex));
		}
		else
		{
			currentIndex = prevIndex;
		}
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::S)) //го
	{
		prevIndex = currentIndex;
		currentIndex += chapter->GetCurrentCol();
		if(chapter->CheckInteraction(currentIndex, sf::Keyboard::S))
		{
			SetPosition(chapter->IndexToPos(currentIndex));
		}
		else
		{
			currentIndex = prevIndex;
		}
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::A)) //аб
	{
		prevIndex = currentIndex;
		SetFlipX(true);
		currentIndex -= 1;
		if (chapter->CheckInteraction(currentIndex, sf::Keyboard::A))
		{
			SetPosition(chapter->IndexToPos(currentIndex));
		}
		else
		{
			currentIndex = prevIndex;
		}
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::D)) //©Л
	{
		prevIndex = currentIndex;
		SetFlipX(false);
		currentIndex += 1;
		if (chapter->CheckInteraction(currentIndex, sf::Keyboard::D))
		{
			SetPosition(chapter->IndexToPos(currentIndex));
		}
		else
		{
			currentIndex = prevIndex;
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

