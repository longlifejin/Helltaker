#pragma once
#include "Scene.h"
#include "SpriteGo.h"
#include "TextGo.h"

class TitleScene : public Scene
{
	enum class Button
	{
		NEWGAME,
		CHAPTERSELECT,
		EXIT,
	};

protected:
	std::wstring fly = L"● 위대한 파리, 베엘제붑 ●";
	std::wstring newGame = L"새 게임";
	std::wstring chaterSelect = L"챕터 선택";
	std::wstring exit = L"나가기";

public:
	TitleScene(SceneIds id);
	virtual ~TitleScene();

	SpriteGo* background1;
	SpriteGo* background2;

	SpriteGo* beelzebub;
	TextGo* theGreatFly;

	SpriteGo* whiteCircle;

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

};

