#pragma once
#include <vector>
#include <string>
#include <iostream>
using namespace std;

/**
*  @brief Class that defines a node to be used in search algorithms
*/
class Node {
	private:
		vector<int> state;
		Node* parent;
		vector<Node*> children;
		string lastMove;
		int depth;
		int pathCost;
		bool visited;

		int findBlankSpaceIndex(vector<int> state);
		bool isValidMove(vector<int> invalidMoves, int index);

	public:
		Node(vector<int> state, Node* parent, string lastMove, int depth, int pathCost);
		
		bool isSameState(vector<int> otherState);

		void generateMoves();
		void moveUP(int blankSpaceIndex);
		void moveRIGHT(int blankSpaceIndex);
		void moveDOWN(int blankSpaceIndex);
		void moveLEFT(int blankSpaceIndex);

		//----------Getters-----------
		Node* getNode();
		vector<int> getState();
		Node* getParent();
		vector<Node*> getChildren();
		string getLastMove();
		int getDepth();
		int getPathCost() const;
		int getVisited() const;
		//----------------------------

		//----------Setters-----------
		void setVisited(bool value);
		void setPathCost(int cost);
		//----------------------------

		void pathToSolution();
		bool isThereCycle();
};