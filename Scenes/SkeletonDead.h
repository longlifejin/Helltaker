#pragma once
#include "SpriteGo.h"
class SkeletonDead :  public SpriteGo
{
protected:
	Animator animator;

public:
	SkeletonDead(const std::string& name = "");
	~SkeletonDead() override;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;

	void OnDestroy();

};

