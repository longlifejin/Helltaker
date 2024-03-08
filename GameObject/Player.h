#pragma once
#include "SpriteGo.h"

class Chapter1;

class Player : public SpriteGo
{
protected:

public:
	Player(const std::string& name = "");
	~Player();

	int moveCount = 23; //é�͸��� �ٲ��ֱ�
	int currentIndex = 49;
	int prevIndex;

	Chapter1* chapter;

	void Init() override;
	void Release() override;

	void Reset() override;

	void Update(float dt) override;

	void OnDamage(); //������ֹ��� ������ 1�� �� ��� �ϱ�
	void OnDie(); //moveCount�� 0�̸� ȣ��, �״� �ִϸ��̼� ���, ���� �����


};

