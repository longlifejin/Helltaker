#pragma once
#include "Scene.h"
#include "SpriteGo.h"
#include "TextGo.h"

class Chapter;

class CollectDemon : public GameObject
{
	enum class SelectLine
	{
		Correct,
		Wrong,
	};

protected:
	sf::Font& fontEB = RES_MGR_FONT.Get("Font/NanumSquareEB.otf");
	sf::Font& fontR = RES_MGR_FONT.Get("Font/NanumSquareR.otf");

	sf::RectangleShape backColor;

	SpriteGo background;
	SpriteGo demon;
	
	TextGo demonName;
	TextGo demonLine;
	TextGo demonLine2;

	SpriteGo wrongButton;
	SpriteGo correctButton;

	TextGo wrongText;
	TextGo correctText;

	sf::Sprite booper;

	sf::Sprite success;
	sf::Sprite badEnd;

	Animator booperAnimator;
	Animator badEndAnimator;
	Animator successAnimator;

	std::wstring panName = L"● 지친 악마, 판데모니카 ●";
	std::wstring pandLine1 = L"지옥 고객 서비스 센터의 판데모니카입니다.";
	std::wstring pandLine2 = L"무엇을 도와드릴까요?"; //TO-DO : 가운데 정렬하는 방법 찾아보기 ㅠ
	
	std::wstring wrongLine = L"우리 집에 한번 오면 알게 될거야.";
	std::wstring correctLine = L"오히려 '그 쪽'을 도와줘야 할 판인데?";

	SelectLine currentSelect = SelectLine::Wrong;

	bool isBadEnd = false;
	bool isSuccess = false;
	bool isBooperOn = false;

	int step = 0;

	bool isAnswerSelect = false;
	int currentStage = 1; //stage마다 창 내용 다르게 바꿔주려고

	float timer = 0.f;
	float changeTime = 3.f;

public:
	CollectDemon(const std::string& name = "");
	virtual ~CollectDemon();

	void Init() override;
	void Release() override;

	void Reset() override;

	Chapter* chapter;

	void Update(float dt) override;

	void Select();
	bool GetAnswerSelect() { return isAnswerSelect; }
	void SetAnswerSelect(bool answer) { isAnswerSelect = answer; }

	void Draw(sf::RenderWindow& window) override;

};

