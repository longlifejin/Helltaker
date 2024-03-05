#include "pch.h"
#include "SceneDev1.h"

SceneDev1::SceneDev1(SceneIds id) :Scene(id)
{

}

SceneDev1::~SceneDev1()
{
}

void SceneDev1::Init()
{

}

void SceneDev1::Update(float dt)
{
	Scene::Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		SceneMgr::Instance().ChangeScene(SceneIds::SCENEDVE1);
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Num1))
	{
		GameObject* findGo = FindGo("Message");
		findGo->SetActive(!findGo->GetActive());
	}
}


void SceneDev1::Release()
{
}

void SceneDev1::Enter()
{


}

void SceneDev1::Exit()
{
}