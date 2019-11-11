#pragma once
//#include "DPElement.cpp"
#include "Clock.cpp"

#include <iostream>
#include <string>
#include <sstream>
#include <queue>
#include <vector>

enum AlgorithmType
{
	BruteForce, BranchAndBound_DFS, DynamicProgramming
};

class Graph
{
private:
	int nodesCount, **distances;

	Clock clock;
	int MinDistanceFrom(int);
	int SecondDistanceFrom(int);

public:
	Graph(int nodesCount);
	~Graph();
	void CompleteDistancesRow(int rowId, std::string row);
	void Display();
	void BruteForce();
	void BruteForce(int*, int, int&, int*);
	void BranchAndBound_DFS();
	void BranchAndBound_DFS(int*, int, int, int, int&, int*);
	void DynamicProgramming(bool);
	int DynamicProgramming(int, int, std::vector<std::vector<std::pair<int, std::vector<int>>>>&, bool);
	void Test(Clock&, int);
};

