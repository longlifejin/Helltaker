#pragma once
#include "Scene.h"
#include "SpriteGo.h"
#include "TextGo.h"

class TitleScene : public Scene
{
protected:


public:
	TitleScene(SceneIds id);
	virtual ~TitleScene();

	SpriteGo* background;

	SpriteGo* beelzebub;
	TextGo* theGreatFly;


	SpriteGo* newGameButton;
	TextGo* newGame;

	SpriteGo* chapterSelectButton;
	TextGo* chapterSelect;

	SpriteGo* exitButton;
	TextGo* exit;

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Update(float dt) override;

};

