#pragma once
#include "Singleton.h"

//1. �ʱ�ȭ / ���η��� / (�޸�) ����
//2. �ð� ���� ���
//3. ...Mgr �ʱ�ȭ �� ���� ���� ����

class Framework : public Singleton<Framework>
{
	friend Singleton<Framework>;
	//TO-DO : �ٸ� Mgr�鵵 friend�����ϰ� ������ ������ֱ�

protected:
	Framework() = default;
	virtual ~Framework() = default;

	sf::RenderWindow window;
	sf::Vector2i windowSize;

	sf::Clock clock;
	float timeScale = 1.f;

	sf::Time realTime; //���� ���ۺ��� ��� �ð�
	sf::Time time; //���� ���ۺ��� ��� �ð� (timeScale ����� �ð�)

	sf::Time realDeltaTime;
	sf::Time deltaTime;

public:
	sf::RenderWindow& GetWindow() { return window; } //�����ؼ� ��� ��(��?)
	const sf::Vector2i& GetWindowSize() const { return windowSize; }

	float GetDT() const { return deltaTime.asSeconds(); }
	float GetRealDT() const { return time.asSeconds(); }
	float GetTime() const { return realDeltaTime.asSeconds(); }
	float GetRealTime() const { return deltaTime.asSeconds(); }

	float GetTimeScale() const { return timeScale; }
	void SetTimeScale(float scale) { timeScale = scale; }

	virtual void Init(int width, int height, const std::string& name = "Timeber!"); //�ʱ�ȭ
	virtual void Do();
	virtual void Release();
};

#define FRAMEWORK (Singleton<Framework>::Instance())
