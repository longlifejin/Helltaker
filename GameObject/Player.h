#pragma once
#include "SpriteGo.h"

class Player : public SpriteGo
{
protected:
	float speed = 300.f;
	sf::Vector2f direction = { 0.f, 0.f };
	int moveCount = 23; //챕터마다 바꿔주기

public:
	Player(const std::string& name = "");
	~Player();

	void Init() override;
	void Release() override;

	void Reset() override;

	void Update(float dt) override;
	void FixedUpdate(float dt);
	void LateUpdate(float dt);

	void OnDamage(int damage); //가시장애물에 닿으면 1씩 더 닳게 하기
	void OnDie(); //moveCount가 0이면 호출, 죽는 애니메이션 재생, 게임 재시작


};

