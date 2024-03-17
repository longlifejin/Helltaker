#include "pch.h"
#include "CollectDemon.h"
#include "SpriteGo.h"
#include "TextGo.h"
#include "Chapter.h"
#include "Transition.h"

CollectDemon::CollectDemon(const std::string& name) : GameObject(name)
{
}

CollectDemon::~CollectDemon()
{
}

void CollectDemon::Init()
{
	step = 0;
	isBadEnd = false;
	isSuccess = false;

	sf::Vector2f windowSize = (sf::Vector2f)FRAMEWORK.GetWindowSize();

	backColor.setFillColor(sf::Color(2, 2, 27));
	backColor.setSize({ (float)FRAMEWORK.GetWindowSize().x, (float)FRAMEWORK.GetWindowSize().y });
	backColor.setOrigin({ 0.f,0.f });
	backColor.setPosition({ 0.f,0.f });

	float Offset = 50.f;
	float PosX = (float)FRAMEWORK.GetWindowSize().x * 0.5f;
	float PosY = (float)FRAMEWORK.GetWindowSize().y;

	background.SetTexture("Texture2D/collectDemonBG.png");
	background.SetOrigin(Origins::BC);
	background.SetPosition({ PosX, PosY * 0.7f - Offset });

	demon.SetTexture("Texture2D/pand_idle.png");
	demon.SetOrigin(Origins::BC);
	demon.SetPosition({ PosX,background.GetPosition().y + Offset });

	demonName.Set(fontEB, panName, 40, sf::Color(219, 72, 77));
	demonName.SetOrigin(Origins::TC);
	demonName.SetPosition({ PosX, demon.GetPosition().y - 40.f});

	demonLine.Set(fontR, pandLine1, 35, sf::Color::White);
	demonLine.SetOrigin(Origins::TC);
	demonLine.SetPosition({ PosX, demonName.GetPosition().y + Offset });

	demonLine2.Set(fontR, pandLine2, 35, sf::Color::White);
	demonLine2.SetOrigin(Origins::TC);
	demonLine2.SetPosition({ PosX, demonLine.GetPosition().y + 40.f });

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

	booper.setTexture((RES_MGR_TEXTURE.Get("Texture2D/booper0023.png")));
	booper.setOrigin({ booper.getLocalBounds().width * 0.5f, booper.getLocalBounds().height * 0.5f });
	booper.setPosition({ (float)FRAMEWORK.GetWindowSize().x * 0.5f, (float)FRAMEWORK.GetWindowSize().y * 0.85f });
	booper.setColor(sf::Color(219, 72, 77));
	booperAnimator.SetTarget(&booper);
	isBooperOn = true;

	badEnd.setTexture((RES_MGR_TEXTURE.Get("Texture2D/dialogueDeathExport0009.png")));
	badEnd.setOrigin({ badEnd.getLocalBounds().width * 0.5f, badEnd.getLocalBounds().height * 0.5f });
	badEnd.setPosition({ background.GetPosition().x,background.GetPosition().y - 300.f });
	badEndAnimator.SetTarget(&badEnd);

	success.setTexture((RES_MGR_TEXTURE.Get("Texture2D/success0007.png")));
	success.setOrigin({ success.getLocalBounds().width * 0.5f, success.getLocalBounds().height * 0.5f });
	success.setPosition({ demonLine2.GetPosition().x, demonLine2.GetPosition().y + 120.f });
	success.setScale({ 0.7f,0.7f });
	successAnimator.SetTarget(&success);

	background.SetActive(true);
	demon.SetActive(true);
	demonName.SetActive(true);
	wrongButton.SetActive(false);
	correctButton.SetActive(false);
	wrongText.SetActive(false);
	correctText.SetActive(false);
	
	currentSelect = SelectLine::Wrong;
	GameObject::Init();
}

void CollectDemon::Release()
{
	GameObject::Release();
}

void CollectDemon::Reset()
{
	GameObject::Reset();
	badEndAnimator.Play("Tables/badEnd.csv");
	badEnd.setOrigin({ badEnd.getLocalBounds().width * 0.5f, badEnd.getLocalBounds().height * 0.5f });
	successAnimator.Play("Tables/success.csv");
	success.setOrigin({ success.getLocalBounds().width * 0.5f, success.getLocalBounds().height * 0.5f });
	isBadEnd = false;
	isSuccess = false;
	booperAnimator.Play("Tables/booper.csv");
	isBooperOn = true;

	step = 0;
}

