#pragma once
#include "SpriteGo.h"
#include "Animator.h"

class Chapter1;

class Player : public SpriteGo
{
public:
	struct ClipInfo //��,��,��,�Ʒ� �� 4��
	{
		std::string idle;
		std::string move;
		bool flipX = false;
		sf::Vector2f point; //������

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

	int moveCount = 23; //é�͸��� �ٲ��ֱ�
	int currentIndex = 49;
	int prevIndex = currentIndex;

	float speed = 300.f;

	Chapter1* chapter;
	Animator animator;

	void Init() override;
	void Release() override;

	void Reset() override;

	void Update(float dt) override;

	void OnDamage(); //������ֹ��� ������ 1�� �� ��� �ϱ�
	void OnDie(); //moveCount�� 0�̸� ȣ��, �״� �ִϸ��̼� ���, ���� �����


};

