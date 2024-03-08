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


public:
	TitleScene(SceneIds id);
	virtual ~TitleScene();

	SpriteGo* background;

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

	Button currentSelection = Button::NEWGAME;

	void Update(float dt) override;

};

