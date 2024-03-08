#include "pch.h"
#include "Chapter1.h"
#include "Player.h"
#include "Demon.h"
#include "Skeleton.h"
#include "Box.h"
#include "TextGo.h"

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

	uiRoseLeft = new SpriteGo("UiRoseLeft");
	uiRoseLeft->SetTexture("Texture2D/mainUIexport_bUI2.png");
	uiRoseLeft->SetOrigin(Origins::TL);
	uiRoseLeft->SetPosition({ 0.f,0.f });
	AddGo(uiRoseLeft, Layers::Ui);

	uiRoseRight = new SpriteGo("UiRoseRight");
	uiRoseRight->SetTexture("Texture2D/mainUIexport_bUI2.png");
	uiRoseRight->SetOrigin(Origins::TL);
	uiRoseRight->SetPosition({ (float)FRAMEWORK.GetWindowSize().x, 0.f });
	uiRoseRight->SetFlipX(true);
	AddGo(uiRoseRight, Layers::Ui);

	uiDemonLeft = new SpriteGo("uiDemonLeft");
	uiDemonLeft->SetTexture("Texture2D/mainUIexport_fUI0001.png");
	uiDemonLeft->SetOrigin(Origins::BL);
	uiDemonLeft->SetPosition({ 0.f, (float)FRAMEWORK.GetWindowSize().y });
	AddGo(uiDemonLeft, Layers::Ui);

	uiDemonRight = new SpriteGo("uiDemonRight");
	uiDemonRight->SetTexture("Texture2D/mainUIexport_fUI0001.png");
	uiDemonRight->SetOrigin(Origins::BL);
	uiDemonRight->SetPosition({ (float)FRAMEWORK.GetWindowSize().x, (float)FRAMEWORK.GetWindowSize().y });
	uiDemonRight->SetFlipX(true); //피봇점도 같이 뒤집히는건가?
	AddGo(uiDemonRight, Layers::Ui);

	moveCount = new TextGo("MoveCount");
	moveCount->Set(fontResMgr.Get("Font/Amiri-Regular.ttf"), "0", 100, sf::Color::White);
	moveCount->SetOrigin(Origins::ML);
	moveCount->SetPosition(IndexToPos(134));
	AddGo(moveCount, Layers::Ui);

	currentStage = new SpriteGo("CurrentStage");
	currentStage->SetTexture("PlusSprite/01.png");
	currentStage->SetOrigin(Origins::MC);
	currentStage->SetScale({ 2.f, 2.f });
	currentStage->SetPosition({ IndexToPos(149).x + size/2.f, IndexToPos(149).y + size/2.5f}); //더 효율적인 방법 없을까
	AddGo(currentStage, Layers::Ui);

	player = new Player("Player");
	AddGo(player, Layers::World);

	mapObj.resize(col * row, MapObject::empty); //모든 내용 비어있는 것으로 처리
	//Update때 챕터에 따라 맵을 다시 세팅해주기 위해서 Init에서 빈 것으로 해줌

	SetMap();

	Scene::Init();
}

void Chapter1::Release()
{
	Scene::Release();
	for (auto& skull : deadSkeletonList)
	{
		RemoveGo(skull);
	}
}

void Chapter1::Enter()
{
	sf::Vector2f windowSize = (sf::Vector2f)FRAMEWORK.GetWindowSize();
	worldView.setSize(windowSize);
	worldView.setCenter(windowSize * 0.5f);
	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);

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

