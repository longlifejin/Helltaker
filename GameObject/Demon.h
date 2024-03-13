#pragma once
#include "SpriteGo.h"
#include "Animator.h"

class Chapter1;

class Demon :  public SpriteGo
{
protected:
	std::string demonIdle = "Tables/pand_Idle.csv"; //é�͹ٲ�� setstring�ؼ� �ִϸ��̼� �ٲٵ��� �����ϱ�

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

