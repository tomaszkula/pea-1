#include "CustomQueue.h"

CustomQueue::CustomQueue()
{
	maxSize = 5;

	queue = new QueueElement[maxSize];
	n = 0;
}

CustomQueue::CustomQueue(int n)
{
	maxSize = n;

	queue = new QueueElement[maxSize];
	this->n = 0;
}

CustomQueue::CustomQueue(QueueElement *tab, int n)
{
	maxSize = n + 2;

	queue = new QueueElement[maxSize];
	for (int i = 0; i < n; i++)
	{
		queue[i] = tab[i];
	}
	this->n = n;
}

CustomQueue::~CustomQueue()
{
	delete [] queue;
}

void CustomQueue::Enqueue(QueueElement item)
{
	if (n < maxSize)
	{
		queue[n] = item;
	}
	else
	{
		maxSize += 100;
		QueueElement *newQueue = new QueueElement[maxSize];
		for (int i = 0; i < n; i++)
		{
			newQueue[i] = queue[i];
		}
		newQueue[n] = item;

		delete[] queue;
		queue = newQueue;
	}

	n++;
}

QueueElement CustomQueue::Dequeue()
{
	QueueElement item = queue[0];
	for (int i = 0; i < n - 1; i++)
	{
		queue[i] = queue[i + 1];
	}
	n--;
	return item;
}

bool CustomQueue::IsEmpty()
{
	if (n < 1) return true;
	else return false;
}

void CustomQueue::Display()
{
	for (int i = 0; i < n; i++)
	{
		std::cout << queue[i].id << " ";
	}
	std::cout << "\n";
}