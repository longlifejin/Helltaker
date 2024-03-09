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

	demonLine1 = new TextGo("DemonLine");
	demonLine1->Set(fontResMgr.Get("Font/NanumSquareR.otf"), pandLine1, 30, sf::Color::White);
	demonLine1->SetOrigin(Origins::TC);
	demonLine1->SetPosition({ demonName->GetPosition().x, demonName->GetPosition().y + Offset });
	AddGo(demonLine1, Layers::Ui);

	demonLine2 = new TextGo("DemonLine");
	demonLine2->Set(fontResMgr.Get("Font/NanumSquareR.otf"), pandLine2, 30, sf::Color::White);
	demonLine2->SetOrigin(Origins::TC);
	demonLine2->SetPosition({ demonLine1->GetPosition().x, demonLine1->GetPosition().y + 30.f });
	AddGo(demonLine2, Layers::Ui);

	float buttonOffset = 90.f;

	select1 = new SpriteGo("NewGameButton");
	select1->SetTexture("Texture2D/button0003.png");
	select1->SetOrigin(Origins::MC);
	select1->SetPosition({ demonLine2->GetPosition().x, demonLine2->GetPosition().y + 100.f});
	select1->SetScale({ 1.1f, 1.1f });
	select1->SetColor(219, 72, 77);
	select1->SetActive(false);
	AddGo(select1, Layers::Ui);

	select2 = new SpriteGo("ChapterSelectButton");
	select2->SetTexture("Texture2D/button0004.png");
	select2->SetOrigin(Origins::MC);
	select2->SetPosition({ select1->GetPosition().x, select1->GetPosition().y + buttonOffset });
	select2->SetColor(82, 46, 61);
	select1->SetActive(true);
	AddGo(select2, Layers::Ui);

	booper = new SpriteGo("Booper");
	booper->SetTexture("Texture2D/booper0023.png");
	booper->SetOrigin(Origins::MC);
	booper->SetPosition({ (float)FRAMEWORK.GetWindowSize().x * 0.5f, (float)FRAMEWORK.GetWindowSize().y * 0.95f });
	booper->SetColor(219, 72, 77);
	AddGo(booper, Layers::Ui);

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

	if (InputMgr::GetKeyDown(sf::Keyboard::Space));
	{
		switch (currentSelect)
		{
		case CollectDemon::SelectLine::Correct:
			//success출력
			break;
		case CollectDemon::SelectLine::Wrong:
			//game over출력
			break;
		default:
			break;
		}
	}

}

void CollectDemon::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
