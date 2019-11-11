#pragma once
#include <iostream>
#include <windows.h>

class Clock {
private:
	double PCFreq;
	__int64 CounterStart;

public:
	Clock()
	{
		this->PCFreq = 0.0;
		this->CounterStart = 0;
	}


	double getCounter()
	{
		LARGE_INTEGER li;
		QueryPerformanceCounter(&li);
		return double(li.QuadPart - CounterStart) / PCFreq;
	}

	void startCounter()
	{
		LARGE_INTEGER li;
		if (!QueryPerformanceFrequency(&li))
			std::cout << "Licznik nie dziala.";

		PCFreq = double(li.QuadPart) / 1000000.0;

		QueryPerformanceCounter(&li);
		CounterStart = li.QuadPart;
	}
};