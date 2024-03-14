#pragma once
#include "SpriteGo.h"
class ChangeScene : public SpriteGo
{
protected:
	Animator animator;

public:
	ChangeScene(const std::string& name = "");
	~ChangeScene() override;

	void Init() override;

	void RemoveChangeSceneImage();

	void Reset() override;
	void Update(float dt) override;
};

