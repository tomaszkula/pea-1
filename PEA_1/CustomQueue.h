#pragma once
#include <iostream>
#include "QueueElement.cpp"

class CustomQueue
{
private:
	QueueElement *queue;
	int n, maxSize;

public:
	CustomQueue();
	CustomQueue(int n);
	CustomQueue(QueueElement *tab, int n);
	~CustomQueue();

	void Enqueue(QueueElement item);
	QueueElement Dequeue();
	bool IsEmpty();
	void Display();
};

