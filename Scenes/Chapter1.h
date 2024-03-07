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
		wall,
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

	SpriteGo* background;
	Player* player;
	Stone* stone;

	sf::VertexArray grid;

	std::vector<MapObject> mapObj;

public:
	int currentIndex;
	int prevIndex;

	Chapter1(SceneIds id);
	virtual ~Chapter1();

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void SetGrid(); 
	bool checkCollision(int index); //인덱스 번호를 받아서 충돌체크
	int GetCurrentIndex() { return currentIndex; }
	int GetCurrentCol() { return col; }
	int GetCurrentRow() { return row; }

	int PosToIndex(sf::Vector2f pos);
	sf::Vector2f IndexToPos(int index);


	void SetObject(int index, MapObject obj);

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

};

