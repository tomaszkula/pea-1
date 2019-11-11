#include "Menu.h"

Menu::Menu(int optToQuit)
{
	SetOptionToQuit(optToQuit);
}

Menu::~Menu()
{
	delete g;
}

void Menu::SetOptionToQuit(int opt)
{
	optToQuit = opt;
}

int Menu::GetOptionToQuit()
{
	return optToQuit;
}

void Menu::Display()
{
	std::cout << "[PEA 1] [MENU]\n";
	std::cout << "[1] Wczytaj z pliku\n";
	std::cout << "[2] Wygeneruj losowo\n";
	std::cout << "[3] Wyswietl dane\n";
	std::cout << "[4] Pomiary do sprawozdania\n";
	std::cout << "[5] Przeglad zupelny(Brute Force)\n";
	std::cout << "[6] Metoda podzialu i ograniczen(B&B) - przeszukiwanie w glab(DFS)\n";
	std::cout << "[7] Programowanie dynamiczne\n";
	std::cout << "[" << GetOptionToQuit() << "] Wyjdz z programu\n";
}

void Menu::Choose()
{
	std::cout << "Wybierz opcje: ";
	std::cin >> opt;
}

int Menu::GetOption()
{
	return opt;
}

void Menu::DoTask()
{
	std::cout << "\n";

	switch (opt)
	{
		case 0:
			return;

		case 1:
			ReadFromFile();
			break;

		case 2:
			GenerateRandomly();
			break;

		case 3:
			DisplayData();
			break;

		case 4:
			Measure();
			break;

		case 5:
			DisplayBruteForce();
			break;

		case 6:
			DisplayBranchAndBound();
			break;

		case 7:
			DisplayDynamicProgramming();
			break;
	}

	std::cout << "\n";
}

void Menu::ReadFromFile()
{
	std::string fileName = "";
	std::cout << "Podaj nazwe pliku: ";
	std::cin >> fileName;

	std::fstream file;
	file.open(fileName, std::fstream::in);
	if (!file.is_open())
	{
		std::cout << "Podany plik nie istnieje lub zostal zle otworzony!\n";
		return;
	}

	int linesCount = 0, nodesCount = 0;
	std::string line;
	while (std::getline(file, line))
	{
		if (++linesCount == 1)
		{
			nodesCount = atoi(line.c_str());

			if (g) delete g;
			g = new Graph(nodesCount);
		}
		else
		{
			g->CompleteDistancesRow(linesCount - 2, line);
		}
	}
	file.close();

	std::cout << "Poprawnie zaladowano dane z pliku.\n";
	std::cout << "Ilosc wierzcholkow: " << nodesCount << "\n";
}

void Menu::GenerateRandomly()
{
	int n;
	std::cout << "Podaj ilosc miast(wierzcholkow): ";
	std::cin >> n;

	int a = 0, b = 50;
	std::cout << "Podaj punkt startowy zakresu: ";
	std::cin >> a;
	std::cout << "Podaj punkt koncowy zakresu: ";
	std::cin >> b;

	GenerateRandomlyData(n, a, b);
}

void Menu::GenerateRandomlyData(int n, int a, int b)
{
	srand(time(NULL));

	if (g)
	{
		delete g;
	}
	g = new Graph(n);

	for (int i = 0; i < n; i++)
	{
		std::string line = "";
		for (int j = 0; j < n; j++)
		{
			if (i == j)
			{
				line += "-1 ";
				continue;
			}

			int num = rand() % (b - a + 1) + a;
			line += std::to_string(num) + " ";
		}
		g->CompleteDistancesRow(i, line);
	}
}

void Menu::DisplayData()
{
	if (!g)
	{
		std::cout << "Brak danych do wyswietlenia!\n";
		return;
	}

	g->Display();
}

void Menu::Measure()
{
	int dataCount = 100; //ilosc instancji i ilosc prob danej instansji
	int bf[8] = { 6, 7, 8, 9, 10, 11, 12, 13}; //N dla bf;
	int bb[9] = { 6, 8, 10, 13, 15, 17, 18, 20, 21 }; //N dla b&b;
	int dp[7] = { 6, 10, 13, 15, 17, 20, 22}; //N dla DP;

	int a = 10, b = 99;
	Clock c;

	/*// BF
	std::cout << "BRUTE FORCE\n";
	for (int i = 0; i < 8; i++)
	{
		double time = 0.0;
		std::cout << "Instancja nr" << i + 1 << " - " << bf[i] << " wierzcholkow\n";
		for (int j = 0; j < dataCount; j++)
		{
			GenerateRandomlyData(bf[i], a, b);

			int minDistance = INT_MAX;
			c.startCounter();
			g->Test(c, 1);
			time += c.getCounter();
		}
		time /= 100.0;
		std::cout << "Sredni czas wykonywania sie algorytmu: " << time << "\n";
	}
	std::cout << "\n";*/

	// B&B
	std::cout << "BRANCH AND BOUND\n";
	for (int i = 0; i < 1; i++)
	{
		double time = 0.0;
		std::cout << "Instancja nr" << i + 1 << " - " << bb[i] << " wierzcholkow\n";
		for (int j = 0; j < dataCount; j++)
		{
			GenerateRandomlyData(bb[i], a, b);
			c.startCounter();
			g->Test(c, 2);
			time += c.getCounter();
		}
		time /= 100.0;
		std::cout << "Sredni czas wykonywania sie algorytmu: " << time << "\n";
	}
	std::cout << "\n";

	/*// DP
	std::cout << "PROGRAMOWANIE DYNAMICZNE\n";
	for (int i = 0; i < 7; i++)
	{
		double time = 0.0;
		std::cout << "Instancja nr" << i + 1 << " - " << dp[i] << " wierzcholkow\n";
		for (int j = 0; j < dataCount; j++)
		{
			GenerateRandomlyData(dp[i], a, b);
			c.startCounter();
			g->Test(c, 3);
			time += c.getCounter();
		}
		time /= 100.0;
		std::cout << "Sredni czas wykonywania sie algorytmu: " << time << "\n";
	}
	std::cout << "\n";*/
}

void Menu::DisplayBruteForce()
{
	if (!g)
	{
		std::cout << "Brak danych, na ktorych moznaby dzialac!\n";
		return;
	}

	std::cout << "Przeglad zupelny(Brute Force):\n";
	g->BruteForce();
}

void Menu::DisplayBranchAndBound()
{
	if (!g)
	{
		std::cout << "Brak danych, na ktorych moznaby dzialac!\n";
		return;
	}

	std::cout << "Metoda podzialu i ograniczen(B&B) - przeszukiwanie w glab(DFS):\n";
	g->BranchAndBound_DFS();
}

void Menu::DisplayDynamicProgramming()
{
	if (!g)
	{
		std::cout << "Brak danych, na ktorych moznaby dzialac!\n";
		return;
	}

	std::cout << "Programowanie dynamiczne:\n";
	g->DynamicProgramming(true);
}