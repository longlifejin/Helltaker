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
	theGreatFly->Set(fontResMgr.Get("Font/CrimsonPro-Medium.ttf"), "Beelzebub, The Great Fly", 40, sf::Color::Red); //컬러를 다르게 줄 수 있는 방법은 없을까?
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
		//TO-DO : 애니메이션 재생하는 내용 넣기


		SCENE_MGR.ChangeScene(SceneIds::CHAPTER1);
	}
}
