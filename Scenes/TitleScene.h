#pragma once
#include "Scene.h"
#include "SpriteGo.h"
#include "TextGo.h"

class TransitionDown;

class TitleScene : public Scene
{
	enum class Button
	{
		NEWGAME,
		CHAPTERSELECT,
		EXIT,
	};

protected:
	std::wstring fly = L"�� ������ �ĸ�, �������� ��";
	std::wstring newGame = L"�� ����";
	std::wstring chaterSelect = L"é�� ����";
	std::wstring exit = L"������";


public:
	TitleScene(SceneIds id);
	virtual ~TitleScene();

	TransitionDown* transitionDown;

	sf::RectangleShape backColor;

	SpriteGo* background1;
	SpriteGo* background2;

	SpriteGo* beelzebub;
	TextGo* theGreatFly;

	SpriteGo* newGameButton;
	TextGo* newGameText;

	SpriteGo* chapterSelectButton;
	TextGo* chapterSelectText;

	SpriteGo* exitButton;
	TextGo* exitText;

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	Button prevSelection = Button::NEWGAME;
	Button currentSelection = Button::NEWGAME;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

};

