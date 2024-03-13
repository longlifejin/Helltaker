#include "pch.h"
#include "CollectDemon.h"
#include "SpriteGo.h";
#include "TextGo.h"

CollectDemon::CollectDemon(const std::string& name) : GameObject(name)
{
}

CollectDemon::~CollectDemon()
{
}

void CollectDemon::Init()
{
	step = 0;

	sf::Vector2f windowSize = (sf::Vector2f)FRAMEWORK.GetWindowSize();

	backColor.setFillColor(sf::Color(2, 2, 27));
	backColor.setSize({ (float)FRAMEWORK.GetWindowSize().x, (float)FRAMEWORK.GetWindowSize().y });
	backColor.setOrigin({ 0.f,0.f });
	backColor.setPosition({ 0.f,0.f });

	float Offset = 50.f;

	background.SetTexture("Texture2D/collectDemonBG.png");
	background.SetOrigin(Origins::BC);
	background.SetPosition({ (float)FRAMEWORK.GetWindowSize().x * 0.5f, (float)FRAMEWORK.GetWindowSize().y * 0.7f - Offset });

	demon.SetTexture("Texture2D/pand_idle.png");
	demon.SetOrigin(Origins::BC);
	demon.SetPosition(background.GetPosition());

	demonName.Set(fontEB, panName, 40, sf::Color(219, 72, 77));
	demonName.SetOrigin(Origins::TC);
	demonName.SetPosition({ demon.GetPosition().x, demon.GetPosition().y + 20.f});

	demonLine.Set(fontR, pandLine1, 30, sf::Color::White);
	demonLine.SetOrigin(Origins::TC);
	demonLine.SetPosition({ demonName.GetPosition().x, demonName.GetPosition().y + Offset });

	demonLine2.Set(fontR, pandLine2, 30, sf::Color::White);
	demonLine2.SetOrigin(Origins::TC);
	demonLine2.SetPosition({ demonLine.GetPosition().x, demonLine.GetPosition().y + 30.f });

	float buttonOffset = 90.f;

	wrongButton.SetTexture("Texture2D/button0003.png");
	wrongButton.SetOrigin(Origins::MC);
	wrongButton.SetPosition({ demonLine2.GetPosition().x, demonLine2.GetPosition().y + 100.f});
	wrongButton.SetScale({ 1.1f, 1.1f });
	wrongButton.SetColor(219, 72, 77);

	correctButton.SetTexture("Texture2D/button0004.png");
	correctButton.SetOrigin(Origins::MC);
	correctButton.SetPosition({ wrongButton.GetPosition().x, wrongButton.GetPosition().y + buttonOffset });
	correctButton.SetColor(82, 46, 61);

	wrongText.Set(fontR, wrongLine, 25, sf::Color::White);
	wrongText.SetOrigin(Origins::MC);
	wrongText.SetPosition({ wrongButton.GetPosition().x, wrongButton.GetPosition().y -10.f });

	correctText.Set(fontR, correctLine, 25, sf::Color::White);
	correctText.SetOrigin(Origins::MC);
	correctText.SetPosition({ correctButton.GetPosition().x, correctButton.GetPosition().y - 10.f });

	booper.SetTexture("Texture2D/booper0023.png");
	booper.SetOrigin(Origins::MC);
	booper.SetPosition({ (float)FRAMEWORK.GetWindowSize().x * 0.5f, (float)FRAMEWORK.GetWindowSize().y * 0.95f });
	booper.SetColor(219, 72, 77);

	badEnd.SetTexture("Texture2D/dialogueDeathExport0009.png");
	badEnd.SetOrigin(Origins::BC);
	badEnd.SetPosition(demon.GetPosition());

	success.SetTexture("Texture2D/success0007.png");
	success.SetOrigin(Origins::MC);
	success.SetPosition({ demonLine2.GetPosition().x, demonLine2.GetPosition().y + 120.f });
	success.SetScale({ 0.7f,0.7f });


	background.SetActive(true);
	demon.SetActive(true);
	demonName.SetActive(true);
	wrongButton.SetActive(false);
	correctButton.SetActive(false);
	wrongText.SetActive(false);
	correctText.SetActive(false);
	booper.SetActive(true);
	badEnd.SetActive(false);
	success.SetActive(false);

	currentSelect = SelectLine::Wrong;
	//isAnswerSelect = false;

	GameObject::Init();
}

void CollectDemon::Release()
{
	GameObject::Release();
}

