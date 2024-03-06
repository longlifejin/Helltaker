#pragma once
#include "SpriteGo.h"

class Player : public SpriteGo
{
protected:
	float speed = 300.f;
	sf::Vector2f direction = { 0.f, 0.f };
	int moveCount = 23; //é�͸��� �ٲ��ֱ�

public:
	Player(const std::string& name = "");
	~Player();

	void Init() override;
	void Release() override;

	void Reset() override;

	void Update(float dt) override;
	void FixedUpdate(float dt);
	void LateUpdate(float dt);

	void OnDamage(int damage); //������ֹ��� ������ 1�� �� ��� �ϱ�
	void OnDie(); //moveCount�� 0�̸� ȣ��, �״� �ִϸ��̼� ���, ���� �����


};

