#include "pch.h"
#include "Player.h"
#include "Chapter.h"
#include "Animator.h"
#include "CollectDemon.h"
#include "Transition.h"

Player::Player(const std::string& name)
	:SpriteGo(name)
{
}

Player::~Player()
{
}

void Player::Init()
{
	SetOrigin(Origins::SELF);
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
	SetOrigin(Origins::SELF);
	SetFlipX(false);
	std::function<void()> DeadEvent_SceneChange = std::bind(&Player::ChangeSceneEvent);
	animator.AddEvent("Tables/player_Die.csv", 17, DeadEvent_SceneChange);
	//std::function<void()> DeadEvent_transition = std::bind(&ChangeScene->ChangeSceneEvent);
}

void Player::Update(float dt)
{
	SpriteGo::Update(dt);
	animator.Update(dt);

	chapter = dynamic_cast<Chapter*>(SCENE_MGR.GetCurrentScene());
	SpriteGo::Update(dt);

	prevIndex = currentIndex;
	
	if (!chapter->IsPause())
	{
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
	}

	if (prevIndex != currentIndex)
	{
		Chapter::MapObject type = chapter->CheckInteraction(currentIndex, prevIndex);

		if (type == Chapter::MapObject::empty)
		{
			SetPosition(chapter->IndexToPos(currentIndex));
			animator.Play("Tables/player_Move.csv");
			animator.PlayQueue("Tables/player_Idle.csv");
		}
		else if (type == Chapter::MapObject::box || type == Chapter::MapObject::skeleton)
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

void Player::ChangeSceneEvent()
{
	SCENE_MGR.ChangeScene(SceneIds::CHAPTER1);
	//chapter->PlayTransition(); //어떻게해야 transition을 출력할 수 있을까~~~~
}

void Player::OnDamage()
{
	moveCount -= 1;
}

void Player::OnDie()
{
	chapter->SetUiActive(false);
	SetOrigin({360.f, 900.f});
	animator.Play("Tables/player_Die.csv");
	moveCount = 0;
	sortOrder = 3;
	chapter->ResortGo(this);
	chapter->backColor->sortOrder = 2;
	chapter->ResortGo(chapter->backColor);

}

void Player::GetDemon()
{
	SetOrigin(Origins::SELF);
	animator.Play("Tables/player_GetDemon.csv");

	//애니메이션 재생 후 다음 챕터 이동
}

