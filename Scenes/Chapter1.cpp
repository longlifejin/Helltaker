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
	player->SetTexture("Sprite/assets100V20057.png");
	player->SetOrigin(Origins::MC);
	player->SetPosition(GetGridPos(51));
	currentIndex = 51;
	AddGo(player, Layers::World);

	SetGrid();

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

void Chapter1::SetGrid()
{
	grid.clear();
	grid.setPrimitiveType(sf::Lines);
	grid.resize((col + 1 + row + 1) * 2);

	sf::Vector2f startLine = { 0.f, 0.f };
	sf::Vector2f endLine = startLine;

	int gridIndex = 0;

	for (int i = 0; i < row + 1; ++i) //가로격자
	{
		startLine = { offsetX ,offsetY + (i * size) };
		endLine = { (float)FRAMEWORK.GetWindowSize().x - offsetX, startLine.y };

		grid[gridIndex].color = sf::Color::Red;
		grid[gridIndex].position = startLine;
		grid[gridIndex + 1].color = sf::Color::Red;
		grid[gridIndex + 1].position = endLine;

		gridIndex += 2;
	}

	startLine = { 0.f, 0.f };
	endLine = startLine;

	for (int i = 0; i < col + 1; ++i) //세로격자
	{
		startLine = { offsetX + (i * size), offsetY };
		endLine = { startLine.x, (float)FRAMEWORK.GetWindowSize().y - offsetY };

		grid[gridIndex].color = sf::Color::Red;
		grid[gridIndex].position = startLine;
		grid[gridIndex + 1].color = sf::Color::Red;
		grid[gridIndex + 1].position = endLine;

		gridIndex += 2;
	}
}

sf::Vector2f Chapter1::GetGridPos(int index)
{
	int rowIndex = index / (col + 1); // 인덱스로부터 행 위치 계산
	int columnIndex = index % (col + 1); // 인덱스로부터 열 위치 계산

	// 격자 칸의 중앙 위치 계산
	float x = offsetX + (columnIndex * size) + size / 2;
	float y = offsetY + (rowIndex * size) + size / 2;

	return sf::Vector2f(x, y);
}

void Chapter1::SetObject()
{

}

void Chapter1::Update(float dt)
{
	Scene::Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::A))
	{
		currentIndex -= 1;
		player->SetPosition(GetGridPos(currentIndex));
	}
}

void Chapter1::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);

	window.setView(worldView);
	window.draw(grid);
}

