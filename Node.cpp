#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include "Node.h"
using namespace std;

/**
*   @brief  Constructor of Node class
*
*   @param  state  - current state
*   @param  parent - parent of the current state
*	@param lastMove - last move executed that originated this current state
*	@param depth - depth of current state
*	@param pathCost - path cost to current state
*   @return new node describing current state
*/
Node::Node(vector<int> state, Node* parent, string lastMove, int depth, int pathCost) {
	this->state = state;
	this->parent = parent;
	this->lastMove = lastMove;
	this->depth = depth;
	this->pathCost = pathCost;
	this->visited = false;
}

/**
*   @brief  Compares two states, in order to verify if they are equal
*
*   @param  otherState  - state to compare
*   @return True or False, whether current state and otherState are equal.
*/
bool Node::isSameState(vector<int> otherState) {
	return getState() == otherState;
}

/**
*   @brief  Finds index of blank space in a state 
*
*   @param  state  - state in which we want to find blank space index
*   @return index of the blank space
*/
int Node::findBlankSpaceIndex(vector<int> state) {
	vector<int>::iterator itr = find(state.begin(), state.end(), 0);
	return distance(state.begin(), itr);
}

/**
*   @brief  Finds index of blank space in a state
*
*   @param  invalidMoves  - vector containing the invalid positions
*   @param  index  - blank space index in the current config
*   @return True or False, whether index is in the invalidMoves vector or not
*/
bool Node::isValidMove(vector<int> invalidMoves, int index) {
	if (find(invalidMoves.begin(), invalidMoves.end(), index) != invalidMoves.end())
		return false;
	else
		return true;
}

/**
*   @brief  Generates all possible moves 
*
*   @return void
*/
void Node::generateMoves(){
	int blankSpaceIndex = findBlankSpaceIndex(getState());
	moveUP(blankSpaceIndex);
	moveRIGHT(blankSpaceIndex);
	moveDOWN(blankSpaceIndex);
	moveLEFT(blankSpaceIndex);
}

/**
*   @brief  Execute the up movement if blankSpaceIndex is in a valid position
*
*   @param  blankSpaceIndex  - blank space index in the current config
*   @return void
*/
void Node::moveUP(int blankSpaceIndex){
	vector<int> invalid_UP_Move { 0,  1,  2,  3 };
	if (isValidMove(invalid_UP_Move, blankSpaceIndex)) {
		vector<int> newState = getState();
		swap(newState[blankSpaceIndex], newState[blankSpaceIndex - 4]);
		Node* child = new Node(newState, getNode(), "UP", getDepth() + 1, getPathCost());
		if (!isThereCycle())
			children.push_back(child);
	}
}

/**
*   @brief  Execute the right movement if blankSpaceIndex is in a valid position
*
*   @param  blankSpaceIndex  - blank space index in the current config
*   @return void
*/
void Node::moveRIGHT(int blankSpaceIndex) {
	vector<int> invalid_RIGHT_Move { 3,  7, 11, 15 };
	if (isValidMove(invalid_RIGHT_Move, blankSpaceIndex)) {
		vector<int> newState = this->state;
		swap(newState[blankSpaceIndex], newState[blankSpaceIndex + 1]);
		Node* child = new Node(newState, getNode(), "RIGHT", getDepth() + 1, getPathCost());
		if (!isThereCycle())
			children.push_back(child);
	}
}

/**
*   @brief  Execute the down movement if blankSpaceIndex is in a valid position
*
*   @param  blankSpaceIndex  - blank space index in the current config
*   @return void
*/
void Node::moveDOWN(int blankSpaceIndex) {
	vector<int> invalid_DOWN_Move { 12, 13, 14, 15 };
	if (isValidMove(invalid_DOWN_Move, blankSpaceIndex)) {
		vector<int> newState = this->state;
		swap(newState[blankSpaceIndex], newState[blankSpaceIndex + 4]);
		Node* child = new Node(newState, getNode(), "DOWN", getDepth() + 1, getPathCost());
		if(!isThereCycle())
			children.push_back(child);
	}
}

/**
*   @brief  Execute the left movement if blankSpaceIndex is in a valid position
*
*   @param  blankSpaceIndex  - blank space index in the current config
*   @return void
*/
void Node::moveLEFT(int blankSpaceIndex) {
	vector<int> invalid_LEFT_Move { 0,  4,  8, 12 };
	if (isValidMove(invalid_LEFT_Move, blankSpaceIndex)) {
		vector<int> newState = this->state;
		swap(newState[blankSpaceIndex], newState[blankSpaceIndex - 1]);
		Node* child = new Node(newState, getNode(), "LEFT", getDepth() + 1, getPathCost());
		if (!isThereCycle())
			children.push_back(child);
	}
}

/**
*   @brief  Get current node
*
*   @return  current node
*/
Node* Node::getNode() {
	return this;
}

/**
*   @brief  Get current state
*
*   @return  vector of current state
*/
vector<int> Node::getState() {
	return this->state;
}

/**
*   @brief  Get current node's parent
*
*   @return  Node of current node's parent
*/
Node* Node::getParent() {
	return this->parent;
}

/**
*   @brief  Get current node's children
*
*   @return  vector of current node's children
*/
vector<Node*> Node::getChildren() {
	return this->children;
}

/**
*   @brief  Get current last move
*
*   @return  string of last move
*/
string Node::getLastMove() {
	return this->lastMove;
}

/**
*   @brief  Get current node's depth
*
*   @return  current node´s depth
*/
int Node::getDepth() {
	return this->depth;
}

/**
*   @brief  Get current node's visited value
*
*   @return  current node's visited value
*/
int Node::getVisited() const {
	return this->visited;
}

/**
*   @brief  Set current node's visited value
*
*   @return  void
*/
void Node::setVisited(bool value) {
	this->visited = value;
}

/**
*   @brief  Get current node's path cost
*
*   @return  current node's path cost
*/
int Node::getPathCost() const {
	return this->pathCost;
}

/**
*   @brief  Set current node's path cost
*
*   @return  void
*/
void Node::setPathCost(int cost) {
	this->pathCost = cost;
}

/**
*   @brief  Print the all movements to get from the initial state to the final state.
*	To get all the movements, it goes from current node, loops to each parent until it reachs the initial node.
*
*   @return  void
*/
void Node::pathToSolution() {
	Node* n = getNode();
	vector<string> moves;

	while (n->getParent() != NULL) {
		if (n->getLastMove().compare("") != 0)
			moves.insert(moves.begin(), n->getLastMove());
		n = n->getParent();
	}

	cout << "List of moves: [";
	for (int i = 0; i < moves.size(); i++) {
		if(i == moves.size()-1)
			cout << moves[i];
		else
			cout << moves[i] + ", ";
	}
	cout << "]" << endl;
}

/**
*   @brief  Checks if there are any cycles, in between current state and the initial state
*
*   @return  True or False, if the current state is equal to any of the previous states
*/
bool Node::isThereCycle() {
	Node* n = getNode();

	while (n->getParent() != NULL) {
		if (n->getParent()->getState() == getState())
			return true;
		n = n->getParent();
	}
	return false;
}




