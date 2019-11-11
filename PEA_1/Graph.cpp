#include "Graph.h"

Graph::Graph(int nodesCount)
{
	this->nodesCount = nodesCount;

	distances = new int * [nodesCount];
	for (int i = 0; i < nodesCount; i++)
	{
		distances[i] = new int[nodesCount];
	}
}

Graph::~Graph()
{
	for (int i = 0; i < nodesCount; i++)
	{
		delete[] distances[i];
	}
	delete[] distances;
}

void Graph::CompleteDistancesRow(int rowId, std::string row)
{
	std::istringstream iss(row);
	for (int i = 0; i < nodesCount; i++)
	{
		iss >> distances[rowId][i];
	}
}

void Graph::Display()
{
	for (int i = 0; i < nodesCount; i++)
	{
		for (int j = 0; j < nodesCount; j++)
		{
			std::cout << distances[i][j] << " ";
		}
		std::cout << "\n";
	}
}

int Graph::MinDistanceFrom(int v)
{
	int min = INT_MAX;
	for (int i = 0; i < nodesCount; i++)
	{
		if (distances[v][i] < min && i != v) min = distances[v][i];
	}
	return min;
}

int Graph::SecondDistanceFrom(int v)
{
	int min = INT_MAX, second = INT_MAX;
	for (int i = 0; i < nodesCount; i++)
	{
		if (i == v) continue;

		if (distances[v][i] < min)
		{
			min = distances[v][i];
			second = min;
		}
		else if (distances[v][i] <= second && distances[v][i] != min) second = distances[v][i];
	}
	return second;
}

void Graph::BruteForce()
{
	int *tab = new int[nodesCount];
	for (int i = 0; i < nodesCount; i++) tab[i] = i;

	int level = 1;
	int minDistance = INT_MAX;
	int *minPath = new int[nodesCount + 1];
	BruteForce(tab, level, minDistance, minPath);

	std::cout << "Dystans(waga): " << minDistance << "\n";
	std::cout << "Sciezka: ";
	for (int i = 0; i < nodesCount + 1; i++) std::cout << minPath[i] << " ";
	std::cout << "\n";

	delete[] tab;
	delete[] minPath;
}

void Graph::BruteForce(int *tab, int level, int& minDistance, int *minPath)
{
	if (level == nodesCount)
	{
		if (distances[tab[level - 1]][0] < 0) return;

		int fullDistance = 0;
		for (int i = 0; i < nodesCount - 1; i++) fullDistance += distances[tab[i]][tab[i + 1]];
		fullDistance += distances[tab[level - 1]][0];

		if (fullDistance < minDistance)
		{
			for (int i = 0; i < nodesCount + 1; i++) minPath[i] = tab[i];
			minPath[nodesCount] = 0;

			minDistance = fullDistance;
		}
	}
	else
	{
		for (int i = level; i < nodesCount; i++)
		{
			if (distances[tab[level - 1]][tab[i]] < 0) continue;

			int temp = tab[level];
			tab[level] = tab[i];
			tab[i] = temp;

			BruteForce(tab, level + 1, minDistance, minPath);

			temp = tab[level];
			tab[level] = tab[i];
			tab[i] = temp;
		}
	}
}

void Graph::BranchAndBound_DFS()
{
	int *tab = new int[nodesCount];
	for (int i = 0; i < nodesCount; i++) tab[i] = i;

	int bound = 0;
	for (int i = 0; i < nodesCount; i++) bound += ceil((MinDistanceFrom(i) + SecondDistanceFrom(i)) / 2.0);

	int level = 1;
	int distance = 0;
	int minDistance = INT_MAX;
	int *minPath = new int[nodesCount + 1];

	BranchAndBound_DFS(tab, level, bound, distance, minDistance, minPath);

	std::cout << "Dystans(waga): " << minDistance << "\n";
	std::cout << "Sciezka: ";
	for (int i = 0; i < nodesCount + 1; i++) std::cout << minPath[i] << " ";
	std::cout << "\n";

	delete[] tab;
	delete[] minPath;
}

