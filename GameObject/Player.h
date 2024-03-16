#pragma once
#include "SpriteGo.h"
#include "Animator.h"

class Chapter;
class Transition;


class Player : public SpriteGo
{
protected:

public:
	Player(const std::string& name = "");
	~Player();

	sf::Vector2f targetPosition; //이동하려는 위치

	//int moveCount = 23; //챕터마다 바꿔주기
	int currentIndex = 49;
	int prevIndex = currentIndex;

	float speed = 300.f;

	Chapter* chapter;
	Transition* transition;
	Animator animator;

	void Init() override;
	void Release() override;

	void Reset() override;
	void ChangeSceneEvent();
	void ChapterUp();
	void Update(float dt) override; 
	
	sf::Vector2f lerp(const sf::Vector2f& start, const sf::Vector2f& end, float t) {
		return start + t * (end - start);
	}

	void GetDemon(); //getdemon 애니메이션 재생용
	void OnDamage(); //가시장애물에 닿으면 1씩 더 닳게 하기
	void OnDie(); //moveCount가 0이면 호출, 죽는 애니메이션 재생, 게임 재시작
};

