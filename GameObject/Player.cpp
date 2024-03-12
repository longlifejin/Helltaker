#include "pch.h"
#include "Player.h"
#include "Chapter1.h"
#include "Animator.h"

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

	clipInfos.push_back({ "Tables/player_Idle.csv", "animations/Move.csv", false, Utils::GetNormal({-1,-1}) });
	clipInfos.push_back({ "Tables/player_Idle.csv", "animations/Move.csv", true, Utils::GetNormal({-1,-1}) });
	clipInfos.push_back({ "Tables/player_Idle.csv", "animations/Move.csv", false, Utils::GetNormal({-1,-1}) });
	clipInfos.push_back({ "Tables/player_Idle.csv", "animations/Move.csv", true, Utils::GetNormal({-1,-1}) });
}

void Player::Release()
{
	SpriteGo::Release();
}

void Player::Reset()
{
	SpriteGo::Reset();
	animator->Play("Tables/player_Idle.csv");
	SetOrigin(Origins::BC);
	SetFlipX(false);

	currentClipInfo = clipInfos[6]; //???
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
		}
		else
		{
			currentIndex = prevIndex;
		}
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::S)) //하
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
	if (InputMgr::GetKeyDown(sf::Keyboard::A)) //좌
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
	if (InputMgr::GetKeyDown(sf::Keyboard::D)) //우
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

	if (moveCount == -1)
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
	
	moveCount = 0;
	//죽는 애니메이션 재생 후 자동 재시작
}