void CollectDemon::Update(float dt)
{
	GameObject::Update(dt);
	badEndAnimator.Update(dt);
	successAnimator.Update(dt);
	booperAnimator.Update(dt);

	chapter = dynamic_cast<Chapter*>(SCENE_MGR.GetCurrentScene());

	if (InputMgr::GetKeyDown(sf::Keyboard::R))
	{
		this->SetActive(false);
		this->Init();
		SCENE_MGR.ChangeScene(SceneIds::CHAPTER);
	}

	switch (chapter->GetCurrentStage())
	{
	case 1:
		Stage1();
		break;
	case 2:
		Stage2();
		break;
	default:
		Develop();
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

void CollectDemon::Stage1()
{
	switch (step)
	{
	case 0:
		booperAnimator.Play("Tables/booper.csv");
		++step;
		break;
	case 1:
		if (InputMgr::GetKeyDown(sf::Keyboard::Space))
		{
			++step;
		}
		break;
	case 2:
		wrongButton.SetActive(true);
		wrongText.SetActive(true);
		correctButton.SetActive(true);
		correctText.SetActive(true);
		isBooperOn = false;
		++step;
		break;
	case 3:
		if (InputMgr::GetKeyDown(sf::Keyboard::W) || InputMgr::GetKeyDown(sf::Keyboard::S))
		{
			Select();
		}

		if (InputMgr::GetKeyDown(sf::Keyboard::Space))
		{
			wrongButton.SetActive(false);
			wrongText.SetActive(false);
			correctButton.SetActive(false);
			correctText.SetActive(false);
			++step;
		}
		break;
	case 4:
		switch (currentSelect)
		{
		case CollectDemon::SelectLine::Correct:
			isSuccess = true;
			successAnimator.Play("Tables/success.csv");
			demonLine.SetString(L"참 달콤한 제안이에요. 커피를 마시고 싶네요.");
			demonLine2.SetString(L"피곤해서 정신을 못 차리겠어요.");
			demon.SetTexture("Texture2D/pand_flust.png");
			isBooperOn = false;
			break;
		case CollectDemon::SelectLine::Wrong:
			isBooperOn = true;
			booperAnimator.Play("Tables/booper.csv");
			demonLine.SetString(L"지옥을 살아서 나갈 생각을 한거야? 망상도 심하셔라.");
			demonLine2.SetActive(false);
			break;
		}
		++step;
		break;
	case 5:
		if (InputMgr::GetKeyDown(sf::Keyboard::Space))
		{
			isSuccess = false;
			isBooperOn = false;
			++step;
		}
		break;
	case 6:
		switch (currentSelect)
		{
		case CollectDemon::SelectLine::Correct:
			isAnswerSelect = true;
			this->SetActive(false);
			this->Release();
			this->Init();
			this->Reset();
			isSuccess = false;
			break;
		case CollectDemon::SelectLine::Wrong:
			isBadEnd = true;
			badEndAnimator.Play("Tables/badEnd.csv");
			demon.SetActive(false);
			background.SetActive(false);
			demonName.SetActive(false);
			isBooperOn = false;
			demonLine.Set(fontEB, L"그녀의 전문적인 친절함이 담긴 손길로 당신의 얼굴을 잡고", 35, sf::Color::Red);
			demonLine2.Set(fontEB, L"목을 비틀어 버렸습니다.", 35, sf::Color::Red);
			demonLine2.SetActive(true);
			break;
		}
		++step;
		break;
	case 7:
		if (InputMgr::GetKeyDown(sf::Keyboard::Space))
		{
			isBadEnd = false;
			chapter->transition->SetChangeScene(SceneIds::CHAPTER);
			chapter->transition->PlayTransitionUp();
			++step;
		}
		break;
	case 8:
		this->SetActive(false);
		this->Release();
		this->Init();
		this->Reset();
		break;
	default:
		break;
	}
}

void CollectDemon::Stage2()
{
	isAnswerSelect = false;

	switch (step)
	{
	case 0:
		demonLine.SetActive(true);
		demonLine2.SetActive(true);
		demon.SetTexture("Texture2D/mod_idle.png");
		demonName.SetString(L"● 색욕의 악마, 모데우스 ●");
		demonLine.SetString(L"너랑 나랑, 지금 당장 하자.");
		demonLine2.SetString(L"");
		booperAnimator.Play("Tables/booper.csv");
		++step;
		break;
	case 1:
		if (InputMgr::GetKeyDown(sf::Keyboard::Space))
		{
			++step;
		}
		break;
	case 2:
		wrongText.SetString(L"좋아. 물어볼 필요도 없지.");
		correctText.SetString(L"그럴 시간 없어. 여자들 모으느라 바빠.");
		wrongButton.SetActive(true);
		wrongText.SetActive(true);
		correctButton.SetActive(true);
		correctText.SetActive(true);
		isBooperOn = false;
		++step;
		break;
	case 3:
		if (InputMgr::GetKeyDown(sf::Keyboard::W) || InputMgr::GetKeyDown(sf::Keyboard::S))
		{
			Select();
		}

		if (InputMgr::GetKeyDown(sf::Keyboard::Space))
		{
			wrongButton.SetActive(false);
			wrongText.SetActive(false);
			correctButton.SetActive(false);
			correctText.SetActive(false);
			++step;
		}
		break;
	case 4:
		switch (currentSelect)
		{
		case CollectDemon::SelectLine::Correct:
			isSuccess = true;
			successAnimator.Play("Tables/success.csv");
			demon.SetTexture("Texture2D/mod_close.png");
			demonLine.SetString(L"악마 하렘? 가여워라... 다들 네 영혼을 찢으려 들텐데, 이건");
			demonLine2.SetString(L"'꼭'봐야겠다.");
			demonLine2.SetActive(true);
			isBooperOn = false;
			break;
		case CollectDemon::SelectLine::Wrong:
			isBooperOn = true;
			booperAnimator.Play("Tables/booper.csv");
			demonLine.SetString(L"다들 처음엔 그러더라... 그리고 결국 도망가려 하던데.");
			demonLine2.SetString(L"혹시 모르니, 다리를 부러뜨려 놔야겠다.");
			demonLine2.SetActive(true);
			break;
		}
		++step;
		break;
	case 5:
		if (InputMgr::GetKeyDown(sf::Keyboard::Space))
		{
			isSuccess = false;
			isBooperOn = false;
			++step;
		}
		break;
	case 6:
		switch (currentSelect)
		{
		case CollectDemon::SelectLine::Correct:
			isAnswerSelect = true;
			this->SetActive(false);
			this->Release();
			this->Init();
			isSuccess = false;
			break;
		case CollectDemon::SelectLine::Wrong:
			isBadEnd = true;
			badEndAnimator.Play("Tables/badEnd.csv");
			demon.SetActive(false);
			background.SetActive(false);
			demonName.SetActive(false);
			isBooperOn = false;
			demonLine.Set(fontEB, L"그녀는 쇠망치를 꺼내 들었습니다. 보기 좋게 끝날 것 같지는", 35, sf::Color::Red);
			demonLine2.Set(fontEB, L"않네요.", 35, sf::Color::Red);
			demonLine2.SetPosition({ (float)FRAMEWORK.GetWindowSize().x-700.f, demonLine.GetPosition().y + 40.f });
			demonLine2.SetActive(true);
			break;
		}
		++step;
		break;
	case 7:
		if (InputMgr::GetKeyDown(sf::Keyboard::Space))
		{
			isBadEnd = false;
			chapter->transition->SetChangeScene(SceneIds::CHAPTER);
			chapter->transition->PlayTransitionUp();
			++step;
		}
		break;
	case 8:
		this->SetActive(false);
		this->Release();
		this->Init();
		break;
	default:
		break;
	}
}

void CollectDemon::Develop()
{
	switch (step)
	{
	case 0:
		//demon.SetTexture("Sprite/beel_fly.png");
		demonName.SetString(L"● 지친 개발자 ●");
		demonLine.SetString(L"이 페이지는 아직 작업중이야.");
		demonLine2.SetString(L"");
		booperAnimator.Play("Tables/booper.csv");
		++step;
	case 1:
		if (InputMgr::GetKeyDown(sf::Keyboard::Space))
		{
			++step;
		}
		break;
	case 2:
		demonLine.SetString(L"일단 다음 맵은 보여주도록 하지.");
		booperAnimator.Play("Tables/booper.csv");
		++step;
	case 3:
		if (InputMgr::GetKeyDown(sf::Keyboard::Space))
		{
			++step;
		}
		break;
	case 4:
		isAnswerSelect = true;
		this->SetActive(false);
		this->Release();
		this->Init();
		isSuccess = false;
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
	if (isBooperOn) { window.draw(booper); }
	if (isSuccess) { window.draw(success); }
	if (isBadEnd) { window.draw(badEnd); }
}
