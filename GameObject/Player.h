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
	void ControlTimeScaleSlowly();
	void TimeScaleRestore();
	
	void Update(float dt) override; 
	
	void GetDemon();
	void OnDie();
};

