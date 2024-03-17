#include "pch.h"
#include "Chapter.h"
#include "Player.h"
#include "Demon.h"
#include "Skeleton.h"
#include "Box.h"
#include "Thorn.h"
#include "Key.h"
#include "LockBox.h"
#include "TextGo.h"
#include "CollectDemon.h"
#include "Pause.h"
#include "Advice.h"
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
	uiDemonRight->SetFlipX(true);
	AddGo(uiDemonRight, Layers::Ui);

	uiMoveCount = new TextGo("MoveCount");
	uiMoveCount->Set(fontResMgr.Get("Font/Amiri-Regular.ttf"), "23", 100, sf::Color::White);
	uiMoveCount->SetOrigin(Origins::MC);
	uiMoveCount->SetPosition({IndexToPos(134).x + size / 2.f, IndexToPos(134).y - size / 20.f });
	AddGo(uiMoveCount, Layers::Ui);

	currentStage = new TextGo("Test");
	currentStage->Set(fontResMgr.Get("Font/alphabetR.ttf"), "I", 90, sf::Color::White);
	currentStage->SetOrigin(Origins::MC);
	currentStage->SetPosition({ IndexToPos(149).x + size / 2.f, IndexToPos(149).y + size / 7.f });
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

	mapObj.resize(col * row, MapObject::empty);

	pause = new Pause("Pause");
	pause->sortLayer = 2;
	AddGo(pause, Layers::Ui);
	pause->SetActive(false);

	adviceTab = new Advice("Advice");
	adviceTab->sortLayer = 2;
	AddGo(adviceTab, Layers::Ui);
	adviceTab->SetActive(false);

	collectDemon = new CollectDemon("Collect");
	collectDemon->sortLayer = 1;
	AddGo(collectDemon, Layers::Ui);
	collectDemon->SetActive(false);

	SetUiActive(true);

	transition = new Transition("Transition");
	AddGo(transition, Layers::Ui);

	dustSprite.setTexture((RES_MGR_TEXTURE.Get("Texture2D/invisible.png")));
	dustSprite.setOrigin({ dustSprite.getLocalBounds().width * 0.5f, dustSprite.getLocalBounds().height * 0.5f });
	dustSprite.setPosition(0.f, 0.f);
	dustAnimator.SetTarget(&dustSprite);

	kickSprite.setTexture((RES_MGR_TEXTURE.Get("Texture2D/invisible.png")));
	kickSprite.setOrigin({ kickSprite.getLocalBounds().width, kickSprite.getLocalBounds().height });
	kickSprite.setPosition(0.f, 0.f);
	kickAnimator.SetTarget(&kickSprite);

	bloodSprite.setTexture((RES_MGR_TEXTURE.Get("Texture2D/invisible.png")));
	bloodSprite.setOrigin({ bloodSprite.getLocalBounds().width + 50.f, bloodSprite.getLocalBounds().height});
	bloodSprite.setPosition(0.f, 0.f);
	bloodAnimator.SetTarget(&bloodSprite);

	lovePlosionSprite.setTexture((RES_MGR_TEXTURE.Get("Texture2D/invisible.png")));
	lovePlosionSprite.setOrigin({ lovePlosionSprite.getLocalBounds().width + 50.f, lovePlosionSprite.getLocalBounds().height + 80.f});
	lovePlosionSprite.setPosition(0.f, 0.f);
	lovePlosionAnimator.SetTarget(&lovePlosionSprite);

	int stage = 1;

	Scene::Init();
}

void Chapter::Release()
{
	Scene::Release();
}

