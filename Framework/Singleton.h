#pragma once

//TO-DO : �̱��� ��ü �����ϱ�


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
		static T instance; //static ��������
		return instance;
	}
};