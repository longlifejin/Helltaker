#include "pch.h"
#include "TitleScene.h"
#include "Transition.h"
#include "Chapter.h"

TitleScene::TitleScene(SceneIds id)
	: Scene(id)
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Init()
{
	backColor.setFillColor(sf::Color(2, 2, 27));
	backColor.setSize({ (float)FRAMEWORK.GetWindowSize().x, (float)FRAMEWORK.GetWindowSize().y });
	backColor.setOrigin({ 0.f,0.f });
	backColor.setPosition({ 0.f,0.f });

	background1 = new SpriteGo("Background1");
	background1->SetTexture("Texture2D/titleBG.png");
	background1->SetOrigin(Origins::TL);
	background1->SetPosition({ 0.f, 200.f }); //위치 잡는 부분 이렇게 안하는 방법이 있을까?
	AddGo(background1, Layers::Ui);

	background2 = new SpriteGo("Background2");
	background2->SetTexture("Texture2D/titleBG.png");
	background2->SetOrigin(Origins::TL);
	background2->SetPosition({ -(float)(FRAMEWORK.GetWindowSize().x), background1->GetPosition().y });
	AddGo(background2, Layers::Ui);

	beelzebub = new SpriteGo("Beelzebub");
	beelzebub->SetTexture("Sprite/beel_fly.png");
	beelzebub->SetOrigin(Origins::TC);
	beelzebub->SetPosition({ (float)(FRAMEWORK.GetWindowSize().x * 0.5), 0.f });
	AddGo(beelzebub, Layers::Ui);

	theGreatFly = new TextGo("TheGreatFly");
	theGreatFly->Set(fontResMgr.Get("Font/NanumSquareEB.otf"), fly, 40, sf::Color(219, 72, 77));

	theGreatFly->SetOrigin(Origins::MC);
	theGreatFly->SetPosition({ (float)(FRAMEWORK.GetWindowSize().x * 0.5), (float)(FRAMEWORK.GetWindowSize().y * 0.5) + 200.f });
	AddGo(theGreatFly, Layers::Ui);

	float buttonOffset = 90.f;

	newGameButton = new SpriteGo("NewGameButton");
	newGameButton->SetTexture("Texture2D/button0003.png");
	newGameButton->SetOrigin(Origins::MC);
	newGameButton->SetPosition({ (float)(FRAMEWORK.GetWindowSize().x * 0.5), (float)(FRAMEWORK.GetWindowSize().y * 0.5) + 300.f });
	newGameButton->SetScale({ 1.1f, 1.1f });
	newGameButton->SetColor(219, 72, 77);
	AddGo(newGameButton, Layers::Ui);

	chapterSelectButton = new SpriteGo("ChapterSelectButton");
	chapterSelectButton->SetTexture("Texture2D/button0004.png");
	chapterSelectButton->SetOrigin(Origins::MC);
	chapterSelectButton->SetPosition( {newGameButton->GetPosition().x, newGameButton->GetPosition().y + buttonOffset});
	chapterSelectButton->SetColor(82, 46, 61);
	AddGo(chapterSelectButton, Layers::Ui);

	exitButton = new SpriteGo("ExitButton");
	exitButton->SetTexture("Texture2D/button0004.png");
	exitButton->SetOrigin(Origins::MC);
	exitButton->SetPosition({chapterSelectButton->GetPosition().x, chapterSelectButton->GetPosition().y + buttonOffset});
	exitButton->SetColor(82, 46, 61);
	AddGo(exitButton, Layers::Ui);

	float textOffset = 9.f;

	newGameText = new TextGo("NewGameText");
	newGameText->Set(fontResMgr.Get("Font/NanumSquareR.otf"), newGame, 30, sf::Color::White);
	newGameText->SetOrigin(Origins::MC);
	newGameText->SetPosition({ newGameButton->GetPosition().x, newGameButton->GetPosition().y -textOffset });
	AddGo(newGameText, Layers::Ui);

	chapterSelectText = new TextGo("ChapterSelectText");
	chapterSelectText->Set(fontResMgr.Get("Font/NanumSquareR.otf"), chapterSelect, 30, sf::Color(82, 46, 61));
	chapterSelectText->SetOrigin(Origins::MC);
	chapterSelectText->SetPosition({ newGameText->GetPosition().x, newGameText->GetPosition().y + buttonOffset });
	AddGo(chapterSelectText, Layers::Ui);

	exitText = new TextGo("ExitText");
	exitText->Set(fontResMgr.Get("Font/NanumSquareR.otf"), exit, 30, sf::Color(82, 46, 61));
	exitText->SetOrigin(Origins::MC);
	exitText->SetPosition({ chapterSelectText->GetPosition().x, chapterSelectText->GetPosition().y + buttonOffset });
	AddGo(exitText, Layers::Ui);

	transition = new Transition("Transition");
	AddGo(transition, Layers::Ui);

	buttons.push_back(newGameButton); //0
	buttons.push_back(chapterSelectButton); //1
	buttons.push_back(exitButton); //2

	buttonTexts.push_back(newGameText);
	buttonTexts.push_back(chapterSelectText);
	buttonTexts.push_back(exitText);

	Scene::Init();
}

