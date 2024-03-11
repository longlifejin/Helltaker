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

	std::wstring panName = L"�� ��ģ �Ǹ�, �ǵ����ī ��";
	std::wstring pandLine1 = L"���� �� ���� ������ �ǵ����ī�Դϴ�.";
	std::wstring pandLine2 = L"������ ���͵帱���?"; //TO-DO : ��� �����ϴ� ��� ã�ƺ��� ��
	
	std::wstring wrongLine = L"�츮 ���� �ѹ� ���� �˰� �ɰž�.";
	std::wstring correctLine = L"������ '�� ��'�� ������� �� ���ε�?";

	SelectLine currentSelect = SelectLine::Wrong;
	Page currentPage = Page::FirstLine;

	bool isSelectTime = false;
	bool isBadEnd = false;
	bool isSuccess = false;

	std::vector<Dialogue> dialogues = {
	   {L"���� �� ���� ������ �ǵ����ī�Դϴ�. \n������ ���͵帱���?", {L"�츮 ���� �ѹ� ���� �˰� �ɰž�.", L"������ '�� ��'�� ������� �� ���ε�?"}, {1,2}},
	   {L"������ ��Ƽ� ���� ������ �Ѱž�? ���� ���ϼŶ�.", {}, {}},
	   {L"�� ������ �����̿���. Ŀ�Ǹ� ���ð� �ͳ׿�. \n�ǰ��ؼ� ������ �� �����ھ��.", {},{}},
	};

	unsigned int currentDialogueIndex = 0;
	int selectedOption = -1;


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

