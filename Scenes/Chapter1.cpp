#include "pch.h"
#include "Chapter1.h"
#include "Player.h"
#include "Demon.h"
#include "Skeleton.h"
#include "Box.h"
#include "TextGo.h"
#include "CollectDemon.h"
#include "Pause.h"

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
	moveCount->Set(fontResMgr.Get("Font/Amiri-Regular.ttf"), "23", 100, sf::Color::White);
	moveCount->SetOrigin(Origins::MC);
	moveCount->SetPosition({IndexToPos(134).x + size / 2.f, IndexToPos(134).y - size / 20.f }); //위치 이상한거 왜 이러는지 파악하기
	AddGo(moveCount, Layers::Ui);

	currentStage = new SpriteGo("CurrentStage");
	currentStage->SetTexture("PlusSprite/01.png");
	currentStage->SetOrigin(Origins::MC);
	currentStage->SetScale({ 2.f, 2.f });
	currentStage->SetPosition({ IndexToPos(149).x + size/2.f, IndexToPos(149).y + size/2.5f}); //더 효율적인 방법 없을까
	AddGo(currentStage, Layers::Ui);

	advice = new TextGo("Advice");
	advice->Set(fontResMgr.Get("Font/NanumSquareEB.otf"), adviceText, 30, sf::Color::White);
	advice->SetOrigin(Origins::MC);
	advice->SetPosition({ IndexToPos(178).x - size / 2.f, IndexToPos(178).y });
	AddGo(advice, Layers::Ui);

	restart = new TextGo("Restart");
	restart->Set(fontResMgr.Get("Font/NanumSquareEB.otf"), restartText, 30, sf::Color::White);
	restart->SetOrigin(Origins::MC);
	restart->SetPosition({ IndexToPos(183).x - size / 2.f, IndexToPos(183).y });
	AddGo(restart, Layers::Ui);

	mapObj.resize(col * row, MapObject::empty); //모든 내용 비어있는 것으로 처리
	//Update때 챕터에 따라 맵을 다시 세팅해주기 위해서 Init에서 빈 것으로 해줌

	pause = new Pause("Pause");
	pause->sortLayer = 2;
	AddGo(pause, Layers::Ui);
	pause->SetActive(false);

	collectDemon = new CollectDemon("Collect");
	collectDemon->sortLayer = 1;
	AddGo(collectDemon, Layers::Ui);
	collectDemon->SetActive(false);

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
	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);

	SetMap();

	Scene::Enter();
}

