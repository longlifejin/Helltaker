#pragma once
#include "Scene.h"
#include "SpriteGo.h"
#include "TextGo.h"

class Transition;
class Chapter;

class TitleScene : public Scene
{
	enum class Button
	{
		NEWGAME = 0,
		CHAPTERSELECT,
		EXIT,
	};

	struct ChapterButton
	{
		SpriteGo* outLineSprite;
		SpriteGo* insideSprite;
		SpriteGo* text;
		bool selected = false;

		ChapterButton(const std::string& chapterNumTextureId)
		{
			outLineSprite->SetTexture("Sprite/W_chapter1.png");
			insideSprite->SetTexture("Sprite/W_W_chapter2");
			text->SetTexture(chapterNumTextureId);
		}
	};

protected:
	std::wstring fly = L"● 위대한 파리, 베엘제붑 ●";
	std::wstring newGame = L"새 게임";
	std::wstring chapterSelect = L"챕터 선택";
	std::wstring exit = L"나가기";

	std::vector<SpriteGo*> buttons;
	std::vector<TextGo*> buttonTexts;
	int currentButtonIndex = 0;
	int numberofButtons = buttons.size();

	std::vector<ChapterButton*> chapterButtons;

public:
	TitleScene(SceneIds id);
	virtual ~TitleScene();

	Transition* transition = nullptr;
	Chapter* chapter;

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

	Button currentSelection = Button::NEWGAME;

	void UpdateButtonStates();

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

};

