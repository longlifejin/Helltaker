#include "pch.h"
#include "TitleScene.h"

TitleScene::TitleScene(SceneIds id)
	: Scene(id)
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Init()
{
	//TO-DO : 배경 움직이도록 수정하기
	background = new SpriteGo("Background");
	background->SetTexture("Sprite/dialogueBG_abyss.png");
	background->SetOrigin(Origins::TC);
	background->SetPosition({ (float)(FRAMEWORK.GetWindowSize().x * 0.5), 170.f }); //위치 잡는 부분 이렇게 안하는 방법이 있을까?
	AddGo(background, Layers::Ui);

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
	chapterSelectText->Set(fontResMgr.Get("Font/NanumSquareR.otf"), chaterSelect, 30, sf::Color::White);
	chapterSelectText->SetOrigin(Origins::MC);
	chapterSelectText->SetPosition({ newGameText->GetPosition().x, newGameText->GetPosition().y + buttonOffset });
	AddGo(chapterSelectText, Layers::Ui);

	exitText = new TextGo("ExitText");
	exitText->Set(fontResMgr.Get("Font/NanumSquareR.otf"), exit, 30, sf::Color::White);
	exitText->SetOrigin(Origins::MC);
	exitText->SetPosition({ chapterSelectText->GetPosition().x, chapterSelectText->GetPosition().y + buttonOffset });
	AddGo(exitText, Layers::Ui);

	Scene::Init();
}

void TitleScene::Release()
{
	Scene::Release();
}

void TitleScene::Enter()
{
	sf::Vector2f windowSize = (sf::Vector2f)FRAMEWORK.GetWindowSize();
	worldView.setSize(windowSize);
	worldView.setCenter(windowSize * 0.5f);
	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);

	Scene::Enter();
}

void TitleScene::Exit()
{
	Scene::Exit();
}

void TitleScene::Update(float dt)
{
	Scene::Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::S))
	{

		switch (currentSelection)
		{
		case TitleScene::Button::NEWGAME:
			currentSelection = Button::CHAPTERSELECT;

			newGameButton->SetTexture("Texture2D/button0004.png");
			newGameButton->SetColor(82, 46, 61);
			newGameButton->SetScale({ 1.f,1.f });

			chapterSelectButton->SetTexture("Texture2D/button0003.png");
			chapterSelectButton->SetColor(219, 72, 77);
			chapterSelectButton->SetScale({ 1.1f,1.1f });

			exitButton->SetTexture("Texture2D/button0004.png");
			exitButton->SetColor(82, 46, 61);
			exitButton->SetScale({ 1.f,1.f });
			break;
		case TitleScene::Button::CHAPTERSELECT:
			currentSelection = Button::EXIT;

			newGameButton->SetTexture("Texture2D/button0004.png");
			newGameButton->SetColor(82, 46, 61);
			newGameButton->SetScale({ 1.f,1.f });

			chapterSelectButton->SetTexture("Texture2D/button0004.png");
			chapterSelectButton->SetColor(82, 46, 61);
			chapterSelectButton->SetScale({ 1.f,1.f });

			exitButton->SetTexture("Texture2D/button0003.png");
			exitButton->SetColor(219, 72, 77);
			exitButton->SetScale({ 1.1f,1.1f });
			break;
		case TitleScene::Button::EXIT:
			currentSelection = Button::NEWGAME;

			newGameButton->SetTexture("Texture2D/button0003.png");
			newGameButton->SetColor(219, 72, 77);
			newGameButton->SetScale({ 1.1f,1.1f });

			chapterSelectButton->SetTexture("Texture2D/button0004.png");
			chapterSelectButton->SetColor(82, 46, 61);
			chapterSelectButton->SetScale({ 1.f,1.f });

			exitButton->SetTexture("Texture2D/button0004.png");
			exitButton->SetColor(82, 46, 61);
			exitButton->SetScale({ 1.f,1.f });
			break;
		default:
			break;
		}
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::W))
	{
		switch (currentSelection)
		{
		case Button::NEWGAME:
			currentSelection = Button::EXIT;

			newGameButton->SetTexture("Texture2D/button0004.png");
			newGameButton->SetColor(82, 46, 61);
			newGameButton->SetScale({ 1.f,1.f });

			chapterSelectButton->SetTexture("Texture2D/button0004.png");
			chapterSelectButton->SetColor(82, 46, 61);
			chapterSelectButton->SetScale({ 1.f,1.f });

			exitButton->SetTexture("Texture2D/button0003.png");
			exitButton->SetColor(219, 72, 77);
			exitButton->SetScale({ 1.1f,1.1f });
			break;
		case Button::CHAPTERSELECT:
			currentSelection = Button::NEWGAME;

			newGameButton->SetTexture("Texture2D/button0004.png");
			newGameButton->SetColor(219, 72, 77);
			newGameButton->SetScale({ 1.1f,1.1f });

			chapterSelectButton->SetTexture("Texture2D/button0003.png");
			chapterSelectButton->SetColor(82, 46, 61);
			chapterSelectButton->SetScale({ 1.f,1.f });

			exitButton->SetTexture("Texture2D/button0004.png");
			exitButton->SetColor(82, 46, 61);
			exitButton->SetScale({ 1.f,1.f });
			break;
		case Button::EXIT:
			currentSelection = Button::CHAPTERSELECT;

			newGameButton->SetTexture("Texture2D/button0004.png");
			newGameButton->SetColor(82, 46, 61);
			newGameButton->SetScale({ 1.f,1.f });

			chapterSelectButton->SetTexture("Texture2D/button0003.png");
			chapterSelectButton->SetColor(219, 72, 77);
			chapterSelectButton->SetScale({ 1.1f,1.1f });

			exitButton->SetTexture("Texture2D/button0004.png");
			exitButton->SetColor(82, 46, 61);
			exitButton->SetScale({ 1.f,1.f });
			break;
		default:
			break;
		}
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		switch (currentSelection)
		{
		case Button::NEWGAME:
			SCENE_MGR.ChangeScene(SceneIds::CHAPTER1);
			break;
		case Button::CHAPTERSELECT:
			//chapter select 화면으로 이동
			break;
		case Button::EXIT:
			//게임 종료 화면
			break;
		default:
			break;
		}
	}
}