void Chapter::Enter()
{
	if (SCENE_MGR.CheckPrevScene() != SceneIds::CHAPTER)
	{
		SOUND_MGR.PlayBgm("AudioClip/Vitality.wav", false);
	}

	mapObj.resize(col * row, MapObject::empty);

	SetUiActive(true);
	backColor->sortOrder = -1;
	ResortGo(backColor);
	sf::Vector2f windowSize = (sf::Vector2f)FRAMEWORK.GetWindowSize();
	worldView.setSize(windowSize);
	worldView.setCenter(windowSize * 0.5f);
	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);
	
	switch (stage)
	{
	case 1:
		uiMoveCount->SetString("23");
		moveCount = 23;
		currentStage->SetString("I");
		background->SetTexture("PlusSprite/chapterBG0001.png");
		background->SetPosition({ 0.f, 0.f });
		break;
	case 2:
		uiMoveCount->SetString("24");
		moveCount = 24;
		currentStage->SetString("II");
		background->SetTexture("PlusSprite/chapterBG0002.png");
		background->SetPosition({ 0.f, 0.f });
		break;
	case 3:
		uiMoveCount->SetString("32");
		moveCount = 32;
		currentStage->SetString("III");
		background->SetTexture("Texture2D/chapterBG0003_edit.png");
		background->SetPosition({ -50.f, 50.f });
		break;
	case 4:
		uiMoveCount->SetString("23");
		moveCount = 23;
		currentStage->SetString("IV");
		background->SetTexture("Texture2D/chapterBG0004.png");
		background->SetPosition({ -50.f, 50.f });
		break;
	case 5:
		uiMoveCount->SetString("23");
		moveCount = 23;
		currentStage->SetString("V");
		background->SetTexture("Texture2D/chapterBG0005.png");
		background->SetPosition({ -50.f, 50.f });
		break;
	case 6:
		uiMoveCount->SetString("43");
		moveCount = 43;
		currentStage->SetString("VI");
		background->SetTexture("Texture2D/chapterBG0006.png");
		background->SetPosition({0.f,0.f });
		break;
	case 7:
		uiMoveCount->SetString("32");
		moveCount = 32;
		currentStage->SetString("VII");
		background->SetTexture("Texture2D/chapterBG0007.png");
		background->SetPosition({ -50.f, 50.f });
		break;
	default:
		break;
	}
	SetMap();
	transition->PlayTransitionDown();
	Scene::Enter();
}

