#include "pch.h"
#include "Stone.h"

Stone* Stone::SetStone(Types stoneType)
{
	Stone* stone = new Stone("STONE");

	switch (stoneType)
	{
	case Stone::Types::Box1:
		stone->SetTexture("PlusSprite.boxExport0001.png");
		break;
	case Stone::Types::Box2:
		stone->SetTexture("PlusSprite.boxExport0002.png");
		break;
	case Stone::Types::Box3:
		stone->SetTexture("PlusSprite.boxExport0003.png");
		break;
	case Stone::Types::Box4:
		stone->SetTexture("PlusSprite.boxExport0004.png");
		break;
	case Stone::Types::Box5:
		stone->SetTexture("PlusSprite.boxExport0005.png");
		break;
	case Stone::Types::Box6:
		stone->SetTexture("PlusSprite.boxExport0006.png");
		break;
	case Stone::Types::Box7:
		stone->SetTexture("PlusSprite.boxExport0007.png");
		break;
	case Stone::Types::Box8:
		stone->SetTexture("PlusSprite.boxExport0008.png");
		break;
	case Stone::Types::Box9:
		stone->SetTexture("PlusSprite.boxExport0009.png");
		break;
	case Stone::Types::Box10:
		stone->SetTexture("PlusSprite.boxExport00010.png");
		break;
	case Stone::Types::Box11:
		stone->SetTexture("PlusSprite.boxExport00011.png");
		break;
	default:
		break;
	}
	return stone;
}


Stone::Stone(const std::string& name)
	:SpriteGo(name)
{
}

Stone::~Stone()
{
}

void Stone::Init()
{
	SpriteGo::Init();
	SetTexture("PlusSprite/boxExport0001.png");
}

void Stone::Release()
{
	SpriteGo::Release();
}

void Stone::Reset()
{
	SpriteGo::Reset();
}

void Stone::Update(float dt)
{
	SpriteGo::Update(dt);


}

void Stone::FixedUpdate(float dt)
{
	SpriteGo::FixedUpdate(dt);
}

void Stone::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);

}
