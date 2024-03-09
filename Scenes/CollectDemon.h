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

	SpriteGo* select1;
	SpriteGo* select2;

	SpriteGo* booper;

	std::wstring panName = L"�� ��ģ �Ǹ�, �ǵ����ī ��";
	std::wstring pandLine1 = L"���� �� ���� ������ �ǵ����ī�Դϴ�.";
	std::wstring pandLine2 = L"������ ���͵帱���?"; //TO-DO : ��� �����ϴ� ��� ã�ƺ��� ��
	
	SelectLine currentSelect = SelectLine::Wrong;

public:
	CollectDemon(SceneIds id);
	virtual ~CollectDemon();

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

};

