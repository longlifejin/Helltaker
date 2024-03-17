#include "pch.h"
#include "Pause.h"
#include "Chapter.h"
#include "CollectDemon.h"
#include "Transition.h"

Pause::Pause(const std::string& name)
	:GameObject(name)
{
}

Pause::~Pause()
{
}

void Pause::Init()
{
	currentSelect = Select::BACK;

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

	passText.Set(fontR, L"퍼즐 넘기기", 30, sf::Color(82, 46, 61));
	passText.SetOrigin(Origins::MC);
	passText.SetPosition({ passSprite.GetPosition().x, passSprite.GetPosition().y - 10.f });

	bgmText.Set(fontR, L"음악", 30, sf::Color(82, 46, 61));
	bgmText.SetOrigin(Origins::MC);
	bgmText.SetPosition({ bgmSprite.GetPosition().x, bgmSprite.GetPosition().y - 10.f });

	currentBgmVolumeText.Set(fontR, L"큼", 30, sf::Color(82, 46, 61)); //볼륨 설정에 따라 setstring해주기
	currentBgmVolumeText.SetOrigin(Origins::MC);
	currentBgmVolumeText.SetPosition({ bgmText.GetPosition().x, bgmText.GetPosition().y + 55.f });

	sfxText.Set(fontR, L"사운드", 30, sf::Color(82, 46, 61));
	sfxText.SetOrigin(Origins::MC);
	sfxText.SetPosition({ sfxSprite.GetPosition().x, sfxSprite.GetPosition().y - 10.f });

	currentSfxVolumeText.Set(fontR, L"큼", 30, sf::Color(82, 46, 61)); //볼륨 설정에 따라 setstring해주기
	currentSfxVolumeText.SetOrigin(Origins::MC);
	currentSfxVolumeText.SetPosition({ sfxText.GetPosition().x, sfxText.GetPosition().y + 55.f });

	goMainText.Set(fontR, L"메인 메뉴", 30, sf::Color(82, 46, 61));
	goMainText.SetOrigin(Origins::MC);
	goMainText.SetPosition({ goMainSprite.GetPosition().x, goMainSprite.GetPosition().y - 10.f });

	ritBorderLeft.SetTexture("Texture2D/ritBorder.png");
	ritBorderLeft.SetOrigin(Origins::BL);
	ritBorderLeft.SetPosition({ goMainSprite.GetPosition().x - 420.f, goMainSprite.GetPosition().y + 220.f });

	ritBorderRight.SetTexture("Texture2D/ritBorder.png");
	ritBorderRight.SetOrigin(Origins::BL);
	ritBorderRight.SetScale({ -1.f,1.f });
	ritBorderRight.SetPosition({ goMainSprite.GetPosition().x + 420.f, goMainSprite.GetPosition().y + 220.f });

	ritStar.SetTexture("Texture2D/ritStar.png");
	ritStar.SetOrigin(Origins::BC);
	ritStar.SetPosition({ritBorderLeft.GetPosition().x + 420.f, ritBorderLeft.GetPosition().y + 30.f});

	ritCodeLeft.SetTexture("Texture2D/ritCode0001.png");
	ritCodeLeft.SetOrigin(Origins::MR);
	ritCodeLeft.SetScale({ 1.1f,1.1f });
	ritCodeLeft.SetPosition({ goMainSprite.GetPosition().x - 110.f,goMainSprite.GetPosition().y + 100.f  });

	ritCodeRight.SetTexture("Texture2D/ritCode0004_edit.png");
	ritCodeRight.SetOrigin(Origins::ML);
	ritCodeRight.SetScale({ 1.1f,1.1f });
	ritCodeRight.SetPosition({ ritCodeLeft.GetPosition().x + 10.f ,goMainText.GetPosition().y + 110.f });
}

void Pause::Release()
{
	GameObject::Release();
}

