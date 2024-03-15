#pragma once
#include "SpriteGo.h"
class TransitionDown : public SpriteGo
{
protected:
	Animator animator;

public:
	TransitionDown(const std::string& name = "");
	~TransitionDown() override;

	void Init() override;

	void RemoveChangeSceneImage();

	void Reset() override;
	void Update(float dt) override;
};

