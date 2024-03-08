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
			moveCount -= 1;
		}
		else
		{
			currentIndex = prevIndex;
			moveCount -= 1;
		}
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::S)) //го
	{
		prevIndex = currentIndex;
		currentIndex += chapter->GetCurrentCol();
		if(chapter->CheckInteraction(currentIndex, sf::Keyboard::S))
		{
			SetPosition(chapter->IndexToPos(currentIndex));
			moveCount -= 1;
		}
		else
		{
			currentIndex = prevIndex;
			moveCount -= 1;
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
			moveCount -= 1;
		}
		else
		{
			currentIndex = prevIndex;
			moveCount -= 1;
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
			moveCount -= 1;
		}
		else
		{
			currentIndex = prevIndex;
			moveCount -= 1;
		}
	}

	if (moveCount == 0)
	{
		OnDie();
	}

}

void Player::OnDamage()
{
	moveCount -= 1;
}

void Player::OnDie()
{
	std::cout << "Game Over" << std::endl;
}

