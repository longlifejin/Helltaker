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
	background->SetPosition({ (float)(FRAMEWORK.GetWindowSize().x * 0.5), 180.f }); //위치 잡는 부분 이렇게 안하는 방법이 있을까?
	AddGo(background, Layers::Ui);

	beelzebub = new SpriteGo("Beelzebub");
	beelzebub->SetTexture("Sprite/beel_fly.png");
	beelzebub->SetOrigin(Origins::TC);
	beelzebub->SetPosition({ (float)(FRAMEWORK.GetWindowSize().x * 0.5), 0.f });
	AddGo(beelzebub, Layers::Ui);

	theGreatFly = new TextGo("TheGreatFly");
	theGreatFly->Set(fontResMgr.Get("Font/CrimsonPro-ExtraBold.ttf"), "Beelzebub, The Great Fly", 40, sf::Color::Red); //컬러를 다르게 줄 수 있는 방법은 없을까?
	theGreatFly->SetOrigin(Origins::MC);
	theGreatFly->SetPosition({ (float)(FRAMEWORK.GetWindowSize().x * 0.5), (float)(FRAMEWORK.GetWindowSize().y * 0.5) + 200.f });
	AddGo(theGreatFly, Layers::Ui);

	float circleOffset = 40.f;

	/*whiteCircle = new SpriteGo("WhiteCircle");
	whiteCircle->SetScale({ 0.1f,0.1f });
	whiteCircle->SetOrigin(Origins::MC);
	whiteCircle->SetPosition({ theGreatFly->GetGlobalBounds().left - circleOffset, 
		(theGreatFly->GetGlobalBounds().top + theGreatFly->GetGlobalBounds().height)});
	whiteCircle->SetTexture("Texture2D/whiteCircle.png");
	AddGo(whiteCircle, Layers::Ui);*/


	float buttonOffset = 90.f;

	newGameButton = new SpriteGo("NewGameButton");
	newGameButton->SetTexture("Texture2D/button0003.png");
	newGameButton->SetOrigin(Origins::MC);
	newGameButton->SetPosition({ (float)(FRAMEWORK.GetWindowSize().x * 0.5), (float)(FRAMEWORK.GetWindowSize().y * 0.5) + 300.f });
	newGameButton->SetScale({ 1.1f, 1.1f });
	AddGo(newGameButton, Layers::Ui);

	chapterSelectButton = new SpriteGo("ChapterSelectButton");
	chapterSelectButton->SetTexture("Texture2D/button0004.png");
	chapterSelectButton->SetOrigin(Origins::MC);
	chapterSelectButton->SetPosition( {newGameButton->GetPosition().x, newGameButton->GetPosition().y + buttonOffset});
	AddGo(chapterSelectButton, Layers::Ui);

	exitButton = new SpriteGo("ExitButton");
	exitButton->SetTexture("Texture2D/button0004.png");
	exitButton->SetOrigin(Origins::MC);
	exitButton->SetPosition({chapterSelectButton->GetPosition().x, chapterSelectButton->GetPosition().y + buttonOffset});
	AddGo(exitButton, Layers::Ui);

	float textOffset = 15.f;

	newGameText = new TextGo("NewGameText");
	newGameText->Set(fontResMgr.Get("Font/CrimsonPro-Medium.ttf"), "NEW GAME", 30, sf::Color::Red);
	newGameText->SetOrigin(Origins::MC);
	newGameText->SetPosition({ newGameButton->GetPosition().x, newGameButton->GetPosition().y -textOffset });
	AddGo(newGameText, Layers::Ui);

	chapterSelectText = new TextGo("ChapterSelectText");
	chapterSelectText->Set(fontResMgr.Get("Font/CrimsonPro-Medium.ttf"), "CHAPTER SELECT", 30, sf::Color::Red);
	chapterSelectText->SetOrigin(Origins::MC);
	chapterSelectText->SetPosition({ newGameText->GetPosition().x, newGameText->GetPosition().y + buttonOffset });
	AddGo(chapterSelectText, Layers::Ui);

	exitText = new TextGo("ExitText");
	exitText->Set(fontResMgr.Get("Font/CrimsonPro-Medium.ttf"), "EXIT", 30, sf::Color::Red);
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
			newGameButton->SetScale({ 1.f,1.f });
			chapterSelectButton->SetTexture("Texture2D/button0003.png");
			chapterSelectButton->SetScale({ 1.1f,1.1f });
			exitButton->SetTexture("Texture2D/button0004.png");
			exitButton->SetScale({ 1.f,1.f });
			break;
		case TitleScene::Button::CHAPTERSELECT:
			currentSelection = Button::EXIT;
			newGameButton->SetTexture("Texture2D/button0004.png");
			newGameButton->SetScale({ 1.f,1.f });
			chapterSelectButton->SetTexture("Texture2D/button0004.png");
			chapterSelectButton->SetScale({ 1.f,1.f });
			exitButton->SetTexture("Texture2D/button0003.png");
			exitButton->SetScale({ 1.1f,1.1f });
			break;
		case TitleScene::Button::EXIT:
			currentSelection = Button::NEWGAME;
			newGameButton->SetTexture("Texture2D/button0003.png");
			newGameButton->SetScale({ 1.1f,1.1f });
			chapterSelectButton->SetTexture("Texture2D/button0004.png");
			chapterSelectButton->SetScale({ 1.f,1.f });
			exitButton->SetTexture("Texture2D/button0004.png");
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
			newGameButton->SetScale({ 1.f,1.f });
			chapterSelectButton->SetTexture("Texture2D/button0004.png");
			chapterSelectButton->SetScale({ 1.f,1.f });
			exitButton->SetTexture("Texture2D/button0003.png");
			exitButton->SetScale({ 1.1f,1.1f });
			break;
		case Button::CHAPTERSELECT:
			currentSelection = Button::NEWGAME;
			newGameButton->SetTexture("Texture2D/button0003.png");
			newGameButton->SetScale({ 1.1f,1.1f });
			chapterSelectButton->SetTexture("Texture2D/button0004.png");
			chapterSelectButton->SetScale({ 1.f,1.f });
			exitButton->SetTexture("Texture2D/button0004.png");
			exitButton->SetScale({ 1.f,1.f });
			break;
		case Button::EXIT:
			currentSelection = Button::CHAPTERSELECT;
			newGameButton->SetTexture("Texture2D/button0004.png");
			newGameButton->SetScale({ 1.f,1.f });
			chapterSelectButton->SetTexture("Texture2D/button0003.png");
			chapterSelectButton->SetScale({ 1.1f,1.1f });
			exitButton->SetTexture("Texture2D/button0004.png");
			exitButton->SetScale({ 1.f,1.f });
			break;
		default:
			break;
		}

		//if (currentSelection == Button::NEWGAME)
		//{
		//	currentSelection = Button::EXIT;
		//	newGameButton->SetTexture("Texture2D/button0004.png");
		//	newGameButton->SetScale({ 1.f,1.f });
		//	chapterSelectButton->SetTexture("Texture2D/button0004.png");
		//	chapterSelectButton->SetScale({ 1.f,1.f });
		//	exitButton->SetTexture("Texture2D/button0003.png");
		//	exitButton->SetScale({ 1.1f,1.1f });
		//}
		//else if (currentSelection == Button::CHAPTERSELECT)
		//{
		//	currentSelection = Button::NEWGAME;
		//	newGameButton->SetTexture("Texture2D/button0003.png");
		//	newGameButton->SetScale({ 1.1f,1.1f });
		//	chapterSelectButton->SetTexture("Texture2D/button0004.png");
		//	chapterSelectButton->SetScale({ 1.f,1.f });
		//	exitButton->SetTexture("Texture2D/button0004.png");
		//	exitButton->SetScale({ 1.f,1.f });
		//}
		//else if (currentSelection == Button::EXIT)
		//{
		//	currentSelection = Button::CHAPTERSELECT;
		//	newGameButton->SetTexture("Texture2D/button0004.png");
		//	newGameButton->SetScale({ 1.f,1.f });
		//	chapterSelectButton->SetTexture("Texture2D/button0003.png");
		//	chapterSelectButton->SetScale({ 1.1f,1.1f });
		//	exitButton->SetTexture("Texture2D/button0004.png");
		//	exitButton->SetScale({ 1.f,1.f });
		//}
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
