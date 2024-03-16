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
class Advice;
class SkeletonDead;
class Transition;
class TransitionDown;


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
		throne,
	};

protected:

	int stage = 1;

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
	Advice* adviceTab = nullptr;
	CollectDemon* collectDemon = nullptr;

	bool isPause = false;
	bool isAdvice = false;

	float timer = 0.f;
	float transitionTime = 1.f;

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
	Chapter(SceneIds id);
	virtual ~Chapter();

	SpriteGo* backColor;
	Demon* demon = nullptr;
	Skeleton* skeleton = nullptr;
	Box* box = nullptr; 

	Animator animator;
	Transition* transition;

	sf::Sprite dustSprite;
	Animator dustAnimator;

	sf::Sprite kickSprite;
	Animator kickAnimator;

	bool isDemonGet = false;

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	int GetCurrentStage() const { return stage; }
	void SetCurrentStage(int stageNumber) { stage = stageNumber; } //챕터 2,3 만들 때 사용할 함수

	void SetGrid(); 
	void SetMap();
	void SetUiActive(bool active);

	MapObject CheckInteraction(int curr, int prev); //인덱스 번호를 받아서 오브젝트 상호작용 작동
	int GetCurrentCol() { return col; }
	int GetCurrentRow() { return row; }
	sf::Vector2f GetPlayerCurrentPos();

	bool IsPause() { return isPause; }
	void SetPause(bool active) { isPause = active; }

	bool IsAdvice() { return isAdvice; }
	void SetAdvice(bool active) { isAdvice = active; }

	int PosToIndex(sf::Vector2f pos);
	sf::Vector2f IndexToPos(int index);

	void SetObject(int index, MapObject obj);

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

};

