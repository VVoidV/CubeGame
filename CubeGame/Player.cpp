#include "stdafx.h"
#include "Player.h"
#include <vector>
#include"cube.h"

bool operator<(const miniNode &lhs, const miniNode &rhs)
{
	return lhs.f > rhs.f;
}

unsigned int Player::chooseNode()
{
	unsigned int n;
	n=open.top().index;
	open.pop();
	return n;
}

void Player::expandNode(unsigned int index)
{
	Node tmp;
	miniNode miniTmp;
	char action[6] = { 'U','D','L','R','F','B' };

	int state[3][3][3];
	int posBuf[25][3];
	
	for (int i = 0; i < 6; i++)
	{
		cube.setState(vertex[index].state);
		if (cube.move(action[i]))
		{
			tmp.action = action[i];	
			cube.getState(state, posBuf);
			tmp.cost = vertex[index].depth + h2(posBuf);
			tmp.depth = vertex[index].depth + 1;
			tmp.parent = index;
			memcpy(tmp.state, state, sizeof(state));
			memcpy(tmp.posBuf, posBuf, sizeof(posBuf));
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					for (int k = 0; k < 3; k++)
					{
						tmp.tag.insert(tmp.tag.size(), 1, state[i][j][k]);
					}
				}
			}
			if (isClosed(tmp.tag)&&notOpen(tmp.tag))
			{
				miniTmp.f = tmp.cost;
				miniTmp.index = vertex.size() ;
				vertex.push_back(tmp);
				open.push(miniTmp);
				isOpen.insert(tmp.tag);
				
			}

		}
	}
	closed.insert(vertex[index].tag);
	isOpen.erase(vertex[index].tag);
}

bool Player::isClosed(string tag)
{
	if (closed.end() == closed.find(tag))
	{
		return true;
	}
	return false;
}

bool Player::notOpen(string tag)
{
	static int count=0;
	if (isOpen.end()==isOpen.find(tag))
	{
		return true;
	}
	count++;
	return false;
}

bool Player::goalTest(int state[][3][3])
{
	
	return !memcmp(state, goal,sizeof(goal));
}

unsigned int Player::h1(int state[][3][3])
{//不在位个数
	int count = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				if (state[i][j][k] != goal[i][j][k])
				{
					++count;
				}
			}
		}
	}
	return count;
}

unsigned int Player::h2(int pos[][3])
{//曼哈顿距离
	int dis=0;

	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < 3;j++)
		{
			dis += abs(pos[i][j] - goalPos[i][j]);
		}
	}
	cout << "h "<<dis << endl;
	return dis;
}

void Player::PrintSolution(unsigned int index)
{
	string s;
	if (index == 0)
	{
		cout << "initial state is the goal!" << endl;
	}
	
	while (index != 0)
	{
		s.insert(s.size(),1,vertex[index].action);
		index = vertex[index].parent;
	}
	for (int i = s.size(); i >= 0;i--)
	{
		cout << s[i]<<' ';
	}
}

Player::Player()
{
}


Player::~Player()
{
}

bool Player::playAS(const char h)
{
	unsigned int index;
	int count = 0;
	while (1)
	{
		if (0 == open.size())
		{
			cout << "no" << endl;
			return false;
		}

		index = chooseNode();
		if (goalTest(vertex[index].state))
		{
			PrintSolution(index);
			return true;
		}
		//cout << count++ << endl;
		cout << vertex[index].cost << endl;
		expandNode(index);
	}
	
}

bool Player::playIDAS(const char)
{
	return false;
}

void Player::setGoal(char state[][3][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				if (state[i][j][k]>=0)
				{
					goalPos[state[i][j][k]][0] = i;
					goalPos[state[i][j][k]][1] = j;
					goalPos[state[i][j][k]][2] = k;
				}
			}
		}
	}
	memcpy(goal, state, sizeof(goal));
}

void Player::init(char state[][3][3])
{
	miniNode n;
	Node t;
	int m = 0;
	t.action = 'N';
	t.depth = 0;
	t.parent = 0;
	memcpy(t.state, state, sizeof(t.state));
	
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				t.tag.insert(t.tag.size(),1,'b'+state[i][j][k]);				
			}
		}
	}
	
	int posIndex[25][3];
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				if (state[i][j][k] >= 0)
				{
					posIndex[state[i][j][k]][0] = i;
					posIndex[state[i][j][k]][1] = j;
					posIndex[state[i][j][k]][2] = k;
				}
			}
		}
	}

	n.f = h2(posIndex);
	t.cost = n.f;
	n.index = 0;
	open.push(n);
	isOpen.insert(t.tag);
	vertex.push_back(t);
	//cube.setState(state);
}
