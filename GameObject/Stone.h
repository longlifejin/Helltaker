#pragma once
#include "SpriteGo.h"
class Stone : public SpriteGo
{
public:
	enum class Types
	{
		Box1, Box2,	Box3, Box4, Box5, Box6, Box7, Box8, Box9, Box10, Box11,
	};

	static Stone* SetStone(Types stoneType);

protected:
	Types type;

public:
	Stone(const std::string& name = "");
	~Stone();

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

};

