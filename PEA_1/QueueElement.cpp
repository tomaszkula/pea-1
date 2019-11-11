struct QueueElement
{
	int id, level, bound, distance;
	int *path, n;

	QueueElement()
	{
		path = new int[10];
		this->n = 10;
	}

	QueueElement(int n)
	{
		path = new int[10];
		this->n = 10;
	}

	QueueElement(const QueueElement &v)
	{
		id = v.id;
		level = v.level;
		bound = v.bound;
		distance = v.distance;

		n = v.n;
		path = new int[n];
		for (int i = 0; i < n; i++) path[i] = v.path[i];
	}

	bool IsPathElement(int id)
	{
		for (int i = 0; i < n; i++)
		{
			if (path[i] == id) return true;
		}
		return false;
	}
};