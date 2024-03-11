#include "pch.h"
#include "CollectDemon.h"
#include "SpriteGo.h";
#include "TextGo.h"

CollectDemon::CollectDemon(SceneIds id)
	:Scene(id)
{
}

CollectDemon::~CollectDemon()
{
}

void CollectDemon::Init()
{
	float Offset = 50.f;

	background = new SpriteGo("Background");
	background->SetTexture("Texture2D/collectDemonBG.png");
	background->SetOrigin(Origins::BC);
	background->SetPosition({ (float)FRAMEWORK.GetWindowSize().x * 0.5f, (float)FRAMEWORK.GetWindowSize().y * 0.7f - Offset });
	AddGo(background, Layers::Ui);

	demon = new SpriteGo("Demon");
	demon->SetTexture("Texture2D/pand_idle.png");
	demon->SetOrigin(Origins::BC);
	demon->SetPosition(background->GetPosition());
	AddGo(demon, Layers::Ui);

	demonName = new TextGo("DemonName");
	demonName->Set(fontResMgr.Get("Font/NanumSquareEB.otf"), panName, 40, sf::Color(219, 72, 77));
	demonName->SetOrigin(Origins::TC);
	demonName->SetPosition({ demon->GetPosition().x, demon->GetPosition().y + 20.f});
	AddGo(demonName, Layers::Ui);

	demonLine = new TextGo("DemonLine");
	demonLine->Set(fontResMgr.Get("Font/NanumSquareR.otf"), pandLine1, 30, sf::Color::White);
	demonLine->SetOrigin(Origins::TC);
	demonLine->SetPosition({ demonName->GetPosition().x, demonName->GetPosition().y + Offset });
	AddGo(demonLine, Layers::Ui);

	demonLine2 = new TextGo("DemonLine");
	demonLine2->Set(fontResMgr.Get("Font/NanumSquareR.otf"), pandLine2, 30, sf::Color::White);
	demonLine2->SetOrigin(Origins::TC);
	demonLine2->SetPosition({ demonLine->GetPosition().x, demonLine->GetPosition().y + 30.f });
	AddGo(demonLine2, Layers::Ui);

	float buttonOffset = 90.f;

	wrongButton = new SpriteGo("WrongButton");
	wrongButton->SetTexture("Texture2D/button0003.png");
	wrongButton->SetOrigin(Origins::MC);
	wrongButton->SetPosition({ demonLine2->GetPosition().x, demonLine2->GetPosition().y + 100.f});
	wrongButton->SetScale({ 1.1f, 1.1f });
	wrongButton->SetColor(219, 72, 77);
	AddGo(wrongButton, Layers::Ui);

	correctButton = new SpriteGo("CorrectButton");
	correctButton->SetTexture("Texture2D/button0004.png");
	correctButton->SetOrigin(Origins::MC);
	correctButton->SetPosition({ wrongButton->GetPosition().x, wrongButton->GetPosition().y + buttonOffset });
	correctButton->SetColor(82, 46, 61);
	AddGo(correctButton, Layers::Ui);

	wrongText = new TextGo("WrongText");
	wrongText->Set(fontResMgr.Get("Font/NanumSquareR.otf"), wrongLine, 25, sf::Color::White);
	wrongText->SetOrigin(Origins::MC);
	wrongText->SetPosition({ wrongButton->GetPosition().x, wrongButton->GetPosition().y -10.f });
	AddGo(wrongText, Layers::Ui);

	correctText = new TextGo("CorrectText");
	correctText->Set(fontResMgr.Get("Font/NanumSquareR.otf"), correctLine, 25, sf::Color::White);
	correctText->SetOrigin(Origins::MC);
	correctText->SetPosition({ correctButton->GetPosition().x, correctButton->GetPosition().y - 10.f });
	AddGo(correctText, Layers::Ui);

	booper = new SpriteGo("Booper");
	booper->SetTexture("Texture2D/booper0023.png");
	booper->SetOrigin(Origins::MC);
	booper->SetPosition({ (float)FRAMEWORK.GetWindowSize().x * 0.5f, (float)FRAMEWORK.GetWindowSize().y * 0.95f });
	booper->SetColor(219, 72, 77);
	AddGo(booper, Layers::Ui);

	wrongButton->SetActive(false);
	wrongText->SetActive(false);
	correctText->SetActive(false);
	correctButton->SetActive(false);
	booper->SetActive(true);

	Scene::Init();
}

void CollectDemon::Release()
{
	Scene::Release();
}

void CollectDemon::Enter()
{
	sf::Vector2f windowSize = (sf::Vector2f)FRAMEWORK.GetWindowSize();
	worldView.setSize(windowSize);
	worldView.setCenter(windowSize * 0.5f);
	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);

	Scene::Enter();
}

void CollectDemon::Exit()
{
	Scene::Exit();
}

void CollectDemon::Update(float dt)
{
	Scene::Update(dt);

	if (!isSelectTime && InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		wrongButton->SetActive(true);
		wrongText->SetActive(true);
		correctButton->SetActive(true);
		correctText->SetActive(true);
		booper->SetActive(false);

		isSelectTime = true;
	}

	if(isSelectTime)
	{
		if (InputMgr::GetKeyDown(sf::Keyboard::W) || InputMgr::GetKeyDown(sf::Keyboard::S))
		{
			Select();
		}

		if (InputMgr::GetKeyDown(sf::Keyboard::Space))
		{
			wrongButton->SetActive(false);
			wrongText->SetActive(false);
			correctButton->SetActive(false);
			correctText->SetActive(false);
			booper->SetActive(true);

			switch (currentSelect)
			{
			case CollectDemon::SelectLine::Correct:
				demonLine->SetString(L"참 달콤한 제안이에요. 커피를 마시고 싶네요.");
				demonLine2->SetString(L"피곤해서 정신을 못 차리겠어요.");
				demon->SetTexture("Texture2D/pand_flust.png");
				isSelectTime = false;
				isBadEnd = false;
				isSuccess = true;
				break;
			case CollectDemon::SelectLine::Wrong:
				demonLine->SetString(L"지옥을 살아서 나갈 생각을 한거야? 망상도 심하셔라.");
				demonLine2->SetActive(false);
				isSelectTime = false;
				isBadEnd = true;
				isSuccess = false;
				break;
			default:
				break;
			}
		}
	}

	if (!isSelectTime && isBadEnd)
	{
		//space누르면 bad end장면 출력
		isBadEnd = false;
	}

	if (!isSelectTime && isSuccess)
	{
		//space누르면 success장면 출력
		isSuccess = false;
	}
}

void CollectDemon::Select()
{
	switch (currentSelect)
	{
	case CollectDemon::SelectLine::Wrong:
		currentSelect = SelectLine::Correct;
		correctButton->SetTexture("Texture2D/button0003.png");
		correctButton->SetColor(219, 72, 77);
		correctButton->SetScale({ 1.1f,1.1f });

		wrongButton->SetTexture("Texture2D/button0004.png");
		wrongButton->SetColor(82, 46, 61);
		wrongButton->SetScale({ 1.f,1.f });
		break;
	case CollectDemon::SelectLine::Correct:
		currentSelect = SelectLine::Wrong;
		correctButton->SetTexture("Texture2D/button0004.png");
		correctButton->SetColor(82, 46, 61);
		correctButton->SetScale({ 1.f,1.f });

		wrongButton->SetTexture("Texture2D/button0003.png");
		wrongButton->SetColor(219, 72, 77);
		wrongButton->SetScale({ 1.1f,1.1f });
		break;
	default:
		break;
	}
}

void CollectDemon::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