void Chapter1::SetMap()
{
	for (int i = 0; i < mapLayout.size(); ++i) //10번 반복
	{
		for (int j = 0; j < mapLayout[i].length(); ++j) //20번 반복
		{
			char mapObjChar = mapLayout[i][j];

			MapObject mapObj;

			switch (mapObjChar)
			{
			case'E': mapObj = MapObject::empty;
				break;
			case'W': mapObj = MapObject::wall;
				break;
			case'P': mapObj = MapObject::player;
				break;
			case'D': mapObj = MapObject::demon;
				break;
			case'S': mapObj = MapObject::skeleton;
				break;
			case'B': mapObj = MapObject::box;
				break;
			case'K': mapObj = MapObject::key;
				break;
			case'L': mapObj = MapObject::lockbox;
				break;
			default: mapObj = MapObject::empty;
				break;
			}
			int index = i * col + j;
			SetObject(index, mapObj);
		}
	}
}

bool Chapter1::CheckInteraction(int index, sf::Keyboard::Key key)
{
	if(mapObj[index] == MapObject::wall)
	{
		player->currentIndex = player->prevIndex;
		return false;
	}
	else if(mapObj[index] == MapObject::box)
	{
		for (auto& b : boxList)
		{
			if (b->GetCurrentIndex() == index)
			{
				if (key == sf::Keyboard::W) // TO-DO : 반복되는 내용 함수로 만들어서 쓰기
				{
					b->prevIndex = b->currentIndex;
					b->currentIndex -= col;
					if (mapObj[b->currentIndex] == MapObject::wall)
					{
						b->Destroy();
						destroyedBoxList.push_back(b);
						mapObj[b->prevIndex] = MapObject::empty;
						return true;
					}
					else if (mapObj[b->currentIndex] == MapObject::demon ||
						mapObj[b->currentIndex] == MapObject::box ||
						mapObj[b->currentIndex] == MapObject::key ||
						mapObj[b->currentIndex] == MapObject::lockbox ||
						mapObj[b->currentIndex] == MapObject::skeleton)
					{
						b->currentIndex = b->prevIndex;
						return false;
					}
					b->SetPosition(IndexToPos(b->currentIndex));
					mapObj[b->prevIndex] = MapObject::player;
					mapObj[b->currentIndex] = MapObject::box;
					return false;
				}
				if (key == sf::Keyboard::S) // TO-DO : 반복되는 내용 함수로 만들어서 쓰기
				{
					b->prevIndex = b->currentIndex;
					b->currentIndex += col;
					if (mapObj[b->currentIndex] == MapObject::wall)
					{
						b->Destroy();
						destroyedBoxList.push_back(b); 
						mapObj[b->prevIndex] = MapObject::empty;
						return true;
					}
					else if (mapObj[b->currentIndex] == MapObject::demon ||
						mapObj[b->currentIndex] == MapObject::box ||
						mapObj[b->currentIndex] == MapObject::key ||
						mapObj[b->currentIndex] == MapObject::lockbox ||
						mapObj[b->currentIndex] == MapObject::skeleton)
					{
						b->currentIndex = b->prevIndex;
						return false;
					}
					b->SetPosition(IndexToPos(b->currentIndex));
					mapObj[b->prevIndex] = MapObject::player;
					mapObj[b->currentIndex] = MapObject::box;
					return false;
				}
				if (key == sf::Keyboard::A) // TO-DO : 반복되는 내용 함수로 만들어서 쓰기
				{
					b->prevIndex = b->currentIndex;
					b->currentIndex -= 1;
					if (mapObj[b->currentIndex] == MapObject::wall)
					{
						b->Destroy();
						destroyedBoxList.push_back(b);
						mapObj[b->prevIndex] = MapObject::empty;
						return true;
					}
					else if (mapObj[b->currentIndex] == MapObject::demon ||
						mapObj[b->currentIndex] == MapObject::box ||
						mapObj[b->currentIndex] == MapObject::key ||
						mapObj[b->currentIndex] == MapObject::lockbox ||
						mapObj[b->currentIndex] == MapObject::skeleton)
					{
						b->currentIndex = b->prevIndex;
						return false;
					}
					b->SetPosition(IndexToPos(b->currentIndex));
					mapObj[b->prevIndex] = MapObject::player;
					mapObj[b->currentIndex] = MapObject::box;
					return false;
				}
				if (key == sf::Keyboard::D) // TO-DO : 반복되는 내용 함수로 만들어서 쓰기
				{
					b->prevIndex = b->currentIndex;
					b->currentIndex += 1;
					if (mapObj[b->currentIndex] == MapObject::wall)
					{
						b->Destroy();
						destroyedBoxList.push_back(b);
						mapObj[b->prevIndex] = MapObject::empty;
						return true;
					}
					else if (mapObj[b->currentIndex] == MapObject::demon ||
						mapObj[b->currentIndex] == MapObject::box ||
						mapObj[b->currentIndex] == MapObject::key ||
						mapObj[b->currentIndex] == MapObject::lockbox ||
						mapObj[b->currentIndex] == MapObject::skeleton)
					{
						b->currentIndex = b->prevIndex;
						return false;
					}
					b->SetPosition(IndexToPos(b->currentIndex));
					mapObj[b->prevIndex] = MapObject::player;
					mapObj[b->currentIndex] = MapObject::box;
					return false;
				}
			}
		}
		player->currentIndex = player->prevIndex;
		return false;
	}
	else if(mapObj[index] == MapObject::demon)
	{
		player->currentIndex = player->prevIndex;
		//player clear animation 재생
		std::cout << "Chapter Clear" << std::endl; //test용
		return false;
	}
	else if (mapObj[index] == MapObject::skeleton)
	{
		//skeleton들을 순회하면서 해당 인덱스에 있는 skeleton만 상호작용할 수 있게 수정하기
		for (auto& skull : skeletonList)
		{
			if (skull->GetCurrentIndex() == index)
			{
				if (key == sf::Keyboard::W) // TO-DO : 반복되는 내용 함수로 만들어서 쓰기
				{
					skull->prevIndex = skull->currentIndex;
					skull->currentIndex -= col;
					if (mapObj[skull->currentIndex] == MapObject::wall)
					{
						skull->OnDie();
						deadSkeletonList.push_back(skull);
						mapObj[skull->prevIndex] = MapObject::empty;
						return true;
					}
					else if (mapObj[skull->currentIndex] == MapObject::demon ||
						mapObj[skull->currentIndex] == MapObject::box ||
						mapObj[skull->currentIndex] == MapObject::key ||
						mapObj[skull->currentIndex] == MapObject::lockbox ||
						mapObj[skull->currentIndex] == MapObject::skeleton)
					{
						skull->currentIndex = skull->prevIndex;
						return false;
					}
					skull->SetPosition(IndexToPos(skull->currentIndex));
					mapObj[skull->prevIndex] = MapObject::player;
					mapObj[skull->currentIndex] = MapObject::skeleton;
					return false;
				}
				else if (key == sf::Keyboard::S)
				{
					skull->prevIndex = skull->currentIndex;
					skull->currentIndex += col; 
					if (mapObj[skull->currentIndex] == MapObject::wall)
					{
						skull->OnDie();
						deadSkeletonList.push_back(skull);
						mapObj[skull->prevIndex] = MapObject::empty;
						return true;
					}
					else if (mapObj[skull->currentIndex] == MapObject::demon ||
						mapObj[skull->currentIndex] == MapObject::box ||
						mapObj[skull->currentIndex] == MapObject::key ||
						mapObj[skull->currentIndex] == MapObject::lockbox ||
						mapObj[skull->currentIndex] == MapObject::skeleton)
					{
						skull->currentIndex = skull->prevIndex;
						return false;
					}
					skull->SetPosition(IndexToPos(skull->currentIndex));
					mapObj[skull->prevIndex] = MapObject::player;
					mapObj[skull->currentIndex] = MapObject::skeleton;
					return false;
				}
				else if (key == sf::Keyboard::A)
				{
					skull->prevIndex = skull->currentIndex;
					skull->currentIndex -= 1;
					if (mapObj[skull->currentIndex] == MapObject::wall)
					{
						skull->OnDie();
						deadSkeletonList.push_back(skull);
						mapObj[skull->prevIndex] = MapObject::empty;
						return true;
					}
					else if (mapObj[skull->currentIndex] == MapObject::demon ||
						mapObj[skull->currentIndex] == MapObject::box ||
						mapObj[skull->currentIndex] == MapObject::key ||
						mapObj[skull->currentIndex] == MapObject::lockbox ||
						mapObj[skull->currentIndex] == MapObject::skeleton)
					{
						skull->currentIndex = skull->prevIndex;
						return false;
					}
					skull->SetPosition(IndexToPos(skull->currentIndex));
					mapObj[skull->prevIndex] = MapObject::player;
					mapObj[skull->currentIndex] = MapObject::skeleton;
					return false;
				}
				else if (key == sf::Keyboard::D)
				{
					skull->prevIndex = skull->currentIndex;
					skull->currentIndex += 1;
					if (mapObj[skull->currentIndex] == MapObject::wall)
					{
						skull->OnDie();
						deadSkeletonList.push_back(skull);
						mapObj[skull->prevIndex] = MapObject::empty;
						return true;
					}
					else if (mapObj[skull->currentIndex] == MapObject::demon ||
						mapObj[skull->currentIndex] == MapObject::box ||
						mapObj[skull->currentIndex] == MapObject::key ||
						mapObj[skull->currentIndex] == MapObject::lockbox ||
						mapObj[skull->currentIndex] == MapObject::skeleton)
					{
						skull->currentIndex = skull->prevIndex;
						return false;
					}
					skull->SetPosition(IndexToPos(skull->currentIndex));
					mapObj[skull->prevIndex] = MapObject::player;
					mapObj[skull->currentIndex] = MapObject::skeleton;
					return false;
				}
			}
		}
		player->currentIndex = player->prevIndex;
		return false;
	}
	//empty인 경우
	mapObj[player->prevIndex] = MapObject::empty;
	return true;
}

