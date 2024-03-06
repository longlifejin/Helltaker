#pragma once
#include "GameObject.h"

class TileMap : public GameObject
{
public:


protected:
	

public:
	TileMap(const std::string& name = "");
	~TileMap();

	void SetTile(sf::Vector2f count, sf::Vector2f size);
	void SetTile(int col, int row, sf::Vector2f size);

	void Init() override;
	void Release() override;

	void Reset() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;


};

