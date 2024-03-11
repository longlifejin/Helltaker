#pragma once
#include "Scene.h"

class SpriteGo;
class TextGo;

struct Dialogue
{
	std::wstring text;
	std::vector<std::wstring> options; // ������
	std::vector<int> nextIndex; // �������� ���� ���� ����� �ε���
	bool haveOptions() const { return !options.empty(); }
};

class CollectDemon : public Scene
{
	enum class SelectLine
	{
		Correct,
		Wrong,
	};


	enum class Page //space���������� ��� ����ǰ� �Ϸ���
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

	std::wstring panName = L"�� ��ģ �Ǹ�, �ǵ����ī ��";
	std::wstring pandLine1 = L"���� �� ���� ������ �ǵ����ī�Դϴ�.";
	std::wstring pandLine2 = L"������ ���͵帱���?"; //TO-DO : ��� �����ϴ� ��� ã�ƺ��� ��
	
	std::wstring wrongLine = L"�츮 ���� �ѹ� ���� �˰� �ɰž�.";
	std::wstring correctLine = L"������ '�� ��'�� ������� �� ���ε�?";

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

