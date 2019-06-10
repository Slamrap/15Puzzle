#pragma once
#ifndef SearchAlgorithms
#define SearchAlgorithms

#include <vector>
using namespace std;

void DFS(vector<int> initialConfig, vector<int> finalConfig);
void BFS(vector<int> initialConfig, vector<int> finalConfig);
void IDFS(vector<int> initialConfig, vector<int> finalConfig);
bool DLS(vector<int> initialConfig, vector<int> finalConfig, int maxDepth);
void GREEDY(vector<int> initialConfig, vector<int> finalConfig, int heuristic);
void AStar(vector<int> initialConfig, vector<int> finalConfig, int heuristic);

#endif