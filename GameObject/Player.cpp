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
	SetOrigin(Origins::BC);
	moveCount = 23;
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

	if (InputMgr::GetKeyDown(sf::Keyboard::W)) //상
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
	if (InputMgr::GetKeyDown(sf::Keyboard::S)) //하
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
	if (InputMgr::GetKeyDown(sf::Keyboard::A)) //좌
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
	if (InputMgr::GetKeyDown(sf::Keyboard::D)) //우
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
	//죽는 애니메이션 재생 후 자동 재시작
}

