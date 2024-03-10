#pragma once
#include "Scene.h"

class SpriteGo;
class TextGo;

class CollectDemon : public Scene
{
	enum class SelectLine
	{
		Correct,
		Wrong,
	};

protected:

	SpriteGo* background;
	SpriteGo* demon;
	
	TextGo* demonName;
	TextGo* demonLine1;
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

	bool isSelectTime = false;
	bool isBadEnd = false;
	bool isSuccess = false;

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

