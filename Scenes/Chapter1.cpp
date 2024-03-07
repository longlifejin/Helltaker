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
	player->SetOrigin(Origins::BC);
	player->SetPosition(IndexToPos(49));
	currentIndex = 49; //챕터1 시작 위치
	AddGo(player, Layers::World);

	mapObj.resize(col * row, MapObject::empty); //모든 내용 비어있는 것으로 처리
	//Update때 챕터에 따라 맵을 다시 세팅해주기 위해서 Init에서 빈 것으로 해줌


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

bool Chapter1::checkCollision(int index)
{
	if (mapObj[index] != MapObject::stone && mapObj[index] != MapObject::wall)
	{
		return true;
	}
	else
	{
		currentIndex = prevIndex;
		return false;
	}
}

int Chapter1::PosToIndex(sf::Vector2f pos)
{
	int rowIndex = (pos.y - offsetY - (size / 2)) / size;
	int columnIndex = (pos.x - offsetX - (size / 2)) / size;

	int index = rowIndex * col + columnIndex;
	return index;
}

sf::Vector2f Chapter1::IndexToPos(int index)
{
	int rowIndex = index / col;
	int columnIndex = index % col; 
	
	float x = offsetX + (columnIndex * size) + size / 2;
	float y = offsetY + (rowIndex * size) + size / 2;

	return sf::Vector2f(x, y);
}

void Chapter1::SetObject(int index, MapObject obj)
{
	mapObj[index] = obj;
	//인덱스에 맞게 이미지도 세팅해주기

}

void Chapter1::Update(float dt)
{
	Scene::Update(dt);


	if (InputMgr::GetKeyDown(sf::Keyboard::F1))
	{
		SetGrid();
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::F2))
	{
		grid.clear();
	}

	SetObject(50, MapObject::wall);
}

void Chapter1::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);

	window.setView(worldView);
	window.draw(grid);
}

