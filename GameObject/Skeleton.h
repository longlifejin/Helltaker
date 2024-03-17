#pragma once
#include "SpriteGo.h"

class Chapter;

class Skeleton : public SpriteGo
{
protected:

public:
	int currentIndex;
	int prevIndex;

	Skeleton(const std::string& name = "");
	~Skeleton();

	Chapter* chapter;
	Animator animator;

	int GetCurrentIndex() { return currentIndex; }

	void Init() override;
	void Release() override;

	void Reset() override;

	void Update(float dt) override;
};

