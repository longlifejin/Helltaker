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