void Chapter::Exit()
{
	if (player != nullptr)
	{
		RemoveGo(player);
	}

	if (key != nullptr)
	{
		RemoveGo(key);
	}

	if (lockBox != nullptr)
	{
		RemoveGo(lockBox);
	}

	for (auto& dem : demonList)
	{
		if(dem != nullptr)
			RemoveGo(dem);
	}
	demonList.clear();

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

	for (auto& th : thornList)
	{
		if (th != nullptr)
			RemoveGo(th);
	}
	thornList.clear();

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

	for (int i = 0; i < row + 1; ++i)
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

	for (int i = 0; i < col + 1; ++i)
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

void Chapter::SetMapLayout()
{
	switch (stage)
	{
	case 1:
		mapLayout =
		{
			"WWWWWWWWWWWWWWWWWWW",
			"WWWWWWWWWWWWWWWWWWW",
			"WWWWWWWWWWEPWWWWWWW",
			"WWWWWWWEESEEWWWWWWW",
			"WWWWWWWESESWWWWWWWW",
			"WWWWWWEEWWWWWWWWWWW",
			"WWWWWWEBEEBEWWWWWWW",
			"WWWWWWEBEBEEDWWWWWW",
			"WWWWWWWWWWWWWWWWWWW",
			"WWWWWWWWWWWWWWWWWWW",
		};
		break;
	case 2:
		mapLayout =
		{
			"WWWWWWWWWWWWWWWWWWW",
			"WWWWWWWWWWWWWWWWWWW",
			"WWWWWWWEEEEWWWWWWWW",
			"WWWWWWWEWTTEEWWWWWW",
			"WWWWWWETWWBBBWWWWWW",
			"WWWWWWEEWWETEWWWWWW",
			"WWWWWWPEWWESEWWWWWW",
			"WWWWWWWWWWDESWWWWWW",
			"WWWWWWWWWWWWWWWWWWW",
			"WWWWWWWWWWWWWWWWWWW",
		};
		break;
	case 3:
		mapLayout =
		{
			"WWWWWWWWWWWWWWWWWWW",
			"WWWWWWWWWWWWWWWWWWW",
			"WWWWWWWWDDDEWWWWWWW",
			"WWWWWWWWWWWLWWWWWWW",
			"WWWWWWWETTEEPWWWWWW",
			"WWWWWWWTWTWEEWWWWWW",
			"WWWWWWWEESTTWWWWWWW",
			"WWWWWKWTWTWEWWWWWWW",
			"WWWWWEEEEESEWWWWWWW",
			"WWWWWWWWWWWWWWWWWWW",
		};
		break;
	case 4:
		mapLayout =
	{
		"WWWWWWWWWWWWWWWWWWW",
		"WWWWWWWWWWWWWWWWWWW",
		"WWWWWWWWWWWWWWWWWWW",
		"WWWWWPWKEBWWWWWWWWW",
		"WWWWWEBTBELEWWWWWWW",
		"WWWWWBEBEBBEDWWWWWW",
		"WWWWWEBEBEBBEWWWWWW",
		"WWWWWWEBEBEWWWWWWWW",
		"WWWWWWWWWWWWWWWWWWW",
		"WWWWWWWWWWWWWWWWWWW",
	};
		break;
	case 5:
		mapLayout =
		{
			"WWWWWWWWWWWWWWWWWWW",
			"WWWWWWWWWWWWWWWWWWW",
			"WWWWWWWWWEDWWWWWWWW",
			"WWWWWWWWELBEWWWWWWW",
			"WWWWWWPWTEBEWWWWWWW",
			"WWWWWWEWETETWWWWWWW",
			"WWWWWWSWBBBBWWWWWWW",
			"WWWWWWTETEETWWWWWWW",
			"WWWWWWWWWWWKWWWWWWW",
			"WWWWWWWWWWWWWWWWWWW",
		};
		break;
	case 6:
		mapLayout =
		{
			"WWWWWWWWWWWWWWWWWWW",
			"WWWWWWWEPEWWWWWWWWW",
			"WWWWWWWBBBWWWWWWWWW",
			"WWWWWWEEEKWWWWWWWWW",
			"WWWWWWWTBEEWWWWWWWW",
			"WWWWWWWSWBBEEWWWWWW",
			"WWWWWWWEEBESWWWWWWW",
			"WWWWWWWWWWLBEWWWWWW",
			"WWWWWWWWWWEDWWWWWWW",
			"WWWWWWWWWWWWWWWWWWW",
		};
		break;
	case 7:
		mapLayout =
		{
			"WWWWWWWWWWWWWWWWWWW",
			"WWWWWWWWWWWWWWWWWWW",
			"WWWWWWWWWDEWWWWWWWW",
			"WWWWWWWWWELEWWWWWWW",
			"WWWWWWEKWBBBWWWWWWW",
			"WWWWWWSBESBEWWWWWWW",
			"WWWWWWEWSEEPWWWWWWW",
			"WWWWWWTWWTWWWWWWWWW",
			"WWWWWWTTTTWWWWWWWWW",
			"WWWWWWWWWWWWWWWWWWW",
		};
		break;
	default:
		break;
	}
}

void Chapter::SetMap()
{
	SetMapLayout();

	for (int i = 0; i < mapLayout.size(); ++i)
	{
		for (int j = 0; j < mapLayout[i].length(); ++j)
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
			case'T': mapObj = MapObject::thorn;
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
	uiMoveCount->SetActive(active);
	currentStage->SetActive(active);
	advice->SetActive(active);
	restart->SetActive(active);
	background->SetActive(active);
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
		moveCount = 0;
		isDemonGet = true;
		return MapObject::demon;
	case MapObject::skeleton:
		for (auto& skull : skeletonList)
		{
			if (skull->GetCurrentIndex() == curr)
			{
				kickSprite.setPosition(IndexToPos(curr));
				kickAnimator.Play("Tables/player_kickEffect.csv");
				skull->prevIndex = skull->currentIndex;
				skull->currentIndex += moveAmount;
				if (mapObj[skull->currentIndex] == MapObject::wall ||
					mapObj[skull->currentIndex] == MapObject::box)
				{
					SOUND_MGR.PlaySfx("AudioClip/enemy_die_01.wav");
					SkeletonDead* skeletonDestroy = new SkeletonDead("Skeleton Dead Animation");
					skeletonDestroy->Init();
					skeletonDestroy->Reset();
					skeletonDestroy->SetPosition(IndexToPos(curr));
					AddGo(skeletonDestroy, Layers::World);

					skull->SetActive(false);
					deadSkeletonList.push_back(skull);
					mapObj[skull->prevIndex] = MapObject::empty;
					skeletonList.remove(skull);
					moveCount -= 1;
					if (mapObj[prev] == MapObject::thorn)
					{
						moveCount -= 1;
						bloodSprite.setPosition(IndexToPos(prev));
						bloodAnimator.Play("Tables/player_blood.csv");
					}
					break;
				}
				else if (mapObj[skull->currentIndex] == MapObject::skeleton)
				{
					SOUND_MGR.PlaySfx("AudioClip/enemy_die_01.wav");
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
					moveCount -= 1;
					if (mapObj[prev] == MapObject::thorn)
					{
						moveCount -= 1;
						bloodSprite.setPosition(IndexToPos(prev));
						bloodAnimator.Play("Tables/player_blood.csv");
					}
					break;
				}
				else if (mapObj[skull->currentIndex] == MapObject::demon ||
					mapObj[skull->currentIndex] == MapObject::key ||
					mapObj[skull->currentIndex] == MapObject::lockbox)
				{
					skull->currentIndex = skull->prevIndex;
					moveCount -= 1;
					if (mapObj[prev] == MapObject::thorn)
					{
						moveCount -= 1;
						bloodSprite.setPosition(IndexToPos(prev));
						bloodAnimator.Play("Tables/player_blood.csv");
					}
					break;
				}
				else if (mapObj[skull->currentIndex] == MapObject::thorn)
				{
					SOUND_MGR.PlaySfx("AudioClip/enemy_die_01.wav");
					SkeletonDead* skeletonDestroy = new SkeletonDead("Skeleton Dead Animation");
					skeletonDestroy->Init();
					skeletonDestroy->Reset();
					skeletonDestroy->SetPosition(IndexToPos(curr));
					AddGo(skeletonDestroy, Layers::World);

					skull->SetActive(false);
					deadSkeletonList.push_back(skull);
					mapObj[skull->prevIndex] = MapObject::empty;
					mapObj[skull->currentIndex] = MapObject::thorn;
					skeletonList.remove(skull);
					moveCount -= 1;
					if (mapObj[prev] == MapObject::thorn)
					{
						moveCount -= 1;
						bloodSprite.setPosition(IndexToPos(prev));
						bloodAnimator.Play("Tables/player_blood.csv");
					}
					break;
				}
				else if (mapObj[skull->currentIndex] == MapObject::empty)
				{
					SOUND_MGR.PlaySfx("AudioClip/enemy_kick_01.wav");
					skull->SetPosition(IndexToPos(skull->currentIndex));
					mapObj[skull->prevIndex] = MapObject::player;
					mapObj[skull->currentIndex] = MapObject::skeleton;
					skull->animator.Play("Tables/Skeleton_Damage.csv");
					skull->animator.PlayQueue("Tables/Skeleton_Idle.csv");
					moveCount -= 1;
					if (mapObj[prev] == MapObject::thorn)
					{
						moveCount -= 1;
						bloodSprite.setPosition(IndexToPos(prev));
						bloodAnimator.Play("Tables/player_blood.csv");
					}
					break;
				}
			}
		}
		player->currentIndex = player->prevIndex;
		return MapObject::skeleton;
	case MapObject::box:
		if (mapObj[prev] == MapObject::thorn)
		{
			moveCount -= 1;
			bloodSprite.setPosition(IndexToPos(prev));
			bloodAnimator.Play("Tables/player_blood.csv");
		}
		for (auto& b : boxList)
		{
			if (b->GetCurrentIndex() == curr)
			{
				kickSprite.setPosition(IndexToPos(curr));
				kickAnimator.Play("Tables/player_kickEffect.csv");
				b->prevIndex = b->currentIndex;
				b->currentIndex += moveAmount;
				if (mapObj[b->currentIndex] == MapObject::wall)
				{
					b->currentIndex = b->prevIndex;
					mapObj[b->currentIndex] = MapObject::box;
					moveCount -= 1;
					break;
				}
				else if (mapObj[b->currentIndex] == MapObject::demon ||
					mapObj[b->currentIndex] == MapObject::box ||
					mapObj[b->currentIndex] == MapObject::key ||
					mapObj[b->currentIndex] == MapObject::lockbox ||
					mapObj[b->currentIndex] == MapObject::skeleton)
				{
					b->currentIndex = b->prevIndex;
					moveCount -= 1;
					break;
				}
				else if (mapObj[b->currentIndex] == MapObject::empty)
				{
					b->SetPosition(IndexToPos(b->currentIndex));
					mapObj[b->prevIndex] = MapObject::player;
					mapObj[b->currentIndex] = MapObject::box;
					moveCount -= 1;
					break;
				}
			}
		}
		player->currentIndex = player->prevIndex;
		return MapObject::box;
	case MapObject::thorn:
		for (auto& th : thornList)
		{
			if (th->GetCurrentIndex() == curr)
			{
				bloodSprite.setPosition(IndexToPos(curr));
				bloodAnimator.Play("Tables/player_blood.csv");
				mapObj[player->currentIndex] = MapObject::thorn;
				moveCount -= 2;
				return MapObject::thorn;
			}
		}
	default:
		moveCount -= 1;
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
		player->currentIndex = index;
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
		demonList.push_back(demon);
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
		box->SetTexture("Sprite/box_edit.png");
		box->currentIndex = box->prevIndex = index;
		box->SetPosition(IndexToPos(index));
		box->SetOrigin(Origins::BOX);
		box->Init();
		boxList.push_back(box);
		AddGo(box, Layers::World);
		break;
	case Chapter::MapObject::key:
		key = new Key("KEY");
		key->SetTexture("Sprite/assets100V20104.png");
		key->SetOrigin(Origins::KEY);
		key->currentIndex = index;
		key->SetPosition(IndexToPos(index));
		key->Init();
		AddGo(key, Layers::World);
		break;
	case Chapter::MapObject::lockbox:
		lockBox = new LockBox("LockBox");
		lockBox->SetTexture("Sprite/backup_lockbox.png");
		lockBox->SetOrigin(Origins::SELF);
		lockBox->currentIndex = index;
		lockBox->SetPosition(IndexToPos(index));
		lockBox->Init();
		AddGo(lockBox, Layers::World);
		break;
	case Chapter::MapObject::thorn:
		thorn = new Thorn("thorn");
		thorn->SetTexture("Sprite/assets100V20116.png");
		thorn->currentIndex = thorn->prevIndex = index;
		thorn->SetPosition(IndexToPos(index));
		thorn->SetOrigin(Origins::MC);
		thorn->Init();
		thornList.push_back(thorn);
		AddGo(thorn, Layers::World);
		break;
	default:
		break;
	}
}

void Chapter::Update(float dt)
{
	Scene::Update(dt);
	dustAnimator.Update(dt);
	kickAnimator.Update(dt);
	bloodAnimator.Update(dt);
	lovePlosionAnimator.Update(dt);

	uiMoveCount->SetString(std::to_string(moveCount));

	if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
	{
		isPause = true;
		FRAMEWORK.SetTimeScale(0.f);
		pause->SetActive(true);
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::L))
	{
		SOUND_MGR.PlaySfx("AudioClip/dialogue_start_01.wav");
		isAdvice = true;
		adviceTab->SetActive(true);
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
		transition->SetChangeScene(SceneIds::CHAPTER);
		transition->PlayTransitionUp();
	}

	if (isDemonGet && !collectDemon->GetActive())
	{
		SOUND_MGR.PlaySfx("AudioClip/button_menu_confirm_01.wav");
		collectDemon->Init();
		collectDemon->Reset();
		collectDemon->SetActive(true);
		isDemonGet = false;
	}

	if (!isDemonGet && collectDemon->GetAnswerSelect() && !collectDemon->GetActive())
	{
		player->SetOrigin(Origins::SELF);
		player->GetDemon();
		lovePlosionSprite.setPosition(demon->GetPosition());
		lovePlosionAnimator.Play("Tables/demon_LovePlosion.csv");
		collectDemon->SetAnswerSelect(false);
	}
}

void Chapter::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);

	window.setView(worldView);
	window.draw(grid);
	window.draw(dustSprite);
	window.draw(kickSprite);
	window.draw(bloodSprite);
	window.draw(lovePlosionSprite);
}