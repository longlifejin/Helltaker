#pragma once
#include "SpriteGo.h"
#include "Animator.h"

class Chapter1;

class Demon :  public SpriteGo
{
protected:
	std::string demonIdle = "Tables/pand_Idle.csv"; //챕터바뀌면 setstring해서 애니메이션 바꾸도록 수정하기

public:
	Demon(const std::string& name = "");
	~Demon();

	Chapter1* chapter;
	Animator animator;

	void Init() override;
	void Release() override;

	void Reset() override;

	void Update(float dt) override;


};

