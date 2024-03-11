#pragma once
#include "Scene.h"
#include "SpriteGo.h"
#include "TextGo.h"

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

	SpriteGo booper;

	SpriteGo success;
	SpriteGo badEnd;

	std::wstring panName = L"�� ��ģ �Ǹ�, �ǵ����ī ��";
	std::wstring pandLine1 = L"���� �� ���� ������ �ǵ����ī�Դϴ�.";
	std::wstring pandLine2 = L"������ ���͵帱���?"; //TO-DO : ��� �����ϴ� ��� ã�ƺ��� ��
	
	std::wstring wrongLine = L"�츮 ���� �ѹ� ���� �˰� �ɰž�.";
	std::wstring correctLine = L"������ '�� ��'�� ������� �� ���ε�?";

	SelectLine currentSelect = SelectLine::Wrong;

	int step = 0;

	bool isAnswerSelect = false;

public:
	CollectDemon(const std::string& name = "");
	virtual ~CollectDemon();

	void Init() override;
	void Release() override;

	void Update(float dt) override;

	void Select();
	bool GetAnswerSelect() { return isAnswerSelect; }

	void Draw(sf::RenderWindow& window) override;

};