void CollectDemon::Update(float dt)
{
	GameObject::Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::R))
	{
		this->SetActive(false);
		this->Init();
		SCENE_MGR.ChangeScene(SceneIds::CHAPTER1);
	}

	switch (step)
	{
	case 0:
		if (InputMgr::GetKeyDown(sf::Keyboard::Space))
		{ ++step; }
		break;
	case 1:
		wrongButton.SetActive(true);
		wrongText.SetActive(true);
		correctButton.SetActive(true);
		correctText.SetActive(true);
		booper.SetActive(false);
		++step;
		break;
	case 2:
		if (InputMgr::GetKeyDown(sf::Keyboard::W) || InputMgr::GetKeyDown(sf::Keyboard::S))
		{ Select();	}

		if (InputMgr::GetKeyDown(sf::Keyboard::Space))
		{
			wrongButton.SetActive(false);
			wrongText.SetActive(false);
			correctButton.SetActive(false);
			correctText.SetActive(false);
			booper.SetActive(true);
			++step;
		}
		break;
	case 3:
		switch (currentSelect)
		{
		case CollectDemon::SelectLine::Correct:
			demonLine.SetString(L"참 달콤한 제안이에요. 커피를 마시고 싶네요.");
			demonLine2.SetString(L"피곤해서 정신을 못 차리겠어요.");
			demon.SetTexture("Texture2D/pand_flust.png");
			booper.SetActive(false);
			success.SetActive(true);

			if (InputMgr::GetKeyDown(sf::Keyboard::Space))
			{ ++step; }
			break;
		case CollectDemon::SelectLine::Wrong:
			demonLine.SetString(L"지옥을 살아서 나갈 생각을 한거야? 망상도 심하셔라.");
			demonLine2.SetActive(false);

			if (InputMgr::GetKeyDown(sf::Keyboard::Space))
			{ ++step; }
			break;
		default:
			break;
		}
		break;
	case 4:
		switch (currentSelect)
		{
		case CollectDemon::SelectLine::Correct:
			isAnswerSelect = true;
			this->SetActive(false);
			this->Release();
			this->Init();
			break;
		case CollectDemon::SelectLine::Wrong:
			badEnd.SetActive(true);
			demon.SetActive(false);
			background.SetActive(false);
			demonName.SetActive(false);
			booper.SetActive(false);
			demonLine.Set(fontEB, L"그녀의 전문적인 친절함이 담긴 손길로 당신의 얼굴을 잡고", 25, sf::Color::Red);
			demonLine2.Set(fontEB, L"목을 비틀어 버렸습니다.", 25, sf::Color::Red);
			demonLine2.SetActive(true);
			if (InputMgr::GetKeyDown(sf::Keyboard::Space))
			{ ++step; }
			break;
		}
		break;
	case 5:
		//게임 재시작
		this->SetActive(false);
		this->Release();
		this->Init();
		SCENE_MGR.ChangeScene(SceneIds::CHAPTER1);
		break;
	default:
		break;
	}
}

void CollectDemon::Select()
{
	switch (currentSelect)
	{
	case CollectDemon::SelectLine::Wrong:
		currentSelect = SelectLine::Correct;
		correctButton.SetTexture("Texture2D/button0003.png");
		correctButton.SetColor(219, 72, 77);
		correctButton.SetScale({ 1.1f,1.1f });

		wrongButton.SetTexture("Texture2D/button0004.png");
		wrongButton.SetColor(82, 46, 61);
		wrongButton.SetScale({ 1.f,1.f });
		break;
	case CollectDemon::SelectLine::Correct:
		currentSelect = SelectLine::Wrong;
		correctButton.SetTexture("Texture2D/button0004.png");
		correctButton.SetColor(82, 46, 61);
		correctButton.SetScale({ 1.f,1.f });

		wrongButton.SetTexture("Texture2D/button0003.png");
		wrongButton.SetColor(219, 72, 77);
		wrongButton.SetScale({ 1.1f,1.1f });
		break;
	default:
		break;
	}
}

void CollectDemon::Draw(sf::RenderWindow& window)
{
	window.draw(backColor);
	if (background.GetActive())	{ background.Draw(window); }
	if (demon.GetActive())	{ demon.Draw(window); }
	if (demonName.GetActive())	{ demonName.Draw(window); }
	if (demonLine.GetActive())	{ demonLine.Draw(window); }
	if (demonLine2.GetActive()) { demonLine2.Draw(window); }
	if (wrongButton.GetActive()) { wrongButton.Draw(window); }
	if (correctButton.GetActive()) { correctButton.Draw(window); }
	if (wrongText.GetActive()) { wrongText.Draw(window); }
	if (correctText.GetActive()) { correctText.Draw(window); }
	if (booper.GetActive()) { booper.Draw(window); }
	if (success.GetActive()) { success.Draw(window); }
	if (badEnd.GetActive()) { badEnd.Draw(window); }
}