void Graph::BranchAndBound_DFS(int *tab, int level, int bound, int distance, int& minDistance, int *minPath)
{
	if (level == nodesCount)
	{
		if (distances[tab[level - 1]][0] < 0) return;

		//sprawdzenie czy wynik jest mniejszy na samym koncu
		int fullDistance = distance + distances[tab[level - 1]][0];
		if (fullDistance < minDistance)
		{
			for (int i = 0; i < nodesCount; i++) minPath[i] = tab[i];
			minPath[nodesCount] = 0;

			minDistance = fullDistance;
		}
	}
	else
	{
		for (int i = level; i < nodesCount; i++)
		{
			if (distances[tab[level - 1]][tab[i]] < 0) continue;

			//uregulowanie granicy
			int tempBound = bound;
			if (level == 1) bound -= ceil((MinDistanceFrom(0) + MinDistanceFrom(tab[i])) / 2.0);
			else if (level == nodesCount - 1) bound -= ceil((SecondDistanceFrom(tab[level - 1]) + SecondDistanceFrom(0)) / 2.0);
			else bound -= ceil((SecondDistanceFrom(tab[level - 1]) + MinDistanceFrom(tab[i])) / 2.0);

			//dystans przebyty od 0 do i
			distance += distances[tab[level - 1]][tab[i]];

			//sprawdzenie czy jest sens dalej sprawdzac
			//najmniejsza mozliwa granica + aktualny przebyty dystans < najmniejszy dystans jaki znaleziono
			if (bound + distance < minDistance)
			{
				int temp = tab[level];
				tab[level] = tab[i];
				tab[i] = temp;

				BranchAndBound_DFS(tab, level + 1, bound, distance, minDistance, minPath);

				temp = tab[level];
				tab[level] = tab[i];
				tab[i] = temp;
			}

			distance -= distances[tab[level - 1]][tab[i]];
			bound = tempBound;
		}
	}
}

void Graph::DynamicProgramming(bool displayPath)
{
	int vStart = 0;
	int visited = 1;

	std::vector<std::vector<std::pair<int, std::vector<int>>>> knownDistances(nodesCount);
	for (auto& kD : knownDistances)
	{
		kD = std::vector<std::pair<int, std::vector<int>>>((1 << nodesCount) - 1, std::make_pair(INT_MAX, std::vector<int>()));
	}

	int minDistance = DynamicProgramming(vStart, visited, knownDistances, displayPath);

	std::cout << "Dystans(waga): " << minDistance << "\n";
	if (displayPath)
	{
		int *minPath = new int[nodesCount + 1];
		minPath[0] = 0;
		minPath[nodesCount] = 0;
		for (int i = 0; i < nodesCount - 1; i++) minPath[i + 1] = knownDistances[0][1].second[i];

		std::cout << "Sciezka: ";
		for (int i = 0; i < nodesCount + 1; i++) std::cout << minPath[i] << " ";
		std::cout << "\n";
	}
}

int Graph::DynamicProgramming(int vStart, int visited, std::vector<std::vector<std::pair<int, std::vector<int>>>>& knownDistances, bool displayPath)
{
	if (visited == (1 << nodesCount) - 1) return distances[vStart][0];
	if (knownDistances[vStart][visited].first != INT_MAX) return knownDistances[vStart][visited].first;

	for (int i = 0; i < nodesCount; i++)
	{
		if (i == vStart || visited & (1 << i)) continue;

		int distance = distances[vStart][i] + DynamicProgramming(i, visited | (1 << i), knownDistances, displayPath);
		std::vector<int> path;
		if (displayPath)
		{
			path.push_back(i);
			path.insert(path.end(), knownDistances[i][visited | (1 << i)].second.begin(), knownDistances[i][visited | (1 << i)].second.end());
		}

		if (distance < knownDistances[vStart][visited].first)
		{
			knownDistances[vStart][visited].first = distance;
			knownDistances[vStart][visited].second = path;
		}
	}

	return knownDistances[vStart][visited].first;
}

void Graph::Test(Clock& c, int idAlgorithm)
{
	int *tab = new int[nodesCount];
	for (int j = 0; j < nodesCount; j++) tab[j] = j;
	int minDistance = INT_MAX;
	int *minPath = new int[nodesCount + 1];

	switch (idAlgorithm)
	{
		case 1:
			c.startCounter();
			BruteForce(tab, 1, minDistance, minPath);
			break;

		case 2:
			int bound; bound = 0;
			for (int j = 0; j < nodesCount; j++) bound += ceil((MinDistanceFrom(j) + SecondDistanceFrom(j)) / 2.0);

			c.startCounter();
			BranchAndBound_DFS(tab, 1, bound, 0, minDistance, minPath);
			break;

		case 3:
			int vStart = 0;
			int visited = 1;
			std::vector<std::vector<std::pair<int, std::vector<int>>>> knownDistances(nodesCount);
			for (auto& kD : knownDistances)
			{
				kD = std::vector<std::pair<int, std::vector<int>>>((1 << nodesCount) - 1, std::make_pair(INT_MAX, std::vector<int>()));
			}

			c.startCounter();
			int minDistance = DynamicProgramming(vStart, visited, knownDistances, false);
			break;
	}

	delete[] tab;
	delete[] minPath;
}