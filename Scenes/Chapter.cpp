#include "pch.h"
#include "Chapter.h"
#include "Player.h"
#include "Demon.h"
#include "Skeleton.h"
#include "Box.h"
#include "TextGo.h"
#include "CollectDemon.h"
#include "Pause.h"
#include "SkeletonDead.h"
#include "Transition.h"

Chapter::Chapter(SceneIds id)
	:Scene(id)
{
}

Chapter::~Chapter()
{
}

void Chapter::Init()
{
	backColor = new SpriteGo("BackColor");
	backColor->SetTexture("Texture2D/backColor.png");
	backColor->SetOrigin({ 0.f,0.f });
	backColor->SetPosition({ 0.f,0.f });
	backColor->sortOrder = -1;
	AddGo(backColor, Layers::World);

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
	uiDemonRight->SetFlipX(true); //�Ǻ����� ���� �������°ǰ�?
	AddGo(uiDemonRight, Layers::Ui);

	moveCount = new TextGo("MoveCount");
	moveCount->Set(fontResMgr.Get("Font/Amiri-Regular.ttf"), "23", 100, sf::Color::White);
	moveCount->SetOrigin(Origins::MC);
	moveCount->SetPosition({IndexToPos(134).x + size / 2.f, IndexToPos(134).y - size / 20.f }); //��ġ �̻��Ѱ� �� �̷����� �ľ��ϱ�
	AddGo(moveCount, Layers::Ui);

	currentStage = new SpriteGo("CurrentStage");
	currentStage->SetTexture("PlusSprite/01.png");
	currentStage->SetOrigin(Origins::MC);
	currentStage->SetScale({ 2.f, 2.f });
	currentStage->SetPosition({ IndexToPos(149).x + size/2.f, IndexToPos(149).y + size/2.5f}); //�� ȿ������ ��� ������
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

	mapObj.resize(col * row, MapObject::empty); //��� ���� ����ִ� ������ ó��
	//Update�� é�Ϳ� ���� ���� �ٽ� �������ֱ� ���ؼ� Init���� �� ������ ����

	pause = new Pause("Pause");
	pause->sortLayer = 2;
	AddGo(pause, Layers::Ui);
	pause->SetActive(false);

	collectDemon = new CollectDemon("Collect");
	collectDemon->sortLayer = 1;
	AddGo(collectDemon, Layers::Ui);
	collectDemon->SetActive(false);

	SetUiActive(true);

	Scene::Init();
}

void Chapter::Release()
{
	Scene::Release();
}

void Chapter::Enter()
{
	backColor->sortOrder = -1;
	ResortGo(backColor);
	sf::Vector2f windowSize = (sf::Vector2f)FRAMEWORK.GetWindowSize();
	worldView.setSize(windowSize);
	worldView.setCenter(windowSize * 0.5f);
	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);

	SetMap();
	SetUiActive(true);

	Scene::Enter();
}

void Chapter::Exit()
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

