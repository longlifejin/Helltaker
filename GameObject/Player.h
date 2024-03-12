#pragma once
#include "SpriteGo.h"
#include "Animator.h"

class Chapter1;

class Player : public SpriteGo
{
public:
	struct ClipInfo //좌,우,위,아래 총 4개
	{
		std::string idle;
		std::string move;
		bool flipX = false;
		sf::Vector2f point; //기준점

		ClipInfo()
		{
		}

		ClipInfo(const std::string& idle, const std::string& move, bool flipX, sf::Vector2f point)
			:idle(idle), move(move), flipX(flipX), point(point)
		{
		}
	};

protected:
	std::vector<ClipInfo> clipInfos;
	ClipInfo currentClipInfo;

public:
	Player(const std::string& name = "");
	~Player();

	int moveCount = 23; //챕터마다 바꿔주기
	int currentIndex = 49;
	int prevIndex = currentIndex;

	float speed = 300.f;

	Chapter1* chapter;
	Animator animator;

	void Init() override;
	void Release() override;

	void Reset() override;

	void Update(float dt) override;

	void OnDamage(); //가시장애물에 닿으면 1씩 더 닳게 하기
	void OnDie(); //moveCount가 0이면 호출, 죽는 애니메이션 재생, 게임 재시작


};

