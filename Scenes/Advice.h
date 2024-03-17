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

	std::wstring name = L"�� ������ �ĸ�, �������� ��";
	std::wstring Line1 = L"������ ��� �Ͱ�����, �ƹ��� ������ ����� ���ϰڱ�.";
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