void Chapter::SetGrid()
{
	grid.clear();
	grid.setPrimitiveType(sf::Lines);
	grid.resize((col + 1 + row + 1) * 2);

	sf::Vector2f startLine = { 0.f, 0.f };
	sf::Vector2f endLine = startLine;

	int gridIndex = 0;

	for (int i = 0; i < row + 1; ++i) //���ΰ���
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

	for (int i = 0; i < col + 1; ++i) //���ΰ���
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

void Chapter::SetMap()
{
	for (int i = 0; i < mapLayout.size(); ++i) //10�� �ݺ�
	{
		for (int j = 0; j < mapLayout[i].length(); ++j) //20�� �ݺ�
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

void Chapter::SetUiActive(bool active)
{
	uiRoseLeft->SetActive(active);
	uiRoseRight->SetActive(active);
	uiDemonLeft->SetActive(active);
	uiDemonRight->SetActive(active);
	moveCount->SetActive(active);
	currentStage->SetActive(active);
	advice->SetActive(active);
	restart->SetActive(active);
	background->SetActive(active);
}

void Chapter::PlayTransition()
{
	Transition* changeScene = new Transition("ChangeScene Animation");
	changeScene->Init();
	changeScene->SetPosition({ 0.f,0.f });
	changeScene->Reset();
	AddGo(changeScene, Layers::Ui);
}

Chapter::MapObject Chapter::CheckInteraction(int curr, int prev)
{
	int moveAmount = curr - prev;

	switch (mapObj[curr])
	{
	case MapObject::wall:
		player->currentIndex = prev;
		mapObj[player->currentIndex] = MapObject::player;
		mapObj[curr] = MapObject::wall;
		return MapObject::wall;
	case MapObject::demon:
		player->currentIndex = prev;
		player->moveCount = 0;
		isDemonGet = true;
		return MapObject::demon;
	case MapObject::skeleton:
		for (auto& skull : skeletonList)
		{
			if (skull->GetCurrentIndex() == curr)
			{
				skull->prevIndex = skull->currentIndex;
				skull->currentIndex += moveAmount;
				if (mapObj[skull->currentIndex] == MapObject::wall ||
					mapObj[skull->currentIndex] == MapObject::box)
				{
					SkeletonDead* skeletonDestroy = new SkeletonDead("Skeleton Dead Animation");
					skeletonDestroy->Init();
					skeletonDestroy->Reset();
					skeletonDestroy->SetPosition(IndexToPos(curr));
					AddGo(skeletonDestroy, Layers::World);

					skull->SetActive(false);
					deadSkeletonList.push_back(skull);
					mapObj[skull->prevIndex] = MapObject::empty;
					skeletonList.remove(skull);
					player->moveCount -= 1;
					break;
				}
				else if (mapObj[skull->currentIndex] == MapObject::skeleton)
				{
					SkeletonDead* skeletonDestroy = new SkeletonDead("Skeleton Dead Animation");
					skeletonDestroy->Init();
					skeletonDestroy->Reset();
					skeletonDestroy->SetPosition(IndexToPos(curr));
					AddGo(skeletonDestroy, Layers::World);

					skull->SetActive(false);
					deadSkeletonList.push_back(skull);
					mapObj[skull->prevIndex] = MapObject::empty;
					mapObj[skull->currentIndex] = MapObject::skeleton;
					skeletonList.remove(skull);
					player->moveCount -= 1;
					break;
				}
				else if (mapObj[skull->currentIndex] == MapObject::demon ||
					mapObj[skull->currentIndex] == MapObject::key ||
					mapObj[skull->currentIndex] == MapObject::lockbox)
				{
					skull->currentIndex = skull->prevIndex;
					player->moveCount -= 1;
					break;
				}
				else if (mapObj[skull->currentIndex] == MapObject::empty)
				{
					skull->SetPosition(IndexToPos(skull->currentIndex));
					mapObj[skull->prevIndex] = MapObject::player;
					mapObj[skull->currentIndex] = MapObject::skeleton;
					skull->animator.Play("Tables/Skeleton_Damage.csv");
					skull->animator.PlayQueue("Tables/Skeleton_Idle.csv");
					player->moveCount -= 1;
					break;
				}
			}
		}
		player->currentIndex = player->prevIndex;
		return MapObject::skeleton;
	case MapObject::box:
		for (auto& b : boxList)
		{
			if (b->GetCurrentIndex() == curr)
			{
				b->prevIndex = b->currentIndex;
				b->currentIndex += moveAmount;
				if (mapObj[b->currentIndex] == MapObject::wall)
				{
					b->currentIndex = b->prevIndex;
					mapObj[b->currentIndex] = MapObject::box;
					player->moveCount -= 1;
					break;
				}
				else if (mapObj[b->currentIndex] == MapObject::demon ||
					mapObj[b->currentIndex] == MapObject::box ||
					mapObj[b->currentIndex] == MapObject::key ||
					mapObj[b->currentIndex] == MapObject::lockbox ||
					mapObj[b->currentIndex] == MapObject::skeleton)
				{
					b->currentIndex = b->prevIndex;
					player->moveCount -= 1;
					break;
				}
				else if (mapObj[b->currentIndex] == MapObject::empty)
				{
					b->SetPosition(IndexToPos(b->currentIndex));
					mapObj[b->prevIndex] = MapObject::player;
					mapObj[b->currentIndex] = MapObject::box;
					player->moveCount -= 1;
					break;
				}
			}
		}
		player->currentIndex = player->prevIndex;
		return MapObject::box;
	default:
		mapObj[player->prevIndex] = MapObject::empty;
		player->moveCount -= 1;
		return MapObject::empty;
	}

}

sf::Vector2f Chapter::GetPlayerCurrentPos()
{
	return IndexToPos(player->currentIndex);
}

int Chapter::PosToIndex(sf::Vector2f pos)
{
	int rowIndex = (pos.y - offsetY - (size / 2)) / size;
	int columnIndex = (pos.x - offsetX - (size / 2)) / size;

	int index = rowIndex * col + columnIndex;
	return index;
}

sf::Vector2f Chapter::IndexToPos(int index)
{
	int rowIndex = index / col;
	int columnIndex = index % col; 
	
	float x = offsetX + (columnIndex * size) + size / 2;
	float y = offsetY + (rowIndex * size) + size / 2;

	return sf::Vector2f(x, y);
}

void Chapter::SetObject(int index, MapObject obj)
{
	mapObj[index] = obj;
	switch (obj)
	{
	case Chapter::MapObject::empty:
		break;
	case Chapter::MapObject::wall:
		break;
	case Chapter::MapObject::player:
		player = new Player("Player");
		player->SetTexture("Sprite/assets100V20057.png");
		player->SetOrigin(Origins::SELF);
		player->SetPosition(IndexToPos(index));
		player->Init();
		AddGo(player, Layers::World);
		player->sortOrder = 2;
		break;
	case Chapter::MapObject::demon:
		demon = new Demon("Demon");
		demon->SetTexture("Sprite/pandemonica_finalModel0010.png");
		demon->SetOrigin(Origins::SELF);
		demon->SetPosition(IndexToPos(index));
		demon->Init();
		AddGo(demon, Layers::World);
		break;
	case Chapter::MapObject::skeleton:
		skeleton = new Skeleton("Skeleton");
		skeleton->SetTexture("Sprite/assets100V20235.png");
		skeleton->currentIndex = skeleton->prevIndex = index;
		skeleton->SetOrigin(Origins::SELF);
		skeleton->SetPosition(IndexToPos(index));
		skeleton->Init();
		skeletonList.push_back(skeleton);
		AddGo(skeleton, Layers::World);
		break;
	case Chapter::MapObject::box:
		box = new Box("Box");
		box->SetTexture("Sprite/boxExport0001.png");
		box->currentIndex = box->prevIndex = index;
		box->SetPosition(IndexToPos(index));
		box->SetOrigin(Origins::SELF);
		box->Init();
		boxList.push_back(box);
		AddGo(box, Layers::World);
		//box->sortOrder = 1;
		break;
	case Chapter::MapObject::key:
		break;
	case Chapter::MapObject::lockbox:
		break;
	default:
		break;
	}
}

void Chapter::Update(float dt)
{
	Scene::Update(dt);

	moveCount->SetString(std::to_string(player->moveCount));

	if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
	{
		isPause = true;
		FRAMEWORK.SetTimeScale(0.f); //�Ͻ������Ҷ� ���ߴ°� �����ϱ� (Ű �Է� ������ �ִϸ��̼� ����� ���߰� ������)
		pause->SetActive(true);
	}

	if (FRAMEWORK.GetTimeScale() == 1.f)
	{
		isPause = false;
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
		PlayTransition();
	}

	/////////////////�׽�Ʈ��//////////////////
	if (InputMgr::GetKeyDown(sf::Keyboard::F3))
	{
		collectDemon->SetActive(true);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::F4))
	{
		player->OnDie();
	}
	//////////////////////////////////////////

	if (isDemonGet && !collectDemon->GetActive()) //isDemonGet - demon ȹ���� ó�� ���� / collectDemonâ�� �ȿ��������� ����
	{
		collectDemon->SetActive(true);
		isDemonGet = false;
	}

	if (!isDemonGet && collectDemon->GetAnswerSelect() && !collectDemon->GetActive()) //demon�� ȹ���ϰ� ����, �������� correct�� ������ collectDemonâ�� ���������� ����
	{
		player->SetOrigin(Origins::SELF);
		player->GetDemon();
		collectDemon->SetAnswerSelect(false);
	}
}

void Chapter::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);

	window.setView(worldView);
	window.draw(grid);
}