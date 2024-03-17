#pragma once
#include "Singleton.h"

//1. 초기화 / 메인루프 / (메모리) 정리
//2. 시간 관련 기능
//3. ...Mgr 초기화 및 정리 등의 관리

class Framework : public Singleton<Framework>
{
	friend Singleton<Framework>;

protected:
	Framework() = default;
	virtual ~Framework() = default;

	sf::RenderWindow window;
	sf::Vector2i windowSize;

	sf::Clock clock;
	float timeScale = 1.f;

	sf::Time realTime;
	sf::Time time;

	sf::Time realDeltaTime;
	sf::Time deltaTime;

	float fixedUpdateTime = 1.f;
	sf::Time fixedDeltaTime;

public:
	sf::RenderWindow& GetWindow() { return window; }
	const sf::Vector2i& GetWindowSize() const { return windowSize; }

	float GetDT() const { return deltaTime.asSeconds(); }
	float GetRealDT() const { return time.asSeconds(); }
	float GetTime() const { return realDeltaTime.asSeconds(); }
	float GetRealTime() const { return deltaTime.asSeconds(); }

	float GetTimeScale() const { return timeScale; }
	void SetTimeScale(float scale) { timeScale = scale; }

	void GameClose() {	window.close(); }

	virtual void Init(int width, int height, const std::string& name = "Helltaker");
	virtual void Do();
	virtual void Release();
};

#define FRAMEWORK (Singleton<Framework>::Instance())
