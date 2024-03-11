#pragma once
#include "Scene.h"
#include "SpriteGo.h"
#include "TextGo.h"

class Player;
class Box;
class Demon;
class Skeleton;

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
		box,
		key,
		lockbox,
	};

protected:
	int col = 19;
	int row = 10;
	float size = 100.f;

	float offsetX = 10.f;
	float offsetY = 40.f;

	SpriteGo* background = nullptr;

	SpriteGo* uiRoseLeft = nullptr;
	SpriteGo* uiRoseRight = nullptr;

	SpriteGo* uiDemonLeft = nullptr;
	SpriteGo* uiDemonRight = nullptr;

	TextGo* moveCount = nullptr;
	SpriteGo* currentStage = nullptr;

	TextGo* advice = nullptr;
	TextGo* restart = nullptr;

	Player* player = nullptr;
	Demon* demon = nullptr;
	Skeleton* skeleton = nullptr;
	Box* box = nullptr;


	std::wstring adviceText = L"● 인생 조언 [L] ●";
	std::wstring restartText = L"● 재시작 [R] ●";

	std::list<Skeleton*> skeletonList;
	std::list<Box*> boxList;
	std::list<Skeleton*> deadSkeletonList;

	sf::VertexArray grid;

	std::vector<MapObject> mapObj;
	std::vector<std::string> mapLayout =
	{
		"WWWWWWWWWWWWWWWWWWW",
		"WWWWWWWWWWWWWWWWWWW",
		"WWWWWWWWWWEPWWWWWWW",
		"WWWWWWWEESEEWWWWWWW",
		"WWWWWWWESESWWWWWWWW",
		"WWWWWWEEWWWWWWWWWWW",
		"WWWWWWEBEEBEWWWWWWW",
		"WWWWWWEBEBEEDWWWWWW",
		"WWWWWWWWWWWWWWWWWWW",
		"WWWWWWWWWWWWWWWWWWW",
	};

public:
	Chapter1(SceneIds id);
	virtual ~Chapter1();

	bool isDemonGet = false;

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void SetGrid(); 

	void SetMap();

	bool CheckInteraction(int index, sf::Keyboard::Key key); //인덱스 번호를 받아서 오브젝트 상호작용 작동
	int GetCurrentCol() { return col; }
	int GetCurrentRow() { return row; }

	bool skullInteraction();

	int PosToIndex(sf::Vector2f pos);
	sf::Vector2f IndexToPos(int index);

	void SetObject(int index, MapObject obj);

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

};