void TitleScene::Release()
{
	Scene::Release();
}

void TitleScene::Enter()
{
	SOUND_MGR.PlayBgm("AudioClip/Apropos.wav", false);

	sf::Vector2f windowSize = (sf::Vector2f)FRAMEWORK.GetWindowSize();
	worldView.setSize(windowSize);
	worldView.setCenter(windowSize * 0.5f);
	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);

	if (SCENE_MGR.CheckPrevScene() != SceneIds::TITLESCENE)
	{
		transition->PlayTransitionDown();
	}

	Scene::Enter();
}

void TitleScene::Exit()
{
	transition->SetChangeScene(SceneIds::TITLESCENE);
	transition->PlayTransitionUp();
	Scene::Exit(); 
}

void TitleScene::UpdateButtonStates()
{
	for (int i = 0; i < buttons.size(); ++i) 
	{
		if (i == currentButtonIndex) 
		{
			buttons[i]->SetTexture("Texture2D/button0003.png");
			buttons[i]->SetColor(219, 72, 77);
			buttons[i]->SetScale({ 1.1f, 1.1f });
			buttonTexts[i]->SetColor(sf::Color::White);

			if (i == 0)
			{
				currentSelection = Button::NEWGAME;
			}
			else if (i == 1)
			{
				currentSelection = Button::CHAPTERSELECT;
			}
			else
			{
				currentSelection = Button::EXIT;
			}
		}
		else 
		{
			buttons[i]->SetTexture("Texture2D/button0004.png");
			buttons[i]->SetColor(82, 46, 61);
			buttons[i]->SetScale({ 1.f, 1.f });
			buttonTexts[i]->SetColor(82, 46, 61);
		}
	}

}

void TitleScene::Update(float dt)
{
	Scene::Update(dt);
	chapter = dynamic_cast<Chapter*>(SCENE_MGR.GetCurrentScene());

	float backgroundSpeed = 50.f;

	sf::Vector2f newBGPos1 = background1->GetPosition();
	newBGPos1.x += backgroundSpeed * dt;
	background1->SetPosition(newBGPos1);

	sf::Vector2f newBGPos2 = background2->GetPosition();
	newBGPos2.x += backgroundSpeed * dt;
	background2->SetPosition(newBGPos2);

	if (newBGPos1.x > (float)FRAMEWORK.GetWindowSize().x)
	{
		background1->SetPosition({ -(float)FRAMEWORK.GetWindowSize().x, newBGPos1.y});
	}
	if (newBGPos2.x > (float)FRAMEWORK.GetWindowSize().x)
	{
		background2->SetPosition({ -(float)FRAMEWORK.GetWindowSize().x, newBGPos2.y });
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::S)) 
	{
		SOUND_MGR.PlaySfx("AudioClip/button_chapter_highlight_01.wav");
		currentButtonIndex = (currentButtonIndex + 1) % buttons.size();
		UpdateButtonStates();
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::W))
	{
		SOUND_MGR.PlaySfx("AudioClip/button_chapter_highlight_01.wav");
		currentButtonIndex = (currentButtonIndex - 1 + buttons.size()) % buttons.size();
		UpdateButtonStates();
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		switch (currentSelection)
		{
		case Button::NEWGAME:
			transition->SetChangeScene(SceneIds::CHAPTER);
			transition->PlayTransitionUp();
			break;
		case Button::CHAPTERSELECT:
			SOUND_MGR.PlaySfx("AudioClip/button_menu_confirm_01.wav");
			break;
		case Button::EXIT:
			FRAMEWORK.GameClose();
			break;
		default:
			break;
		}
	}
}

void TitleScene::Draw(sf::RenderWindow& window)
{
	window.draw(backColor);
	Scene::Draw(window);
}
