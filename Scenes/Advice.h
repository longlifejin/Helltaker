#pragma once
#include "GameObject.h"
#include "SpriteGo.h"
#include "TextGo.h"

class Chapter;

class Advice : public GameObject
{
protected:
	sf::Font& fontEB = RES_MGR_FONT.Get("Font/NanumSquareEB.otf");
	sf::Font& fontR = RES_MGR_FONT.Get("Font/NanumSquareR.otf");

	int step = 0;
	float Offset = 50.f;

	sf::RectangleShape backColor;
	SpriteGo background;
	SpriteGo demon;

	TextGo demonName;
	TextGo demonLine;
	TextGo demonLine2;

	sf::Sprite booper;
	bool isBooperOn = true;

	std::wstring name = L"● 위대한 파리, 베엘제붑 ●";
	std::wstring Line1 = L"조언을 얻고 싶겠지만, 아무도 없으니 물어보질 못하겠군.";
	std::wstring Line2 = L"";

	Animator booperAnimator;
	Chapter* chapter;

public:
	Advice(const std::string& name = "");
	virtual ~Advice();

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;

	void Stage1();
	void Stage2();
	void Develop();

	void Draw(sf::RenderWindow& window) override;
};

