#pragma once
#include "SpriteGo.h"

class Chapter;

class Thorn : public SpriteGo
{
protected:

public:
	Thorn(const std::string& name = "");
	~Thorn();

	int currentIndex;
	int prevIndex;

	Chapter* chapter;
	Animator animator;

	void Init() override;
	void Release() override;

	int GetCurrentIndex() { return currentIndex; }
	void Reset() override;

	void Update(float dt) override;


};

