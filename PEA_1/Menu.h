#pragma once
#include "Graph.h"
#include "Clock.cpp"

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <time.h>

class Menu
{
private:
	int optToQuit;
	int opt = 0;
	Graph *g;

	void ReadFromFile();
	void GenerateRandomly();
	void GenerateRandomlyData(int, int, int);
	void DisplayData();
	void Measure();
	void DisplayBruteForce();
	void DisplayBranchAndBound();
	void DisplayDynamicProgramming();

public:
	Menu(int optToQuit = 0);
	~Menu();
	void SetOptionToQuit(int);
	int GetOptionToQuit();
	void Choose();
	int GetOption();
	void DoTask();
	void Display();
};

