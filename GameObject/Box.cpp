#include "pch.h"
#include "Box.h"

Box* Box::SetBox(Types stoneType)
{
	Box* box = new Box("STONE");

	switch (stoneType)
	{
	case Box::Types::Box1:
		box->SetTexture("PlusSprite.boxExport0001.png");
		break;
	case Box::Types::Box2:
		box->SetTexture("PlusSprite.boxExport0002.png");
		break;
	case Box::Types::Box3:
		box->SetTexture("PlusSprite.boxExport0003.png");
		break;
	case Box::Types::Box4:
		box->SetTexture("PlusSprite.boxExport0004.png");
		break;
	case Box::Types::Box5:
		box->SetTexture("PlusSprite.boxExport0005.png");
		break;
	case Box::Types::Box6:
		box->SetTexture("PlusSprite.boxExport0006.png");
		break;
	case Box::Types::Box7:
		box->SetTexture("PlusSprite.boxExport0007.png");
		break;
	case Box::Types::Box8:
		box->SetTexture("PlusSprite.boxExport0008.png");
		break;
	case Box::Types::Box9:
		box->SetTexture("PlusSprite.boxExport0009.png");
		break;
	case Box::Types::Box10:
		box->SetTexture("PlusSprite.boxExport00010.png");
		break;
	case Box::Types::Box11:
		box->SetTexture("PlusSprite.boxExport00011.png");
		break;
	default:
		break;
	}
	return box;
}


Box::Box(const std::string& name)
	:SpriteGo(name)
{
}

Box::~Box()
{
}

void Box::Init()
{
	SpriteGo::Init();
}

void Box::Release()
{
	SpriteGo::Release();
}

void Box::Reset()
{
	SpriteGo::Reset();
	SetOrigin(Origins::BOX);
}

void Box::Update(float dt)
{
	SpriteGo::Update(dt);
}

void Box::FixedUpdate(float dt)
{
	SpriteGo::FixedUpdate(dt);
}

void Box::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);

}
