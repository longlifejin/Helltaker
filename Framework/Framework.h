#pragma once
#include "Singleton.h"

//1. 초기화 / 메인루프 / (메모리) 정리
//2. 시간 관련 기능
//3. ...Mgr 초기화 및 정리 등의 관리

class Framework : public Singleton<Framework>
{
	friend Singleton<Framework>;
	//TO-DO : 다른 Mgr들도 friend선언하고 생성자 만들어주기

protected:
	Framework() = default;
	virtual ~Framework() = default;

	sf::RenderWindow window;
	sf::Vector2i windowSize;

	sf::Clock clock;
	float timeScale = 1.f;

	sf::Time realTime; //게임 시작부터 경과 시간
	sf::Time time; //게임 시작부터 경과 시간 (timeScale 적용되 시간)

	sf::Time realDeltaTime;
	sf::Time deltaTime;

public:
	sf::RenderWindow& GetWindow() { return window; } //조심해서 써야 함(왜?)
	const sf::Vector2i& GetWindowSize() const { return windowSize; }

	float GetDT() const { return deltaTime.asSeconds(); }
	float GetRealDT() const { return time.asSeconds(); }
	float GetTime() const { return realDeltaTime.asSeconds(); }
	float GetRealTime() const { return deltaTime.asSeconds(); }

	float GetTimeScale() const { return timeScale; }
	void SetTimeScale(float scale) { timeScale = scale; }

	virtual void Init(int width, int height, const std::string& name = "Timeber!"); //초기화
	virtual void Do();
	virtual void Release();
};

#define FRAMEWORK (Singleton<Framework>::Instance())
