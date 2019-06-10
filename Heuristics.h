#pragma once
#ifndef Heuristics
#define Heuristics

#include <vector>
using namespace std;

int indexOfValue(int value, vector<int> currentConfig);
int heuristic_OutOfPlacePieces(vector<int> currentConfig, vector<int> finalConfig);
int manhattanDistance_aux(int i, int j);
int heuristic_Manhattan_Distance(vector<int> currentConfig, vector<int> finalConfig);

#endif