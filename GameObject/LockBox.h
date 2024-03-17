#pragma once
#include "SpriteGo.h"

class LockBox : public SpriteGo
{
protected:

public:
	int currentIndex;
	int prevIndex;

	LockBox(const std::string& name = "");
	~LockBox();

	int GetCurrentIndex() { return currentIndex; }

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
};

