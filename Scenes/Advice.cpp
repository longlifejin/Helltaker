#include "pch.h"
#include "Advice.h"
#include "Chapter.h"

Advice::Advice(const std::string& name)
	:GameObject(name)
{
}

Advice::~Advice()
{
}

void Advice::Init()
{
	step = 0;

	backColor.setFillColor(sf::Color(2, 2, 27));
	backColor.setSize({ (float)FRAMEWORK.GetWindowSize().x, (float)FRAMEWORK.GetWindowSize().y });
	backColor.setOrigin({ 0.f,0.f });
	backColor.setPosition({ 0.f,0.f });

	background.SetTexture("Texture2D/dialogueBG_hell.png");
	background.SetOrigin(Origins::BC);
	background.SetPosition({ (float)FRAMEWORK.GetWindowSize().x * 0.5f, (float)FRAMEWORK.GetWindowSize().y * 0.7f - Offset });

	demon.SetTexture("Sprite/beel_fly.png");
	demon.SetOrigin(Origins::BC);
	demon.SetPosition({ background.GetPosition().x,background.GetPosition().y + Offset });

	demonName.Set(fontEB, name, 40, sf::Color(219, 72, 77));
	demonName.SetOrigin(Origins::TC);
	demonName.SetPosition({ demon.GetPosition().x, demon.GetPosition().y - 40.f });

	demonLine.Set(fontR, Line1, 35, sf::Color::White);
	demonLine.SetOrigin(Origins::TC);
	demonLine.SetPosition({ demonName.GetPosition().x, demonName.GetPosition().y + Offset });

	demonLine2.Set(fontR, Line2, 35, sf::Color::White);
	demonLine2.SetOrigin(Origins::TC);
	demonLine2.SetPosition({ demonLine.GetPosition().x, demonLine.GetPosition().y + 40.f });

	booper.setTexture((RES_MGR_TEXTURE.Get("Texture2D/booper0023.png")));
	booper.setOrigin({ booper.getLocalBounds().width * 0.5f, booper.getLocalBounds().height * 0.5f });
	booper.setPosition({ (float)FRAMEWORK.GetWindowSize().x * 0.5f, (float)FRAMEWORK.GetWindowSize().y * 0.85f });
	booper.setColor(sf::Color(219, 72, 77));
	booperAnimator.SetTarget(&booper);
	isBooperOn = true;

	GameObject::Init();
}

void Advice::Release()
{
	GameObject::Release();
}

void Advice::Reset()
{
	GameObject::Reset();
	booperAnimator.Play("Tables/booper.csv");
}

