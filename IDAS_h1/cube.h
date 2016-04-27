#ifndef CUBE_H
#define CUBE_H
#include <string>

using namespace std;

struct Node
{
	string path;
	char state[28];
	int blank;
	int h;
	int f;
	int g;
	
	bool move(char action);
}; 

bool goaltest(Node chosenNode);

#endif 
