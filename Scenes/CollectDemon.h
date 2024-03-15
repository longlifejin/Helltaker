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

	std::wstring panName = L"�� ��ģ �Ǹ�, �ǵ����ī ��";
	std::wstring pandLine1 = L"���� �� ���� ������ �ǵ����ī�Դϴ�.";
	std::wstring pandLine2 = L"������ ���͵帱���?"; //TO-DO : ��� �����ϴ� ��� ã�ƺ��� ��
	
	std::wstring wrongLine = L"�츮 ���� �ѹ� ���� �˰� �ɰž�.";
	std::wstring correctLine = L"������ '�� ��'�� ������� �� ���ε�?";

	SelectLine currentSelect = SelectLine::Wrong;

	bool isBadEnd = false;
	bool isSuccess = false;
	bool isBooperOn = false;

	int step = 0;

	bool isAnswerSelect = false;
	int currentStage = 1; //stage���� â ���� �ٸ��� �ٲ��ַ���

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