void Advice::Update(float dt)
{
	GameObject::Update(dt);
	booperAnimator.Update(dt);

	chapter = dynamic_cast<Chapter*>(SCENE_MGR.GetCurrentScene());

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

void Advice::Stage1()
{
	switch (step)
	{
	case 0:
		booperAnimator.Play("Tables/booper.csv");
		++step;
	case 1:
		if (InputMgr::GetKeyDown(sf::Keyboard::Space))
		{
			++step;
		}
		break;
	case 2:
		demonLine.SetString(L"아직 귀여운 악마를 찾지도 못했으니 말야.");
		booperAnimator.Play("Tables/booper.csv");
		++step;
	case 3:
		if (InputMgr::GetKeyDown(sf::Keyboard::Space))
		{
			++step;
		}
		break;
	case 4:
		demonLine.SetString(L"내가 얼마나 귀여워 보일지는 모르겠지만, 난 그냥");
		demonLine2.SetString(L"나레이터야.");
		booperAnimator.Play("Tables/booper.csv");
		++step;
	case 5:
		if (InputMgr::GetKeyDown(sf::Keyboard::Space))
		{
			++step;
		}
		break;
	case 6:
		demonLine.SetString(L"하렘을 가득 채울만한 아가씨들을 구해서 그 쪽의 마음을 채워");
		demonLine2.SetString(L"줄 조언을 해주도록 괴롭혀보라고.");
		booperAnimator.Play("Tables/booper.csv");
		++step;
		break;
	case 7:
		if (InputMgr::GetKeyDown(sf::Keyboard::Space))
		{
			++step;
		}
		break;
	case 8:
		this->SetActive(false);
		chapter->SetAdvice(false);
		Release();
		Init();
	default:
		break;
	}
}

void Advice::Stage2()
{
	switch (step)
	{
	case 0:
		demon.SetTexture("Texture2D/pand_flust.png");
		demon.SetOrigin(Origins::BC);
		demon.SetPosition({ background.GetPosition().x + 700.f ,background.GetPosition().y + Offset });
		demonName.SetString(L"● 지친 악마, 판데모니카 ●");
		demonLine.SetString(L"어차피 같이 다닐 김에, 제 일이나 해야겠네요.");
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
		demon.SetTexture("Texture2D/pand_Idle.png");
		demonLine.SetString(L"지옥을 돌아다니면서 의지력이 많이 소모되는 건 느껴보셨죠?");
		demonLine2.SetString(L"지옥에서 의지력이 다 떨어진다면, 죽은 목숨이죠.");
		booperAnimator.Play("Tables/booper.csv");
		++step;
	case 3:
		if (InputMgr::GetKeyDown(sf::Keyboard::Space))
		{
			++step;
		}
		break;
	case 4:
		demonLine.SetString(L"가시밭 위를 걸어 다닐 때는 의지력이 2배로 소모 될 거에요.");
		demonLine2.SetString(L"굳이 알려드리자면 가시밭에 있는 시간을 최소한으로");
		booperAnimator.Play("Tables/booper.csv");
		++step;
	case 5:
		if (InputMgr::GetKeyDown(sf::Keyboard::Space))
		{
			++step;
		}
		break;
	case 6:
		demonLine.SetString(L"지옥의 고객 서비스 센터를 이용해 주셔서 감사합니다.");
		demonLine2.SetString(L"");
		booperAnimator.Play("Tables/booper.csv");
		++step;
		break;
	case 7:
		demonLine.SetString(L"지옥의 고객 서비스 센터를 이용해 주셔서 감사합니다.");
		demonLine2.SetString(L"");
		booperAnimator.Play("Tables/booper.csv");
		++step;
		break;
	case 8:
		if (InputMgr::GetKeyDown(sf::Keyboard::Space))
		{
			++step;
		}
		break;
	case 9:
		this->SetActive(false);
		chapter->SetAdvice(false);
		Release();
		Init();
	default:
		break;
	}
}

void Advice::Develop()
{
	switch (step)
	{
	case 0:
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
		demonLine.SetString(L"더 넘겨봤자 나오는건 없다네.");
		booperAnimator.Play("Tables/booper.csv");
		++step;
	case 3:
		if (InputMgr::GetKeyDown(sf::Keyboard::Space))
		{
			++step;
		}
		break;
	case 4:
		demonLine.SetString(L"개발 실력을 키워서 돌아오겠네.");
		demonLine2.SetString(L"");
		booperAnimator.Play("Tables/booper.csv");
		++step;
	case 5:
		if (InputMgr::GetKeyDown(sf::Keyboard::Space))
		{
			++step;
		}
		break; 
	case 6:
		this->SetActive(false);
		chapter->SetAdvice(false);
		Release();
		Init();
	default:
		break;
	}
}

void Advice::Draw(sf::RenderWindow& window)
{
	GameObject::Draw(window);
	window.draw(backColor);
	if (background.GetActive()) { background.Draw(window); }
	if (demon.GetActive()) { demon.Draw(window); }
	if (demonName.GetActive()) { demonName.Draw(window); }
	if (demonLine.GetActive()) { demonLine.Draw(window); }
	if (demonLine2.GetActive()) { demonLine2.Draw(window); }
	if (isBooperOn) { window.draw(booper); }
}
