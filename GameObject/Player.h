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

	sf::Vector2f targetPosition; //�̵��Ϸ��� ��ġ

	//int moveCount = 23; //é�͸��� �ٲ��ֱ�
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

	void GetDemon(); //getdemon �ִϸ��̼� �����
	void OnDamage(); //������ֹ��� ������ 1�� �� ��� �ϱ�
	void OnDie(); //moveCount�� 0�̸� ȣ��, �״� �ִϸ��̼� ���, ���� �����
};

