#pragma once
#include "SpriteGo.h"
class Key : public SpriteGo
{
protected:
	std::string keyIdle = "Tables/key_idle.csv";
	Animator animator;

public:
	int currentIndex;
	int prevIndex;

	Key(const std::string& name = "");
	~Key();

	int GetCurrentIndex() { return currentIndex; }

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
};

