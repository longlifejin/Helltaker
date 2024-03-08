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
	//TO-DO : ��� �����̵��� �����ϱ�
	background = new SpriteGo("Background");
	background->SetTexture("Sprite/dialogueBG_abyss.png");
	background->SetOrigin(Origins::TC);
	background->SetPosition({ (float)(FRAMEWORK.GetWindowSize().x * 0.5), 180.f }); //��ġ ��� �κ� �̷��� ���ϴ� ����� ������?
	AddGo(background, Layers::Ui);

	beelzebub = new SpriteGo("Beelzebub");
	beelzebub->SetTexture("Sprite/beel_fly.png");
	beelzebub->SetOrigin(Origins::TC);
	beelzebub->SetPosition({ (float)(FRAMEWORK.GetWindowSize().x * 0.5), 0.f });
	AddGo(beelzebub, Layers::Ui);

	theGreatFly = new TextGo("TheGreatFly");
	theGreatFly->Set(fontResMgr.Get("Font/CrimsonPro-Medium.ttf"), "Beelzebub, The Great Fly", 40, sf::Color::Red); //�÷��� �ٸ��� �� �� �ִ� ����� ������?
	theGreatFly->SetOrigin(Origins::MC);
	theGreatFly->SetPosition({ (float)(FRAMEWORK.GetWindowSize().x * 0.5), (float)(FRAMEWORK.GetWindowSize().y * 0.5) + 200.f });
	AddGo(theGreatFly, Layers::Ui);





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

	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		//TO-DO : �ִϸ��̼� ����ϴ� ���� �ֱ�


		SCENE_MGR.ChangeScene(SceneIds::CHAPTER1);
	}
}
