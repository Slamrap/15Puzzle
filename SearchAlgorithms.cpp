#include <vector>
#include <algorithm>
#include "SearchAlgorithms.h"
#include "Node.h"
#include "Heuristics.h"
#include <stack>
#include <queue>
#include <iostream>

using namespace std;

/**
*  @brief Custom comparator for priority queue
*/
struct Compare{
	bool operator()(const Node* current, const Node* other) {
		return current->getPathCost() > other->getPathCost();
	}
};

/**
*   @brief  Depth-First Search Algorithm
*
*   @param  initialConfig  - initial state
*   @param  finalConfig - final state
*   @return void
*/
void DFS(vector<int> initialConfig, vector<int> finalConfig){
	stack<Node*> stack;

	bool SolutionFound = false;
	int maxDepth = 13;

	Node* initialNode = new Node(initialConfig, NULL, "", 0, 0);
	
	stack.push(initialNode);

	int n_Generated_Nodes = 0;
	while (!stack.empty() && !SolutionFound) {
		Node* aux = stack.top();
		stack.pop();

		aux->setVisited(true);

		aux->generateMoves();
		n_Generated_Nodes += aux->getChildren().size();

		if (maxDepth > aux->getDepth()) {
			for (Node* n : aux->getChildren()) {
				if (n->isSameState(finalConfig)) {
					cout << "Solution found!" << endl;
					cout << "" << endl;
					SolutionFound = true;
					n->pathToSolution();
					cout << "Depth: " << n->getDepth() << endl;
					cout << "Number of generated nodes: " << n_Generated_Nodes << endl;
				}		
				if (n->getVisited() == false)
					stack.push(n);
			}
		}
	}
}

/**
*   @brief  Breadth-First Search Algorithm
*
*   @param  initialConfig  - initial state
*   @param  finalConfig - final state
*   @return void
*/
void BFS(vector<int> initialConfig, vector<int> finalConfig) {
	queue<Node*> queue;
	bool SolutionFound = false;

	Node* initialNode = new Node(initialConfig, NULL, "", 0, 0);
	queue.push(initialNode);

	int n_Generated_Nodes = 0;
	while (!queue.empty() && !SolutionFound) {
		Node* aux = queue.front();
		queue.pop();

		aux->setVisited(true);

		aux->generateMoves();
		n_Generated_Nodes += aux->getChildren().size();

		for (Node* n : aux->getChildren()) {
			if (n->isSameState(finalConfig)) {
				cout << "Solution found!" << endl;
				cout << "" << endl;
				SolutionFound = true;
				n->pathToSolution();
				cout << "Depth: " << n->getDepth() << endl;
				cout << "Number of generated nodes: " << n_Generated_Nodes << endl;
			}
			if (n->getVisited() == false)
				queue.push(n);
		}
	}
}

/**
*   @brief  Iterative Deepening Depth-First Search Algorithm
*
*   @param  initialConfig  - initial state
*   @param  finalConfig - final state
*   @return void
*/
void IDFS(vector<int> initialConfig, vector<int> finalConfig) {
	int maxDepth = 0;
	bool SolutionFound = false;

	while (!SolutionFound) {
		if(DLS(initialConfig, finalConfig, maxDepth))
			SolutionFound = true;
		maxDepth++;
	}
}

/**
*   @brief  Depth-Limited Search Algorithm, used to assist IDFS.
*
*   @param  initialConfig  - initial state
*   @param  finalConfig - final state
*	@param  maxDepth - current max depth received from IDFS;
*   @return True or False, in case the solution is found
*/
bool DLS(vector<int> initialConfig, vector<int> finalConfig, int maxDepth) {
	stack<Node*> stack;
	bool SolutionFound = false;

	Node* initialNode = new Node(initialConfig, NULL, "", 0, 0);
	stack.push(initialNode);

	int n_Generated_Nodes = 0;
	while (!stack.empty()) {
		Node* aux = stack.top();
		stack.pop();

		aux->setVisited(true);
		
		aux->generateMoves();
		n_Generated_Nodes += aux->getChildren().size();

		if (maxDepth > aux->getDepth()) {
			for (Node* n : aux->getChildren()) {
				if (n->isSameState(finalConfig)) {
					cout << "Solution found!" << endl;
					cout << "" << endl;
					SolutionFound = true;
					n->pathToSolution();
					cout << "Depth: " << n->getDepth() << endl;
					cout << "Number of generated nodes: " << n_Generated_Nodes << endl;
					return SolutionFound;
				}
				if (n->getVisited() == false)
					stack.push(n);
			}
		}
	}
	return SolutionFound;
}

/**
*   @brief  Best-First Search: Greedy Algorithm
*
*   @param  initialConfig  - initial state
*   @param  finalConfig - final state
*	@param heuristic - option chosen in the heuristics menu
*   @return void
*/
void GREEDY(vector<int> initialConfig, vector<int> finalConfig, int heuristic) {
	priority_queue<Node*, vector<Node*>, Compare> pq;
	bool SolutionFound = false;

	Node* initialNode = new Node(initialConfig, NULL, "", 0, 0);
	pq.push(initialNode);

	int n_Generated_Nodes = 0;
	while (!pq.empty() && !SolutionFound) {
		Node* aux = pq.top();
		pq.pop();

		aux->setVisited(true);

		aux->generateMoves();
		n_Generated_Nodes += aux->getChildren().size();

		for (Node* n : aux->getChildren()) {
			if (n->isSameState(finalConfig)) {
				cout << "Solution found!" << endl;
				cout << "" << endl;
				SolutionFound = true;
				n->pathToSolution();
				cout << "Depth: " << n->getDepth() << endl;
				cout << "Number of generated nodes: " << n_Generated_Nodes << endl;
			}
			if (n->getVisited() == false) {
				if (heuristic == 1) {
					int cost = heuristic_OutOfPlacePieces(n->getState(), finalConfig);
					n->setPathCost(cost);
				}
				else {
					int cost = heuristic_Manhattan_Distance(n->getState(), finalConfig);
					n->setPathCost(cost);
				}
				pq.push(n);
			}
		}
	}
}

/**
*   @brief  Best-First Search: A* Algorithm
*
*   @param  initialConfig  - initial state
*   @param  finalConfig - final state
*	@param heuristic - option chosen in the heuristics menu
*   @return void
*/
void AStar(vector<int> initialConfig, vector<int> finalConfig, int heuristic) {
	priority_queue<Node*, vector<Node*>, Compare> pq;
	bool SolutionFound = false;

	Node* initialNode = new Node(initialConfig, NULL, "", 0, 0);
	pq.push(initialNode);

	vector<Node*> visited;

	int n_Generated_Nodes = 0;
	while (!pq.empty() && !SolutionFound) {
		Node* aux = pq.top();
		pq.pop();

		visited.push_back(aux);
		aux->generateMoves();
		n_Generated_Nodes += aux->getChildren().size();

		for (Node* n : aux->getChildren()) {
			if (n->isSameState(finalConfig)) {
				cout << "Solution found!" << endl;
				cout << "" << endl;
				SolutionFound = true;
				n->pathToSolution();
				cout << "Depth: " << n->getDepth() << endl;
				cout << "Number of generated nodes: " << n_Generated_Nodes << endl;
			}
			if (heuristic == 1) {
				int cost = n->getDepth() + heuristic_OutOfPlacePieces(n->getState(), finalConfig);
				n->setPathCost(cost);
			}
			else {
				int cost = n->getDepth() + heuristic_Manhattan_Distance(n->getState(), finalConfig);
				n->setPathCost(cost);
			}
			pq.push(n);
		}
	}
}