void Chapter1::Exit()
{

	if (player != nullptr)
	{
		RemoveGo(player);
	}

	if (demon != nullptr)
	{
		RemoveGo(player);
	}

	for (auto& skull : deadSkeletonList)
	{
		if(skull != nullptr)
			RemoveGo(skull);
	}
		deadSkeletonList.clear();

	for (auto& skull : skeletonList)
	{
		if(skull != nullptr)
			RemoveGo(skull);
	}
		skeletonList.clear();

	for (auto& b : boxList)
	{
		if(b!= nullptr)
			RemoveGo(b);
	}
	boxList.clear();

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
						b->currentIndex = b->prevIndex;
						mapObj[b->currentIndex] = MapObject::box;
						player->moveCount -= 1;
						return false;
					}
					else if (mapObj[b->currentIndex] == MapObject::demon ||
						mapObj[b->currentIndex] == MapObject::box ||
						mapObj[b->currentIndex] == MapObject::key ||
						mapObj[b->currentIndex] == MapObject::lockbox ||
						mapObj[b->currentIndex] == MapObject::skeleton)
					{
						b->currentIndex = b->prevIndex;
						player->moveCount -= 1;
						return false;
					}
					b->SetPosition(IndexToPos(b->currentIndex));
					mapObj[b->prevIndex] = MapObject::player;
					mapObj[b->currentIndex] = MapObject::box;
					player->moveCount -= 1;
					return false;
				}
				if (key == sf::Keyboard::S) // TO-DO : 반복되는 내용 함수로 만들어서 쓰기
				{
					b->prevIndex = b->currentIndex;
					b->currentIndex += col;
					if (mapObj[b->currentIndex] == MapObject::wall)
					{
						b->currentIndex = b->prevIndex;
						mapObj[b->currentIndex] = MapObject::box;
						player->moveCount -= 1;
						return false;
					}
					else if (mapObj[b->currentIndex] == MapObject::demon ||
						mapObj[b->currentIndex] == MapObject::box ||
						mapObj[b->currentIndex] == MapObject::key ||
						mapObj[b->currentIndex] == MapObject::lockbox ||
						mapObj[b->currentIndex] == MapObject::skeleton)
					{
						b->currentIndex = b->prevIndex;
						player->moveCount -= 1;
						return false;
					}
					b->SetPosition(IndexToPos(b->currentIndex));
					mapObj[b->prevIndex] = MapObject::player;
					mapObj[b->currentIndex] = MapObject::box;
					player->moveCount -= 1;
					return false;
				}
				if (key == sf::Keyboard::A) // TO-DO : 반복되는 내용 함수로 만들어서 쓰기
				{
					b->prevIndex = b->currentIndex;
					b->currentIndex -= 1;
					if (mapObj[b->currentIndex] == MapObject::wall)
					{
						b->currentIndex = b->prevIndex;
						mapObj[b->currentIndex] = MapObject::box;
						player->moveCount -= 1;
						return false;
					}
					else if (mapObj[b->currentIndex] == MapObject::demon ||
						mapObj[b->currentIndex] == MapObject::box ||
						mapObj[b->currentIndex] == MapObject::key ||
						mapObj[b->currentIndex] == MapObject::lockbox ||
						mapObj[b->currentIndex] == MapObject::skeleton)
					{
						b->currentIndex = b->prevIndex;
						player->moveCount -= 1;
						return false;
					}
					b->SetPosition(IndexToPos(b->currentIndex));
					mapObj[b->prevIndex] = MapObject::player;
					mapObj[b->currentIndex] = MapObject::box;
					player->moveCount -= 1;
					return false;
				}
				if (key == sf::Keyboard::D) // TO-DO : 반복되는 내용 함수로 만들어서 쓰기
				{
					b->prevIndex = b->currentIndex;
					b->currentIndex += 1;
					if (mapObj[b->currentIndex] == MapObject::wall)
					{
						b->currentIndex = b->prevIndex;
						mapObj[b->currentIndex] = MapObject::box;
						player->moveCount -= 1;
						return false;
					}
					else if (mapObj[b->currentIndex] == MapObject::demon ||
						mapObj[b->currentIndex] == MapObject::box ||
						mapObj[b->currentIndex] == MapObject::key ||
						mapObj[b->currentIndex] == MapObject::lockbox ||
						mapObj[b->currentIndex] == MapObject::skeleton)
					{
						b->currentIndex = b->prevIndex;
						player->moveCount -= 1;
						return false;
					}
					b->SetPosition(IndexToPos(b->currentIndex));
					mapObj[b->prevIndex] = MapObject::player;
					mapObj[b->currentIndex] = MapObject::box;
					player->moveCount -= 1;
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
		player->moveCount = 0;
		isDemonGet = true;
		return false;
	}
	else if (mapObj[index] == MapObject::skeleton)
	{
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
						skeletonList.remove(skull);
						player->moveCount -= 1;
						return false;
					}
					else if (mapObj[skull->currentIndex] == MapObject::demon ||
						mapObj[skull->currentIndex] == MapObject::box ||
						mapObj[skull->currentIndex] == MapObject::key ||
						mapObj[skull->currentIndex] == MapObject::lockbox)
					{
						skull->currentIndex = skull->prevIndex;
						player->moveCount -= 1;
						return false;
					}
					else if (mapObj[skull->currentIndex] == MapObject::skeleton)
					{
						skull->OnDie();
						deadSkeletonList.push_back(skull);
						mapObj[skull->prevIndex] = MapObject::empty;
						skeletonList.remove(skull);
						player->moveCount -= 1;
						return false;
					}
					skull->SetPosition(IndexToPos(skull->currentIndex));
					mapObj[skull->prevIndex] = MapObject::player;
					mapObj[skull->currentIndex] = MapObject::skeleton;
					player->moveCount -= 1;
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
						skeletonList.remove(skull);
						player->moveCount -= 1;
						return false;
					}
					else if (mapObj[skull->currentIndex] == MapObject::demon ||
						mapObj[skull->currentIndex] == MapObject::box ||
						mapObj[skull->currentIndex] == MapObject::key ||
						mapObj[skull->currentIndex] == MapObject::lockbox)
					{
						skull->currentIndex = skull->prevIndex;
						player->moveCount -= 1;
						return false;
					}
					else if (mapObj[skull->currentIndex] == MapObject::skeleton)
					{
						skull->OnDie();
						deadSkeletonList.push_back(skull);
						mapObj[skull->prevIndex] = MapObject::empty;
						skeletonList.remove(skull);
						player->moveCount -= 1;
						return false;
					}
					skull->SetPosition(IndexToPos(skull->currentIndex));
					mapObj[skull->prevIndex] = MapObject::player;
					mapObj[skull->currentIndex] = MapObject::skeleton;
					player->moveCount -= 1;
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
						skeletonList.remove(skull);
						player->moveCount -= 1;
						return false;
					}
					else if (mapObj[skull->currentIndex] == MapObject::demon ||
						mapObj[skull->currentIndex] == MapObject::box ||
						mapObj[skull->currentIndex] == MapObject::key ||
						mapObj[skull->currentIndex] == MapObject::lockbox)
					{
						skull->currentIndex = skull->prevIndex;
						player->moveCount -= 1;
						return false;
					}
					else if (mapObj[skull->currentIndex] == MapObject::skeleton)
					{
						skull->OnDie();
						deadSkeletonList.push_back(skull);
						mapObj[skull->prevIndex] = MapObject::empty;
						skeletonList.remove(skull);
						player->moveCount -= 1;
						return false;
					}
					skull->SetPosition(IndexToPos(skull->currentIndex));
					mapObj[skull->prevIndex] = MapObject::player;
					mapObj[skull->currentIndex] = MapObject::skeleton;
					player->moveCount -= 1;
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
						skeletonList.remove(skull);
						player->moveCount -= 1;
						return false;
					}
					else if (mapObj[skull->currentIndex] == MapObject::demon ||
						mapObj[skull->currentIndex] == MapObject::box ||
						mapObj[skull->currentIndex] == MapObject::key ||
						mapObj[skull->currentIndex] == MapObject::lockbox)
					{
						skull->currentIndex = skull->prevIndex;
						player->moveCount -= 1;
						return false;
					}
					else if (mapObj[skull->currentIndex] == MapObject::skeleton)
					{
						skull->OnDie();
						deadSkeletonList.push_back(skull);
						mapObj[skull->prevIndex] = MapObject::empty;
						skeletonList.remove(skull);
						player->moveCount -= 1;
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
		player->moveCount -= 1;
		return false;
	}
	//empty인 경우
	mapObj[player->prevIndex] = MapObject::empty;
	player->moveCount -= 1;
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
		player = new Player("Player");
		player->SetTexture("Sprite/assets100V20057.png");
		player->SetOrigin(Origins::BC);
		player->SetPosition(IndexToPos(index));
		player->Init();
		AddGo(player, Layers::World);
		break;
	case Chapter1::MapObject::demon:
		demon = new Demon("Demon");
		demon->SetTexture("Sprite/pandemonica_finalModel0010.png");
		demon->SetPosition(IndexToPos(index));
		demon->SetOrigin(Origins::BC);
		demon->Init();
		AddGo(demon, Layers::World);
		break;
	case Chapter1::MapObject::skeleton:
		skeleton = new Skeleton("Skeleton");
		skeleton->SetTexture("Sprite/assets100V20235.png");
		skeleton->currentIndex = skeleton->prevIndex = index;
		skeleton->SetPosition(IndexToPos(index));
		skeleton->SetOrigin(Origins::BC);
		skeleton->Init();
		skeletonList.push_back(skeleton); //생성하면 list에 넣어주기
		AddGo(skeleton, Layers::World);
		break;
	case Chapter1::MapObject::box:
		box = new Box("Box");
		box->SetTexture("Sprite/boxExport0001.png");
		box->currentIndex = box->prevIndex = index;
		box->SetPosition(IndexToPos(index));
		box->SetOrigin(Origins::BC);
		box->Init();
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

	moveCount->SetString(std::to_string(player->moveCount));

	if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
	{
		pause->SetActive(true);
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::F1))
	{
		SetGrid();
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::F2))
	{
		grid.clear();
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::R))
	{
		SCENE_MGR.ChangeScene(SceneIds::CHAPTER1);
	}

	if (isDemonGet && !collectDemon->GetActive())
	{
		collectDemon->SetActive(true);
		isDemonGet = false;
	}

	if (collectDemon->GetAnswerSelect())
	{
		//획득 애니메이션 재생 후 다음 챕터로 넘어가기
		//std::cout << "다음 챕터로 가자" << std::endl;
	}
}

void Chapter1::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);

	window.setView(worldView);
	window.draw(grid);
}

