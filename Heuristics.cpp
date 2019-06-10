#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
*   @brief  get index of a value in a vector
*
*   @param  value  - value to find
*   @param  currentConfig - current configuration state
*   @return index
*/
int indexOfValue(int value, vector<int> currentConfig) {
	vector<int>::iterator itr = find(currentConfig.begin(), currentConfig.end(), value);
	return distance(currentConfig.begin(), itr);
}

/**
*   @brief  Checks and counts the number of out of place pieces
*
*   @param  currentConfig  - current configuration state
*   @param  finalConfig - final configuration state
*   @return number of out of place pieces
*/
int heuristic_OutOfPlacePieces(vector<int> currentConfig, vector<int> finalConfig) {
	int count = 0;
	for (int i = 0; i < 16; i++)
		if (currentConfig[i] != finalConfig[i])
			count++;
	return count;
}

/**
*   @brief  Auxiliar function of 
*
*   @param  i  - index of a piece in the current state
*   @param  j - index of a piece in the final state
*   @return number of moves to put current piece in the same place as in the finalConfig state
*/
int manhattanDistance_aux(int i, int j) {
	int x1 = i / 4;
	int y1 = i % 4;

	int x2 = j / 4;
	int y2 = j % 4;

	return abs(x1 - x2) + abs(y1 - y2);
}

/**
*   @brief  Sums the distances of each piece according to its position in the finalConfig state
*
*   @param  currentConfig  - current configuration state
*   @param  finalConfig - final configuration state
*   @return sum of all distances
*/
int heuristic_Manhattan_Distance(vector<int> currentConfig, vector<int> finalConfig) {
	int count = 0;
	for (int i = 0; i < 16; i++) {
		count += manhattanDistance_aux(indexOfValue(i, currentConfig), indexOfValue(i, finalConfig));
	}
	return count;
}