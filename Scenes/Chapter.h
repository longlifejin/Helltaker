#pragma once
#include "Scene.h"
#include "SpriteGo.h"
#include "TextGo.h"

class Player;
class Box;
class Demon;
class Skeleton;
class CollectDemon;
class Pause;
class SkeletonDead;

class Chapter : public Scene
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

	Pause* pause = nullptr;
	CollectDemon* collectDemon = nullptr;

	bool isPause = false;

	std::wstring adviceText = L"�� �λ� ���� [L] ��";
	std::wstring restartText = L"�� ����� [R] ��";

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
	Chapter(SceneIds id);
	virtual ~Chapter();

	SpriteGo* backColor;
	Demon* demon = nullptr;
	Skeleton* skeleton = nullptr;
	Box* box = nullptr; 

	bool isDemonGet = false;

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void SetGrid(); 
	void SetMap();
	void SetUiActive(bool active);
	void PlayTransition();

	MapObject CheckInteraction(int curr, int prev); //�ε��� ��ȣ�� �޾Ƽ� ������Ʈ ��ȣ�ۿ� �۵�
	int GetCurrentCol() { return col; }
	int GetCurrentRow() { return row; }
	sf::Vector2f GetPlayerCurrentPos();

	bool IsPause() { return isPause; }
	void SetPause(bool active) { isPause = active; }

	int PosToIndex(sf::Vector2f pos);
	sf::Vector2f IndexToPos(int index);

	void SetObject(int index, MapObject obj);

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

};
