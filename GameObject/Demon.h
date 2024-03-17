#pragma once
#include "SpriteGo.h"
#include "Animator.h"

class Chapter;

class Demon :  public SpriteGo
{
protected:
	std::string demonIdle = "Tables/pand_Idle.csv";

public:
	Demon(const std::string& name = "");
	~Demon();

	Chapter* chapter;
	Animator animator;

	void Init() override;
	void Release() override;

	void Reset() override;
	void SetdemonIdle(std::string Id);

	void Update(float dt) override;


};

