#include <queue>
#include <unordered_set>
#include <iostream>
#include <string>
#include "cube.h"

using namespace std;

#ifndef PLAYER_H
#define PLAYER_H
class Player
{
private:
	Cube cube;
	int goal[3][3][3];
	int goalPos[25][3];

	struct Node
	{
		int state[3][3][3];
		int posBuf[25][3];
		char action;
		unsigned int parent;
		unsigned int cost;
		unsigned int depth;
		string tag;
	};
	
	
	
	deque<struct Node> vertex;
	priority_queue<class miniNode> open;
	unordered_set<string> closed;

	unsigned int chooseNode();
	void expandNode(unsigned int index);
	bool isClosed(string tag);
	bool goalTest(int state[][3][3]);
	unsigned int h1(int state[][3][3]);
	unsigned int h2(int pos[][3]);
	void PrintSolution(unsigned int index);
public:
	Player();
	~Player();
	bool playAS(const char);
	bool playIDAS(const char);
	void setGoal(int state[][3][3]);
	void init(int state[][3][3]);
	

};

class miniNode
{
public:
	unsigned int index;
	unsigned int f;
};


#endif // !PLAYER_H

