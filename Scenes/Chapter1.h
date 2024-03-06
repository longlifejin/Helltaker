#pragma once
#include "Scene.h"
#include "SpriteGo.h"

class Player;
class Stone;

class Chapter1 : public Scene
{

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
	SpriteGo* background;
	Player* player;
	Stone* box;

	std::vector<sf::VertexArray> grid;
	sf::VertexArray gridHorizontal;

	std::vector<MapObject> map;

public:
	Chapter1(SceneIds id);
	virtual ~Chapter1();

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

};

