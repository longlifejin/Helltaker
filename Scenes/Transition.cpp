#include "pch.h"
#include "Transition.h"

Transition::Transition(const std::string& name)
	:SpriteGo(name)
{
}

Transition::~Transition()
{
}

void Transition::Init()
{
	SpriteGo::Init();
	SetOrigin(Origins::BC);
	animator.SetTarget(&sprite);

	//ó�� ����� �� ���� ���� �ذ��Ϸ��� �̸� load ����//
	RES_MGR_TEXTURE.Load("Sprite/transition0002.png");
	RES_MGR_TEXTURE.Load("Sprite/transition0003.png");
	RES_MGR_TEXTURE.Load("Sprite/transition0004.png");
	RES_MGR_TEXTURE.Load("Sprite/transition0005.png");
	RES_MGR_TEXTURE.Load("Sprite/transition0006.png");
	RES_MGR_TEXTURE.Load("Sprite/transition0007.png");
	RES_MGR_TEXTURE.Load("Sprite/transition0008.png");
	RES_MGR_TEXTURE.Load("Sprite/transition0009.png");
	RES_MGR_TEXTURE.Load("Sprite/transition0010.png");
	RES_MGR_TEXTURE.Load("Sprite/transition0011.png");
	RES_MGR_TEXTURE.Load("Sprite/transition0012.png");
	RES_MGR_TEXTURE.Load("Sprite/transition0013.png");
	RES_MGR_TEXTURE.Load("Sprite/transition0014.png");
	RES_MGR_TEXTURE.Load("Sprite/transition0015.png");

	RES_MGR_TEXTURE.Load("Sprite/transition0016.png");
	RES_MGR_TEXTURE.Load("Sprite/transition0017.png");
	RES_MGR_TEXTURE.Load("Sprite/transition0018.png");
	RES_MGR_TEXTURE.Load("Sprite/transition0019.png");
	RES_MGR_TEXTURE.Load("Sprite/transition0020.png");
	RES_MGR_TEXTURE.Load("Sprite/transition0021.png");
	RES_MGR_TEXTURE.Load("Sprite/transition0022.png");
	RES_MGR_TEXTURE.Load("Sprite/transition0023.png");
	RES_MGR_TEXTURE.Load("Sprite/transition0024.png");
	RES_MGR_TEXTURE.Load("Sprite/transition0025.png");
	RES_MGR_TEXTURE.Load("Sprite/transition0026.png");
	RES_MGR_TEXTURE.Load("Sprite/transition0027.png");
	RES_MGR_TEXTURE.Load("Sprite/transition0028.png");
	RES_MGR_TEXTURE.Load("Sprite/transition0029.png");
	RES_MGR_TEXTURE.Load("Sprite/transition0030.png");
	///////////////////////////////////////////////////
}

void Transition::RemoveChangeSceneImage()
{
	SCENE_MGR.GetCurrentScene()->RemoveGo(this); //�����Ҷ����� �����ִ� �����ϱ� ���ʿ��� �� ����. �̰� ���ֱ�
}

void Transition::SceneChange()
{
	SCENE_MGR.ChangeScene(scene);
}

void Transition::PlayTransitionUp()
{
	SetActive(true);
	animator.Play("Tables/transition_Up.csv");
}

void Transition::PlayTransitionDown()
{
	SetActive(true);
	animator.Play("Tables/transition_Down.csv");
}

void Transition::Reset()
{
	animator.ClearEvent();

	SetPosition({1920.f * 0.5f, 1080.f});
	animator.SetOrigin(Origins::BC);
	animator.AddEvent("Tables/transition_Up.csv", 13, std::bind(&Transition::SceneChange, this));
	animator.AddEvent("Tables/transition_Down.csv", 14, std::bind([this]() {SetActive(false); }));
}

void Transition::Update(float dt)
{
	SpriteGo::Update(dt);
	animator.Update(dt);
}