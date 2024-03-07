#pragma once
#include "SpriteGo.h"

class Chapter1;

class Player : public SpriteGo
{
protected:
	int moveCount = 23; //챕터마다 바꿔주기

public:
	Player(const std::string& name = "");
	~Player();

	int currentIndex = 49;
	int prevIndex;

	Chapter1* chapter;

	void Init() override;
	void Release() override;

	void Reset() override;

	void Update(float dt) override;
	void FixedUpdate(float dt);
	void LateUpdate(float dt);

	void OnDamage(int damage); //가시장애물에 닿으면 1씩 더 닳게 하기
	void OnDie(); //moveCount가 0이면 호출, 죽는 애니메이션 재생, 게임 재시작


};

