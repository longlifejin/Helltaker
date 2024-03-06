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
	background = new SpriteGo("Background");
	background->SetTexture("PlusSprite/chapterBG0001.png");
	background->SetOrigin(Origins::TL);
	background->SetPosition({ 0.f, 0.f });
	AddGo(background, Layers::World);

	player = new Player("Player");
	player->SetOrigin(Origins::BL);
	player->SetTexture("Sprite/assets100V20057.png");
	player->SetPosition({ 0.f,0.f });
	AddGo(player, Layers::World);

	int col = 19;
	int row = 10;
	float size = 100.f;

	grid.clear();
	grid.setPrimitiveType(sf::Lines);
	grid.resize((col + 1 + row + 1) * 2);

	sf::Vector2f windowSize = (sf::Vector2f)FRAMEWORK.GetWindowSize();

	sf::Vector2f startLine = { 0.f, 10.f };
	sf::Vector2f endLine = startLine;
	
	int gridIndex = 0;

	for (int i = 0; i < row + 1; ++i)
	{
		startLine = { startLine.x, startLine.y + (i * size) };
		endLine = { 1920.f, startLine.y };
		
		grid[gridIndex].color = sf::Color::Red;
		grid[gridIndex].position = { startLine };

		grid[gridIndex + 1].color = sf::Color::Red;
		grid[gridIndex + 1].position = { endLine };

		gridIndex += 2;

		startLine = { 0.f, 10.f };
		endLine = startLine;
	}

	startLine = { 20.f, 0.f };
	endLine = startLine;

	for (int i = 0; i < col + 1; ++i)
	{
		startLine = { startLine.x + (i * size), startLine.y};
		endLine = { startLine.x, 1080.f };

		grid[gridIndex].color = sf::Color::Red;
		grid[gridIndex].position = { startLine };

		grid[gridIndex + 1].color = sf::Color::Red;
		grid[gridIndex + 1].position = { endLine };

		gridIndex += 2;

		startLine = { 20.f, 0.f };
		endLine = startLine;
	}
	Scene::Init();
}

void Chapter1::Release()
{
	Scene::Release();
}

void Chapter1::Enter()
{
	sf::Vector2f windowSize = (sf::Vector2f)FRAMEWORK.GetWindowSize();
	worldView.setSize(windowSize);
	worldView.setCenter(windowSize * 0.5f);

	Scene::Enter();
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

	window.setView(worldView);
	window.draw(grid);
}

