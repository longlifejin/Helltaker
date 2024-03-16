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
		demonLine.SetString(L"���� �Ϳ��� �Ǹ��� ã���� �������� ����.");
		booperAnimator.Play("Tables/booper.csv");
		++step;
	case 3:
		if (InputMgr::GetKeyDown(sf::Keyboard::Space))
		{
			++step;
		}
		break;
	case 4:
		demonLine.SetString(L"���� �󸶳� �Ϳ��� �������� �𸣰�����, �� �׳�");
		demonLine2.SetString(L"�������;�.");
		booperAnimator.Play("Tables/booper.csv");
		++step;
	case 5:
		if (InputMgr::GetKeyDown(sf::Keyboard::Space))
		{
			++step;
		}
		break;
	case 6:
		demonLine.SetString(L"�Ϸ��� ���� ä�︸�� �ư������� ���ؼ� �� ���� ������ ä��");
		demonLine2.SetString(L"�� ������ ���ֵ��� �����������.");
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
		demonName.SetString(L"�� ��ģ �Ǹ�, �ǵ����ī ��");
		demonLine.SetString(L"������ ���� �ٴ� �迡, �� ���̳� �ؾ߰ڳ׿�.");
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
		demonLine.SetString(L"������ ���ƴٴϸ鼭 �������� ���� �Ҹ�Ǵ� �� ����������?");
		demonLine2.SetString(L"�������� �������� �� �������ٸ�, ���� �������.");
		booperAnimator.Play("Tables/booper.csv");
		++step;
	case 3:
		if (InputMgr::GetKeyDown(sf::Keyboard::Space))
		{
			++step;
		}
		break;
	case 4:
		demonLine.SetString(L"���ù� ���� �ɾ� �ٴ� ���� �������� 2��� �Ҹ� �� �ſ���.");
		demonLine2.SetString(L"���� �˷��帮�ڸ� ���ù翡 �ִ� �ð��� �ּ�������");
		booperAnimator.Play("Tables/booper.csv");
		++step;
	case 5:
		if (InputMgr::GetKeyDown(sf::Keyboard::Space))
		{
			++step;
		}
		break;
	case 6:
		demonLine.SetString(L"������ �� ���� ���͸� �̿��� �ּż� �����մϴ�.");
		demonLine2.SetString(L"");
		booperAnimator.Play("Tables/booper.csv");
		++step;
		break;
	case 7:
		demonLine.SetString(L"������ �� ���� ���͸� �̿��� �ּż� �����մϴ�.");
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
		demonName.SetString(L"�� ��ģ ������ ��");
		demonLine.SetString(L"�� �������� ���� �۾����̾�.");
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
		demonLine.SetString(L"�� �Ѱܺ��� �����°� ���ٳ�.");
		booperAnimator.Play("Tables/booper.csv");
		++step;
	case 3:
		if (InputMgr::GetKeyDown(sf::Keyboard::Space))
		{
			++step;
		}
		break;
	case 4:
		demonLine.SetString(L"���� �Ƿ��� Ű���� ���ƿ��ڳ�.");
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
