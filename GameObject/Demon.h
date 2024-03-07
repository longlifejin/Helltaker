#pragma once
#include "SpriteGo.h"

class Chapter1;

class Demon :  public SpriteGo
{
protected:


public:
	Demon(const std::string& name = "");
	~Demon();

	Chapter1* chapter;

	void Init() override;
	void Release() override;

	void Reset() override;

	void Update(float dt) override;
	void FixedUpdate(float dt);
	void LateUpdate(float dt);

	void OnDie();


};

