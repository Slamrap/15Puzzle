#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <ctime>

#include "Node.h"
#include "SearchAlgorithms.h"
#include "Heuristics.h"

using namespace std;

/**
*   @brief  Checks if any game state is solvable
*
*   @param  currentConfig - current game state
*   @return True or False, respectively, if game state is solvable
*/
bool hasParity(vector<int> currentConfig) {
	int nInversions = 0;
	int blankSpaceRow = indexOfValue(0, currentConfig) / 4;

	for (int i = 0; i < 16; i++) {
		for (int j = i + 1; j < 16; j++) {
			if (currentConfig[i] > currentConfig[j] && currentConfig[j] != 0)
				nInversions++;
		}
	}
	return (blankSpaceRow % 2 != 0) == (nInversions % 2 == 0);
}

/**
*   @brief  Reads configuration, given by user input, and puts it into a vector   
*
*   @return vector containing configuration given by the user
*/
vector<int> insertConfig() {
	vector<int> v;
	int num;

	while (cin >> num) {
		v.push_back(num);
		if (cin.get() == '\n') 
			break;
	}
	return v;
}

/**
*   @brief  Menu for chosing which search algorithm, the user wants to use
*
*   @param  initialConfig  - initial state
*   @param  finalConfig - final state
*   @return the option that the user chose
*/
int menuSearches(vector<int> initialConfig, vector<int> finalConfig) {
	int option;
	
	cout << "" << endl;
	cout << "+-----------------------+" << endl;
	cout << "|                       |" << endl;
	cout << "|       Algorithms      |" << endl;
	cout << "|                       |" << endl;
	cout << "+-----------------------+" << endl;
	cout << "|        1. DFS         |" << endl;
	cout << "+-----------------------+" << endl;
	cout << "|        2. BFS         |" << endl;
	cout << "+-----------------------+" << endl;
	cout << "|        3. IDFS        |" << endl;
	cout << "+-----------------------+" << endl;
	cout << "|        4. GREEDY      |" << endl;
	cout << "+-----------------------+" << endl;
	cout << "|        5. A*          |" << endl;
	cout << "+-----------------------+" << endl;

	cout << "Select one of the options above [1-5]: ";
	cin >> option;

	cout << "" << endl;

	return option;
}

/**
*   @brief  Menu for chosing which heuristic, the user wants to use
*
*   @param  initialConfig  - initial state
*   @param  finalConfig - final state
*   @return the option that the user chose
*/
int menuHeuristics(vector<int> initialConfig, vector<int> finalConfig) {
	int option;

	cout << "+---------------------------------+" << endl;
	cout << "|                                 |" << endl;
	cout << "|            Heuristics           |" << endl;
	cout << "|                                 |" << endl;
	cout << "+---------------------------------+" << endl;
	cout << "|     1. Nº pieces out of place   |" << endl;
	cout << "+---------------------------------+" << endl;
	cout << "|     2. Manhattan Distance       |" << endl;
	cout << "+---------------------------------+" << endl;

	cout << "Select one of the options above [1-2]: ";
	cin >> option;

	cout << "" << endl;

	return option;
}

/**
*   @brief  Menu for chosing which search algorithms and heuristics, the user wants to use
*
*   @param  initialConfig  - initial state
*   @param  finalConfig - final state
*   @return void
*/
void menu(vector<int> initialConfig, vector<int> finalConfig) {
	int searchOption = -1;
	int heuristicOption = -1;
	
	searchOption = menuSearches(initialConfig, finalConfig);
	
	if (searchOption == 4 || searchOption == 5)
		heuristicOption = menuHeuristics(initialConfig, finalConfig);

	cout << "Searching for path to solution..." << endl;

	clock_t begin = clock();
	
	switch (searchOption) {
		case 1: 
			cout << "Using DFS Algorithm" << endl;
			DFS(initialConfig, finalConfig); 
			break;
		case 2: 
			cout << "Using BFS Algorithm" << endl;
			BFS(initialConfig, finalConfig);
			break;
		case 3: 
			cout << "Using IDFS Algorithm" << endl;
			IDFS(initialConfig, finalConfig);
			break;
		case 4: 
			if (heuristicOption == 1)
				cout << "Using Greedy Algorithm with heuristic - N� pieces out of place heuristic" << endl;
			else
				cout << "Using Greedy Algorithm with heuristic - Manhattan Distance" << endl;
			GREEDY(initialConfig, finalConfig, heuristicOption);
			break;
		case 5: 
			if (heuristicOption == 1)
				cout << "Using A* Algorithm with heuristic - N� pieces out of place" << endl;
			else
				cout << "Using A* Algorithm with heuristic - Manhattan Distance" << endl;
			AStar(initialConfig, finalConfig, heuristicOption);
			break;
		default: cout << "Please choose one of the options above!" << endl;
	}

	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

	cout << "Elapsed time to find solution: " << elapsed_secs << " seconds" << endl;

}

/**
*   Main function
*/
int main() {
	cout << "+----------------------------+" << endl;
	cout << "|                            |" << endl;
	cout << "| Welcome to 15 Puzzle Game! |" << endl;
	cout << "|                            |" << endl;
	cout << "+----------------------------+" << endl;
	cout << "" << endl;

	vector<int> initialConfig;
	vector<int> finalConfig;

	cout << "Initial configuration: ";
	initialConfig = insertConfig();
	cout << "Final configuration: ";
	finalConfig = insertConfig();

	if (!(hasParity(initialConfig) == hasParity(finalConfig))) {
		cout << "" << endl;
		cout << "This puzzle has no solution." << endl;
	}
	else {
		cout << "" << endl;
		cout << "This puzzle has solution." << endl;
		menu(initialConfig, finalConfig);
	}

	return 0;
}