bool Chapter1::skullInteraction()
{
	return true;
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
	switch (obj)
	{
	case Chapter1::MapObject::empty:
		break;
	case Chapter1::MapObject::wall:
		break;
	case Chapter1::MapObject::player:
		player->SetTexture("Sprite/assets100V20057.png");
		player->SetOrigin(Origins::BC);
		player->SetPosition(IndexToPos(index));
		break;
	case Chapter1::MapObject::demon:
		demon = new Demon("Demon");
		demon->SetTexture("Sprite/pandemonica_finalModel0010.png");
		demon->SetPosition(IndexToPos(index));
		demon->SetOrigin(Origins::BC);
		AddGo(demon, Layers::World);
		break;
	case Chapter1::MapObject::skeleton:
		skeleton = new Skeleton("Skeleton");
		skeleton->SetTexture("Sprite/assets100V20235.png");
		skeleton->currentIndex = skeleton->prevIndex = index;
		skeleton->SetPosition(IndexToPos(index));
		skeleton->SetOrigin(Origins::BC);
		skeletonList.push_back(skeleton); //생성하면 list에 넣어주기
		AddGo(skeleton, Layers::World);
		break;
	case Chapter1::MapObject::box:
		box = new Box("Box");
		box->SetTexture("Sprite/boxExport0001.png");
		box->currentIndex = box->prevIndex = index;
		box->SetPosition(IndexToPos(index));
		box->SetOrigin(Origins::BC);
		boxList.push_back(box);
		AddGo(box, Layers::World);
		break;
	case Chapter1::MapObject::key:
		break;
	case Chapter1::MapObject::lockbox:
		break;
	default:
		break;
	}
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

	moveCount->SetString(std::to_string(player->moveCount));
}

void Chapter1::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);

	window.setView(worldView);
	window.draw(grid);
}

