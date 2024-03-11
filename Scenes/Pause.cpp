#include "pch.h"
#include "Pause.h"

Pause::Pause(const std::string& name)
	:GameObject(name)
{
}

Pause::~Pause()
{
}

void Pause::Init()
{
	backColor.setFillColor({ 2, 2, 27, 220});
	backColor.setSize({ (float)FRAMEWORK.GetWindowSize().x, (float)FRAMEWORK.GetWindowSize().y });
	backColor.setOrigin({ 0.f,0.f });
	backColor.setPosition({ 0.f,0.f });

	menuText.Set(fontEB, L"● 일시정지 메뉴 ●", 40, sf::Color(219, 72, 77));
	menuText.SetOrigin(Origins::MC);
	menuText.SetPosition({ (float)FRAMEWORK.GetWindowSize().x * 0.5f, (float)FRAMEWORK.GetWindowSize().y * 0.1f });

	float Offset = 80.f;

	backSprite.SetTexture("Texture2D/button_small_edit.png");
	backSprite.SetColor(219, 72, 77);
	backSprite.SetScale({ 1.1f,1.1f });
	backSprite.SetOrigin(Origins::MC);
	backSprite.SetPosition({ menuText.GetPosition().x, menuText.GetPosition().y + Offset * 1.5f});

	passSprite.SetTexture("Texture2D/button_small_edit.png");
	passSprite.SetColor(82, 46, 61);
	passSprite.SetScale({ 1.f,1.f });
	passSprite.SetOrigin(Origins::MC);
	passSprite.SetPosition({ backSprite.GetPosition().x, backSprite.GetPosition().y + Offset });

	bgmSprite.SetTexture("Texture2D/button_small_edit.png");
	bgmSprite.SetColor(82, 46, 61);
	bgmSprite.SetScale({ 1.f,1.f });
	bgmSprite.SetOrigin(Origins::MC);
	bgmSprite.SetPosition({ passSprite.GetPosition().x, passSprite.GetPosition().y + Offset });

	sfxSprite.SetTexture("Texture2D/button_small_edit.png");
	sfxSprite.SetColor(82, 46, 61);
	sfxSprite.SetScale({ 1.f,1.f });
	sfxSprite.SetOrigin(Origins::MC);
	sfxSprite.SetPosition({ bgmSprite.GetPosition().x, bgmSprite.GetPosition().y + Offset *1.5f });

	goMainSprite.SetTexture("Texture2D/button_small_edit.png");
	goMainSprite.SetColor(82, 46, 61);
	goMainSprite.SetScale({ 1.f,1.f });
	goMainSprite.SetOrigin(Origins::MC);
	goMainSprite.SetPosition({ sfxSprite.GetPosition().x, sfxSprite.GetPosition().y + Offset * 1.5f });

	backText.Set(fontR, L"돌아가기", 30, sf::Color::White);
	backText.SetOrigin(Origins::MC);
	backText.SetPosition({ backSprite.GetPosition().x, backSprite.GetPosition().y - 10.f});

	passText.Set(fontR, L"퍼즐 넘기기", 30, sf::Color::White);
	passText.SetOrigin(Origins::MC);
	passText.SetPosition({ passSprite.GetPosition().x, passSprite.GetPosition().y - 10.f });

	bgmText.Set(fontR, L"음악", 30, sf::Color::White);
	bgmText.SetOrigin(Origins::MC);
	bgmText.SetPosition({ bgmSprite.GetPosition().x, bgmSprite.GetPosition().y - 10.f });

	currentBgmVolumeText.Set(fontR, L"음소거", 30, sf::Color::White); //볼륨 설정에 따라 setstring해주기
	currentBgmVolumeText.SetOrigin(Origins::MC);
	currentBgmVolumeText.SetPosition({ bgmText.GetPosition().x, bgmText.GetPosition().y + 55.f });

	sfxText.Set(fontR, L"사운드", 30, sf::Color::White);
	sfxText.SetOrigin(Origins::MC);
	sfxText.SetPosition({ sfxSprite.GetPosition().x, sfxSprite.GetPosition().y - 10.f });

	currentSfxVolumeText.Set(fontR, L"음소거", 30, sf::Color::White); //볼륨 설정에 따라 setstring해주기
	currentSfxVolumeText.SetOrigin(Origins::MC);
	currentSfxVolumeText.SetPosition({ sfxText.GetPosition().x, sfxText.GetPosition().y + 55.f });

	goMainText.Set(fontR, L"메인 메뉴", 30, sf::Color::White);
	goMainText.SetOrigin(Origins::MC);
	goMainText.SetPosition({ goMainSprite.GetPosition().x, goMainSprite.GetPosition().y - 10.f });

	//ritCodeLeft.SetTexture()




}

void Pause::Release()
{
}

void Pause::Update(float dt)
{
}

void Pause::Draw(sf::RenderWindow& window)
{
	GameObject::Draw(window);
	window.draw(backColor);

	menuText.Draw(window);

	backSprite.Draw(window);
	passSprite.Draw(window);
	bgmSprite.Draw(window);
	sfxSprite.Draw(window);
	goMainSprite.Draw(window);

	backText.Draw(window);
	passText.Draw(window);
	bgmText.Draw(window);
	currentBgmVolumeText.Draw(window);
	sfxText.Draw(window);
	currentSfxVolumeText.Draw(window);
	goMainText.Draw(window);

	ritCodeLeft.Draw(window);
	ritCodeRight.Draw(window);

	ritBorder.Draw(window);
	ritStar.Draw(window);
}
