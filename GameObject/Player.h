#pragma once
#include "SpriteGo.h"

class Chapter1;

class Player : public SpriteGo
{
protected:
	int moveCount = 23; //é�͸��� �ٲ��ֱ�

public:
	Player(const std::string& name = "");
	~Player();

	int currentIndex;
	int prevIndex;

	Chapter1* chapter;

	void Init() override;
	void Release() override;

	void Reset() override;

	void Update(float dt) override;
	void FixedUpdate(float dt);
	void LateUpdate(float dt);

	void OnDamage(int damage); //������ֹ��� ������ 1�� �� ��� �ϱ�
	void OnDie(); //moveCount�� 0�̸� ȣ��, �״� �ִϸ��̼� ���, ���� �����


};

