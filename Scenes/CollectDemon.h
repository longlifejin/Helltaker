#pragma once
#include "Scene.h"

class SpriteGo;
class TextGo;

class CollectDemon : public Scene
{
	enum class SelectLine
	{
		Correct,
		Wrong,
	};

protected:

	SpriteGo* background;
	SpriteGo* demon;
	
	TextGo* demonName;
	TextGo* demonLine1;
	TextGo* demonLine2;

	SpriteGo* select1;
	SpriteGo* select2;

	SpriteGo* booper;

	std::wstring panName = L"● 지친 악마, 판데모니카 ●";
	std::wstring pandLine1 = L"지옥 고객 서비스 센터의 판데모니카입니다.";
	std::wstring pandLine2 = L"무엇을 도와드릴까요?"; //TO-DO : 가운데 정렬하는 방법 찾아보기 ㅠ
	
	SelectLine currentSelect = SelectLine::Wrong;

public:
	CollectDemon(SceneIds id);
	virtual ~CollectDemon();

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

};

