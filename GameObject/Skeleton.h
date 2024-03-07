#pragma once
#include "SpriteGo.h"

class Chapter1;

class Skeleton : public SpriteGo
{
protected:

public:
	int currentIndex;
	int prevIndex;

	Skeleton(const std::string& name = "");
	~Skeleton();

	Chapter1* chapter;

	int GetCurrentIndex() { return currentIndex; }

	void Init() override;
	void Release() override;

	void Reset() override;

	void Update(float dt) override;

	void OnDie();
};

