#include "pch.h"
#include "Chapter1.h"
#include "Player.h"
#include "Stone.h"

Chapter1::Chapter1(SceneIds id)
	:Scene(id)
{
}

Chapter1::~Chapter1()
{
}

void Chapter1::Init()
{
	Scene::Init();
	background = new SpriteGo("Background");
	background->SetTexture("PlusSprite/chapterBG0001.png");
	AddGo(background, Layers::World);

	player = new Player("Player");
	player->SetOrigin(Origins::TL);
	player->SetTexture("Sprite/assets100V20057.png");
	player->SetPosition({ (float)(FRAMEWORK.GetWindowSize().x * 0.6),(float)(FRAMEWORK.GetWindowSize().y * 0.2) }); //일단 하드코딩 ㅠ
	AddGo(player, Layers::World);

	gridHorizontal.clear();
	gridHorizontal.setPrimitiveType(sf::Lines);
	gridHorizontal[0].position = sf::Vector2f(0.f, 100.f);
	gridHorizontal[1].position = sf::Vector2f(1920.f, 100.f);
	gridHorizontal[0].color = sf::Color::Red;
	gridHorizontal[1].color = sf::Color::Red;
	
	

}

void Chapter1::Release()
{
	Scene::Release();
}

void Chapter1::Enter()
{
	Scene::Enter();
	sf::Vector2f windowSize = (sf::Vector2f)FRAMEWORK.GetWindowSize();
	worldView.setSize(windowSize);
	worldView.setCenter({ (float)(windowSize.x * 0.5), (float)(windowSize.y * 0.5) });
}

void Chapter1::Exit()
{
	Scene::Exit();
}

void Chapter1::Update(float dt)
{
	Scene::Update(dt);
}

void Chapter1::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	window.draw(gridHorizontal);
}

