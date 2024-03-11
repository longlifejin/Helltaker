#pragma once
#include "GameObject.h"
#include "SpriteGo.h"
#include "TextGo.h"


class Pause : public GameObject
{
protected:
	sf::Font& fontEB = RES_MGR_FONT.Get("Font/NanumSquareEB.otf");
	sf::Font& fontR = RES_MGR_FONT.Get("Font/NanumSquareR.otf");

	sf::RectangleShape backColor;
	
	TextGo menuText;

	SpriteGo backSprite;
	SpriteGo passSprite;
	SpriteGo bgmSprite;
	SpriteGo sfxSprite;
	SpriteGo goMainSprite;

	TextGo backText;
	TextGo passText;
	TextGo bgmText;
	TextGo currentBgmVolumeText;
	TextGo sfxText;
	TextGo currentSfxVolumeText;
	TextGo goMainText;

	SpriteGo ritCodeLeft;
	SpriteGo ritCodeRight;

	SpriteGo ritBorder;
	SpriteGo ritStar;

public:
	Pause(const std::string& name = "");
	virtual ~Pause();

	void Init() override;
	void Release() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

