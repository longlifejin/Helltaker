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
	//std::function<void()> DeadEvent_transition = std::bind(&ChangeScene->ChangeSceneEvent);
	animator.AddEvent("Tables/player_Die.csv", 17, DeadEvent_SceneChange);
}

void Player::Update(float dt)
{
	SpriteGo::Update(dt);
	animator.Update(dt);

	chapter = dynamic_cast<Chapter1*>(SCENE_MGR.GetCurrentScene());
	SpriteGo::Update(dt);

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

void Player::ChangeSceneEvent()
{
	SCENE_MGR.ChangeScene(SceneIds::CHAPTER1);
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

