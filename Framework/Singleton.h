#pragma once

//TO-DO : 싱글턴 객체 보장하기


template <typename T>
class Singleton
{
protected:
	Singleton() = default;
	virtual ~Singleton() = default;

	Singleton(const Singleton&) = delete;
	Singleton(Singleton&&) = delete;
	Singleton& operator=(const Singleton&) = delete;
	Singleton& operator=(Singleton&&) = delete;

public:
	static T& Instance()
	{
		static T instance; //static 지역변수
		return instance;
	}
};