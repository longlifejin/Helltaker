#pragma once
#include "Scene.h"

class SpriteGo;
class TextGo;

struct Dialogue
{
	std::wstring text;
	std::vector<std::wstring> options; // 선택지
	std::vector<int> nextIndex; // 선택지에 따른 다음 대사의 인덱스
	bool haveOptions() const { return !options.empty(); }
};

class CollectDemon : public Scene
{
	enum class SelectLine
	{
		Correct,
		Wrong,
	};


	enum class Page //space누를때마다 대사 변경되게 하려고
	{
		FirstLine = 0,
		SelectWrong_1,
		SelectCorrect_1,

	};

protected:
	sf::RectangleShape backColor;

	SpriteGo* background;
	SpriteGo* demon;
	
	TextGo* demonName;
	TextGo* demonLine;
	TextGo* demonLine2;

	SpriteGo* wrongButton;
	SpriteGo* correctButton;

	TextGo* wrongText;
	TextGo* correctText;

	SpriteGo* booper;

	SpriteGo* success;
	SpriteGo* badEnd;

	std::wstring panName = L"● 지친 악마, 판데모니카 ●";
	std::wstring pandLine1 = L"지옥 고객 서비스 센터의 판데모니카입니다.";
	std::wstring pandLine2 = L"무엇을 도와드릴까요?"; //TO-DO : 가운데 정렬하는 방법 찾아보기 ㅠ
	
	std::wstring wrongLine = L"우리 집에 한번 오면 알게 될거야.";
	std::wstring correctLine = L"오히려 '그 쪽'을 도와줘야 할 판인데?";

	SelectLine currentSelect = SelectLine::Wrong;

	bool isSelectTime = false;


	int step = 0;

public:
	CollectDemon(SceneIds id);
	virtual ~CollectDemon();

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Update(float dt) override;

	void Select();

	void Draw(sf::RenderWindow& window) override;

};

