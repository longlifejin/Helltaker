#pragma once
#include "SpriteGo.h"
class Box : public SpriteGo
{
public:
	enum class Types
	{
		Box1, Box2,	Box3, Box4, Box5, Box6, Box7, Box8, Box9, Box10, Box11,
	};

	static Box* SetBox(Types stoneType);

protected:
	Types type;

public:
	Box(const std::string& name = "");
	~Box();

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

};

