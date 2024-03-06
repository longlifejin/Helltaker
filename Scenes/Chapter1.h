#pragma once
#include "Scene.h"
#include "SpriteGo.h"

class Player;
class Stone;

class Chapter1 : public Scene
{
public:
	enum class MapObject
	{
		empty,
		player,
		demon,
		skeleton,
		stone,
		key,
		lockbox,
	};

protected:
	int col = 19;
	int row = 10;
	float size = 100.f;

	float offsetX = 10.f;
	float offsetY = 40.f;

	int currentIndex;
	
	SpriteGo* background;
	Player* player;
	Stone* stone;

	sf::VertexArray grid;

	std::vector<MapObject> mapObj;

public:
	Chapter1(SceneIds id);
	virtual ~Chapter1();

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void SetGrid();
	sf::Vector2f GetGridPos(int index);
	int GetCurrentIndex() { return currentIndex; }

	void SetObject();

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

};

