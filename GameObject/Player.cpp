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
	animator.SetTarget(&sprite);
}

void Player::Release()
{
	SpriteGo::Release();
}

void Player::Reset()
{
	animator.Play("Tables/player_Idle.csv");
	SetOrigin(Origins::SELF);
	SetFlipX(false);
	animator.AddEvent("Tables/player_Die.csv", 17, std::bind(&Player::ChangeSceneEvent, this));
	animator.AddEvent("Tables/player_GetDemon.csv", 12, std::bind(&Player::ControlTimeScaleSlowly, this));
	animator.AddEvent("Tables/player_GetDemon.csv", 13, std::bind(&Player::TimeScaleRestore, this));
	animator.AddEvent("Tables/player_GetDemon.csv", 23, std::bind(&Player::ChangeSceneEvent, this));
	animator.AddEvent("Tables/player_GetDemon.csv", 23, std::bind(&Player::ChapterUp, this));
	
}

void Player::Update(float dt)
{
	SpriteGo::Update(dt);
	animator.Update(dt);

	chapter = dynamic_cast<Chapter*>(SCENE_MGR.GetCurrentScene());
	SpriteGo::Update(dt);

	prevIndex = currentIndex;
	
	if (!chapter->IsPause() && !chapter->IsAdvice() && !chapter->collectDemon->GetActive())
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

		if (type == Chapter::MapObject::empty )
		{
			SetPosition(chapter->IndexToPos(currentIndex));
			SOUND_MGR.PlaySfx("AudioClip/character_move_01.wav");
			animator.Play("Tables/player_Move.csv");
			animator.PlayQueue("Tables/player_Idle.csv");

			chapter->dustSprite.setPosition(chapter->IndexToPos(prevIndex));
			chapter->dustAnimator.Play("Tables/player_moveDust.csv");
		}
		else if (type == Chapter::MapObject::thorn)
		{
			SetPosition(chapter->IndexToPos(currentIndex));
			SOUND_MGR.PlaySfx("AudioClip/spikes_damage_01.wav");
			animator.Play("Tables/player_Move.csv");
			animator.PlayQueue("Tables/player_Idle.csv");

			chapter->dustSprite.setPosition(chapter->IndexToPos(prevIndex));
			chapter->dustAnimator.Play("Tables/player_moveDust.csv");
		}
		else if (type == Chapter::MapObject::box )
		{
			currentIndex = prevIndex;
			SetPosition(chapter->IndexToPos(currentIndex));
			SOUND_MGR.PlaySfx("AudioClip/stone_kick_01.wav");
			animator.Play("Tables/player_Kick.csv");
			animator.PlayQueue("Tables/player_Idle.csv");
		}
		else if (type == Chapter::MapObject::skeleton)
		{
			currentIndex = prevIndex;
			SetPosition(chapter->IndexToPos(currentIndex));
			animator.Play("Tables/player_Kick.csv");
			animator.PlayQueue("Tables/player_Idle.csv");
		}
	}



	if (chapter->GetCurrentMoveCount() <= -1)
	{
		OnDie();
	}
}

void Player::ChangeSceneEvent()
{
	animator.Stop();
	chapter->transition->SetChangeScene(SceneIds::CHAPTER);
	chapter->transition->PlayTransitionUp();
}

void Player::OnDie()
{
	SOUND_MGR.PlaySfx("AudioClip/player_death_01.wav");
	chapter->SetUiActive(false);
	SetOrigin({360.f, 900.f});
	animator.Play("Tables/player_Die.csv");
	chapter->SetmoveCount(0);
	sortOrder = 3;
	chapter->ResortGo(this);
	chapter->backColor->sortOrder = 2;
	chapter->ResortGo(chapter->backColor);
}

void Player::ChapterUp() //GetDemon 애니메이션 재생 후 다음 챕터로 이동
{
	chapter->SetCurrentStage(chapter->GetCurrentStage() + 1);
}

void Player::ControlTimeScaleSlowly()
{
	FRAMEWORK.SetTimeScale(0.2f);
}

void Player::TimeScaleRestore()
{
	FRAMEWORK.SetTimeScale(1.f);
}

void Player::GetDemon()
{
	SetOrigin(Origins::SELF);
	SOUND_MGR.PlaySfx("AudioClip/succub_capture_01.wav");
	animator.Play("Tables/player_GetDemon.csv");
}

