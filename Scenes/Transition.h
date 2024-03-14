#pragma once
#include "SpriteGo.h"
class Transition : public SpriteGo
{
protected:
	Animator animator;

public:
	Transition(const std::string& name = "");
	~Transition() override;

	void Init() override;

	void RemoveChangeSceneImage();
	static void SceneChange();

	void Reset() override;
	void Update(float dt) override;
};

