#include "pch.h"
#include "Player.h"
#include "Chapter1.h"
#include "Animator.h"
#include "CollectDemon.h"

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

	animator.SetTarget(&sprite);

}

void Player::Release()
{
	SpriteGo::Release();
}

void Player::Reset()
{
	SpriteGo::Reset();
	animator.Play("Tables/player_Idle.csv");
	SetOrigin(Origins::BC);
	SetFlipX(false);

}

void Player::Update(float dt)
{
	SpriteGo::Update(dt);
	animator.Update(dt);
	
	chapter = dynamic_cast<Chapter1*>(SCENE_MGR.GetCurrentScene());
	
	prevIndex = currentIndex;

	if (InputMgr::GetKeyDown(sf::Keyboard::W))
	{
		currentIndex -= chapter->GetCurrentCol();
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::S))
	{
		currentIndex += chapter->GetCurrentCol();
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::A))
	{
		currentIndex -= 1;
		this->SetFlipX(true);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::D))
	{
		currentIndex += 1;
		this->SetFlipX(false);
	}

	if (prevIndex != currentIndex)
	{
		Chapter1::MapObject type = chapter->CheckInteraction(currentIndex, prevIndex);

		if (type == Chapter1::MapObject::empty)
		{
			SetPosition(chapter->IndexToPos(currentIndex));
			animator.Play("Tables/player_Move.csv");
			animator.PlayQueue("Tables/player_Idle.csv");
			
		}
		else if (type == Chapter1::MapObject::box || type == Chapter1::MapObject::skeleton)
		{
			currentIndex = prevIndex;
			SetPosition(chapter->IndexToPos(currentIndex));
			animator.Play("Tables/player_Kick.csv");
			animator.PlayQueue("Tables/player_Idle.csv");
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

