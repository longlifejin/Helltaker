#include "pch.h"
#include "TileMap.h"

TileMap::TileMap(const std::string& name)
	:GameObject(name)
{
}

TileMap::~TileMap()
{
}

void TileMap::SetTile(sf::Vector2f count, sf::Vector2f size)
{


}

void TileMap::Init()
{
	GameObject::Init();
}

void TileMap::Release()
{
	GameObject::Release();

}


void TileMap::Reset()
{
	GameObject::Reset();

}

void TileMap::Update(float dt)
{
	GameObject::Update(dt);

}

void TileMap::Draw(sf::RenderWindow& window)
{
	GameObject::Draw(window);

}