void Pause::Update(float dt)
{
	chapter = dynamic_cast<Chapter*>(SCENE_MGR.GetCurrentScene());

	if (InputMgr::GetKeyDown(sf::Keyboard::W))
	{
		switch (currentSelect)
		{
		case Select::BACK:
			currentSelect = Select::MAIN;

			backSprite.SetTexture("Texture2D/button_small_edit.png");
			backSprite.SetColor(82, 46, 61);
			backSprite.SetScale({ 1.f,1.f });
			backText.SetColor(82, 46, 61);

			passSprite.SetTexture("Texture2D/button_small_edit.png");
			passSprite.SetColor(82, 46, 61);
			passSprite.SetScale({ 1.f,1.f });
			passText.SetColor(82, 46, 61);

			bgmSprite.SetTexture("Texture2D/button_small_edit.png");
			bgmSprite.SetColor(82, 46, 61);
			bgmSprite.SetScale({ 1.f,1.f });
			bgmText.SetColor(82, 46, 61);

			sfxSprite.SetTexture("Texture2D/button_small_edit.png");
			sfxSprite.SetColor(82, 46, 61);
			sfxSprite.SetScale({ 1.f,1.f });
			sfxText.SetColor(82, 46, 61);

			currentBgmVolumeText.SetColor(82, 46, 61);
			currentSfxVolumeText.SetColor(82, 46, 61);

			goMainSprite.SetTexture("Texture2D/button_small_edit.png");
			goMainSprite.SetColor(219, 72, 77);
			goMainSprite.SetScale({ 1.1f,1.1f });
			goMainText.SetColor(sf::Color::White);
			break;
		case Select::PASS:
			currentSelect = Select::BACK;

			backSprite.SetTexture("Texture2D/button_small_edit.png");
			backSprite.SetColor(219, 72, 77);
			backSprite.SetScale({ 1.1f,1.1f });
			backText.SetColor(sf::Color::White);

			passSprite.SetTexture("Texture2D/button_small_edit.png");
			passSprite.SetColor(82, 46, 61);
			passSprite.SetScale({ 1.f,1.f });
			passText.SetColor(82, 46, 61);

			bgmSprite.SetTexture("Texture2D/button_small_edit.png");
			bgmSprite.SetColor(82, 46, 61);
			bgmSprite.SetScale({ 1.f,1.f });
			bgmText.SetColor(82, 46, 61);

			sfxSprite.SetTexture("Texture2D/button_small_edit.png");
			sfxSprite.SetColor(82, 46, 61);
			sfxSprite.SetScale({ 1.f,1.f });
			sfxText.SetColor(82, 46, 61);

			currentBgmVolumeText.SetColor(82, 46, 61);
			currentSfxVolumeText.SetColor(82, 46, 61);

			goMainSprite.SetTexture("Texture2D/button_small_edit.png");
			goMainSprite.SetColor(82, 46, 61);
			goMainSprite.SetScale({ 1.f,1.f });
			goMainText.SetColor(82, 46, 61);
			break;
		case Select::BGM:
			currentSelect = Select::PASS;

			backSprite.SetTexture("Texture2D/button_small_edit.png");
			backSprite.SetColor(82, 46, 61);
			backSprite.SetScale({ 1.f,1.f });
			backText.SetColor(82, 46, 61);

			passSprite.SetTexture("Texture2D/button_small_edit.png");
			passSprite.SetColor(219, 72, 77);
			passSprite.SetScale({ 1.1f,1.1f });
			passText.SetColor(sf::Color::White);

			bgmSprite.SetTexture("Texture2D/button_small_edit.png");
			bgmSprite.SetColor(82, 46, 61);
			bgmSprite.SetScale({ 1.f,1.f });
			bgmText.SetColor(82, 46, 61);

			sfxSprite.SetTexture("Texture2D/button_small_edit.png");
			sfxSprite.SetColor(82, 46, 61);
			sfxSprite.SetScale({ 1.f,1.f });
			sfxText.SetColor(82, 46, 61);

			currentBgmVolumeText.SetColor(82, 46, 61);
			currentSfxVolumeText.SetColor(82, 46, 61);

			goMainSprite.SetTexture("Texture2D/button_small_edit.png");
			goMainSprite.SetColor(82, 46, 61);
			goMainSprite.SetScale({ 1.f,1.f });
			goMainText.SetColor(82, 46, 61);
			break;
		case Select::SFX:
			currentSelect = Select::BGM;

			backSprite.SetTexture("Texture2D/button_small_edit.png");
			backSprite.SetColor(82, 46, 61);
			backSprite.SetScale({ 1.f,1.f });
			backText.SetColor(82, 46, 61);

			passSprite.SetTexture("Texture2D/button_small_edit.png");
			passSprite.SetColor(82, 46, 61);
			passSprite.SetScale({ 1.f,1.f });
			passText.SetColor(82, 46, 61);

			bgmSprite.SetTexture("Texture2D/button_small_edit.png");
			bgmSprite.SetColor(219, 72, 77);
			bgmSprite.SetScale({ 1.1f,1.1f });
			bgmText.SetColor(sf::Color::White);

			sfxSprite.SetTexture("Texture2D/button_small_edit.png");
			sfxSprite.SetColor(82, 46, 61);
			sfxSprite.SetScale({ 1.f,1.f });
			sfxText.SetColor(82, 46, 61);

			currentBgmVolumeText.SetColor(sf::Color::White);
			currentSfxVolumeText.SetColor(82, 46, 61);

			goMainSprite.SetTexture("Texture2D/button_small_edit.png");
			goMainSprite.SetColor(82, 46, 61);
			goMainSprite.SetScale({ 1.f,1.f });
			goMainText.SetColor(82, 46, 61);
			break;
		case Select::MAIN:
			currentSelect = Select::SFX;

			backSprite.SetTexture("Texture2D/button_small_edit.png");
			backSprite.SetColor(82, 46, 61);
			backSprite.SetScale({ 1.f,1.f });
			backText.SetColor(82, 46, 61);

			passSprite.SetTexture("Texture2D/button_small_edit.png");
			passSprite.SetColor(82, 46, 61);
			passSprite.SetScale({ 1.f,1.f });
			passText.SetColor(82, 46, 61);

			bgmSprite.SetTexture("Texture2D/button_small_edit.png");
			bgmSprite.SetColor(82, 46, 61);
			bgmSprite.SetScale({ 1.f,1.f });
			bgmText.SetColor(82, 46, 61);

			sfxSprite.SetTexture("Texture2D/button_small_edit.png");
			sfxSprite.SetColor(219, 72, 77);
			sfxSprite.SetScale({ 1.1f,1.1f });
			sfxText.SetColor(sf::Color::White);

			currentBgmVolumeText.SetColor(82, 46, 61);
			currentSfxVolumeText.SetColor(sf::Color::White);

			goMainSprite.SetTexture("Texture2D/button_small_edit.png");
			goMainSprite.SetColor(82, 46, 61);
			goMainSprite.SetScale({ 1.f,1.f });
			goMainText.SetColor(82, 46, 61);
			break;

		}
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::S))
	{
		switch (currentSelect)
		{
		case Select::BACK:
			currentSelect = Select::PASS;

			backSprite.SetTexture("Texture2D/button_small_edit.png");
			backSprite.SetColor(82, 46, 61);
			backSprite.SetScale({ 1.f,1.f });
			backText.SetColor(82, 46, 61);

			passSprite.SetTexture("Texture2D/button_small_edit.png");
			passSprite.SetColor(219, 72, 77);
			passSprite.SetScale({ 1.1f,1.1f });
			passText.SetColor(sf::Color::White);

			bgmSprite.SetTexture("Texture2D/button_small_edit.png");
			bgmSprite.SetColor(82, 46, 61);
			bgmSprite.SetScale({ 1.f,1.f });
			bgmText.SetColor(82, 46, 61);

			sfxSprite.SetTexture("Texture2D/button_small_edit.png");
			sfxSprite.SetColor(82, 46, 61);
			sfxSprite.SetScale({ 1.f,1.f });
			sfxText.SetColor(82, 46, 61);

			currentBgmVolumeText.SetColor(82, 46, 61);
			currentSfxVolumeText.SetColor(82, 46, 61);

			goMainSprite.SetTexture("Texture2D/button_small_edit.png");
			goMainSprite.SetColor(82, 46, 61);
			goMainSprite.SetScale({ 1.f,1.f });
			goMainText.SetColor(82, 46, 61);
			break;
		case Select::PASS:
			currentSelect = Select::BGM;

			backSprite.SetTexture("Texture2D/button_small_edit.png");
			backSprite.SetColor(82, 46, 61);
			backSprite.SetScale({ 1.f,1.f });
			backText.SetColor(82, 46, 61);

			passSprite.SetTexture("Texture2D/button_small_edit.png");
			passSprite.SetColor(82, 46, 61);
			passSprite.SetScale({ 1.f,1.f });
			passText.SetColor(82, 46, 61);

			bgmSprite.SetTexture("Texture2D/button_small_edit.png");
			bgmSprite.SetColor(219, 72, 77);
			bgmSprite.SetScale({ 1.1f,1.1f });
			bgmText.SetColor(sf::Color::White);

			sfxSprite.SetTexture("Texture2D/button_small_edit.png");
			sfxSprite.SetColor(82, 46, 61);
			sfxSprite.SetScale({ 1.f,1.f });
			sfxText.SetColor(82, 46, 61);

			currentBgmVolumeText.SetColor(sf::Color::White);
			currentSfxVolumeText.SetColor(82, 46, 61);

			goMainSprite.SetTexture("Texture2D/button_small_edit.png");
			goMainSprite.SetColor(82, 46, 61);
			goMainSprite.SetScale({ 1.f,1.f });
			goMainText.SetColor(82, 46, 61);
			break;
		case Select::BGM:
			currentSelect = Select::SFX;

			backSprite.SetTexture("Texture2D/button_small_edit.png");
			backSprite.SetColor(82, 46, 61);
			backSprite.SetScale({ 1.f,1.f });
			backText.SetColor(82, 46, 61);

			passSprite.SetTexture("Texture2D/button_small_edit.png");
			passSprite.SetColor(82, 46, 61);
			passSprite.SetScale({ 1.f,1.f });
			passText.SetColor(82, 46, 61);

			bgmSprite.SetTexture("Texture2D/button_small_edit.png");
			bgmSprite.SetColor(82, 46, 61);
			bgmSprite.SetScale({ 1.f,1.f });
			bgmText.SetColor(82, 46, 61);

			sfxSprite.SetTexture("Texture2D/button_small_edit.png");
			sfxSprite.SetColor(219, 72, 77);
			sfxSprite.SetScale({ 1.1f,1.1f });
			sfxText.SetColor(sf::Color::White);

			currentBgmVolumeText.SetColor(82, 46, 61);
			currentSfxVolumeText.SetColor(sf::Color::White);

			goMainSprite.SetTexture("Texture2D/button_small_edit.png");
			goMainSprite.SetColor(82, 46, 61);
			goMainSprite.SetScale({ 1.f,1.f });
			goMainText.SetColor(82, 46, 61);
			break;
		case Select::SFX:
			currentSelect = Select::MAIN;

			backSprite.SetTexture("Texture2D/button_small_edit.png");
			backSprite.SetColor(82, 46, 61);
			backSprite.SetScale({ 1.f,1.f });
			backText.SetColor(82, 46, 61);

			passSprite.SetTexture("Texture2D/button_small_edit.png");
			passSprite.SetColor(82, 46, 61);
			passSprite.SetScale({ 1.f,1.f });
			passText.SetColor(82, 46, 61);

			bgmSprite.SetTexture("Texture2D/button_small_edit.png");
			bgmSprite.SetColor(82, 46, 61);
			bgmSprite.SetScale({ 1.f,1.f });
			bgmText.SetColor(82, 46, 61);

			sfxSprite.SetTexture("Texture2D/button_small_edit.png");
			sfxSprite.SetColor(82, 46, 61);
			sfxSprite.SetScale({ 1.f,1.f });
			sfxText.SetColor(82, 46, 61);

			currentBgmVolumeText.SetColor(82, 46, 61);
			currentSfxVolumeText.SetColor(82, 46, 61);

			goMainSprite.SetTexture("Texture2D/button_small_edit.png");
			goMainSprite.SetColor(219, 72, 77);
			goMainSprite.SetScale({ 1.1f,1.1f });
			goMainText.SetColor(sf::Color::White);
			break;
		case Select::MAIN:
			currentSelect = Select::BACK;

			backSprite.SetTexture("Texture2D/button_small_edit.png");
			backSprite.SetColor(219, 72, 77);
			backSprite.SetScale({ 1.1f,1.1f });
			backText.SetColor(sf::Color::White);

			passSprite.SetTexture("Texture2D/button_small_edit.png");
			passSprite.SetColor(82, 46, 61);
			passSprite.SetScale({ 1.f,1.f });
			passText.SetColor(82, 46, 61);

			bgmSprite.SetTexture("Texture2D/button_small_edit.png");
			bgmSprite.SetColor(82, 46, 61);
			bgmSprite.SetScale({ 1.f,1.f });
			bgmText.SetColor(82, 46, 61);

			sfxSprite.SetTexture("Texture2D/button_small_edit.png");
			sfxSprite.SetColor(82, 46, 61);
			sfxSprite.SetScale({ 1.f,1.f });
			sfxText.SetColor(82, 46, 61);

			currentBgmVolumeText.SetColor(82, 46, 61);
			currentSfxVolumeText.SetColor(82, 46, 61);

			goMainSprite.SetTexture("Texture2D/button_small_edit.png");
			goMainSprite.SetColor(82, 46, 61);
			goMainSprite.SetScale({ 1.f,1.f });
			goMainText.SetColor(82, 46, 61);
			break;

		}
	}

	if (currentSelect == Select::BGM)
	{
		if (InputMgr::GetKeyDown(sf::Keyboard::A))
		{
			switch (currentBGMVolume)
			{
			case Volume::LOUD:
				currentBGMVolume = Volume::MIDDLE;
				currentBgmVolumeText.SetString(L"중간");
				break;
			case Volume::MIDDLE:
				currentBGMVolume = Volume::SMALL;
				currentBgmVolumeText.SetString(L"작음");
				break;
			case Volume::SMALL:
				currentBGMVolume = Volume::MUTE;
				currentBgmVolumeText.SetString(L"음소거");
				break;
			case Volume::MUTE:
				currentBGMVolume = Volume::LOUD;
				currentBgmVolumeText.SetString(L"큼");
				break;
			}
		}
		if (InputMgr::GetKeyDown(sf::Keyboard::D))
		{
			switch (currentBGMVolume)
			{
			case Volume::LOUD:
				currentBGMVolume = Volume::MUTE;
				currentBgmVolumeText.SetString(L"음소거");
				break;
			case Volume::MIDDLE:
				currentBGMVolume = Volume::LOUD;
				currentBgmVolumeText.SetString(L"큼");
				break;
			case Volume::SMALL:
				currentBGMVolume = Volume::MIDDLE;
				currentBgmVolumeText.SetString(L"중간");
				break;
			case Volume::MUTE:
				currentBGMVolume = Volume::SMALL;
				currentBgmVolumeText.SetString(L"작음");
				break;
			}
		}
	}

	if (currentSelect == Select::SFX)
	{
		if (InputMgr::GetKeyDown(sf::Keyboard::A))
		{
			switch (currentSFXVolume)
			{
			case Volume::LOUD:
				currentSFXVolume = Volume::MIDDLE;
				currentSfxVolumeText.SetString(L"중간");
				break;
			case Volume::MIDDLE:
				currentSFXVolume = Volume::SMALL;
				currentSfxVolumeText.SetString(L"작음");
				break;
			case Volume::SMALL:
				currentSFXVolume = Volume::MUTE;
				currentSfxVolumeText.SetString(L"음소거");
				break;
			case Volume::MUTE:
				currentSFXVolume = Volume::LOUD;
				currentSfxVolumeText.SetString(L"큼");
				break;
			}
		}
		if (InputMgr::GetKeyDown(sf::Keyboard::D))
		{
			switch (currentSFXVolume)
			{
			case Volume::LOUD:
				currentSFXVolume = Volume::MUTE;
				currentSfxVolumeText.SetString(L"음소거");
				break;
			case Volume::MIDDLE:
				currentSFXVolume = Volume::LOUD;
				currentSfxVolumeText.SetString(L"큼");
				break;
			case Volume::SMALL:
				currentSFXVolume = Volume::MIDDLE;
				currentSfxVolumeText.SetString(L"중간");
				break;
			case Volume::MUTE:
				currentSFXVolume = Volume::SMALL;
				currentSfxVolumeText.SetString(L"작음");
				break;
			}
		}
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		switch (currentSelect)
		{
		case Pause::Select::BACK:
			this->SetActive(false);
			FRAMEWORK.SetTimeScale(1.f);
			break;
		case Pause::Select::PASS: //collectDemon창 출력 후 올바르게 고르면 그 자리에서 getdemon애니메이션 출력
			FRAMEWORK.SetTimeScale(1.f);
			this->SetActive(false);
			chapter->isDemonGet = true;
			break;
		case Pause::Select::BGM: //사운드 넣고 볼륨 설정 추가해주기
			switch (currentBGMVolume)
			{
			case Pause::Volume::LOUD:
				break;
			case Pause::Volume::MIDDLE:
				break;
			case Pause::Volume::SMALL:
				break;
			case Pause::Volume::MUTE:
				break;
			default:
				break;
			}
			break;
		case Pause::Select::SFX:
			switch (currentSFXVolume)
			{
			case Pause::Volume::LOUD:
				break;
			case Pause::Volume::MIDDLE:
				break;
			case Pause::Volume::SMALL:
				break;
			case Pause::Volume::MUTE:
				break;
			default:
				break;
			}
			break;
		case Pause::Select::MAIN:
			FRAMEWORK.SetTimeScale(1.f);
			chapter->SetCurrentStage(1);
			//chapter->Init();
			chapter->transition->SetChangeScene(SceneIds::TITLESCENE);
			chapter->transition->PlayTransitionUp();
			this->SetActive(false);
			break;
		default:
			break;
		}
	}

	if (FRAMEWORK.GetTimeScale() == 1.f)
	{
		Release();
		Init();
	}
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

	ritBorderLeft.Draw(window);
	ritBorderRight.Draw(window);
	ritStar.Draw(window);
}
