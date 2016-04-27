 // cube_h2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "cube.h"
#include <windows.h>
#include <queue>
#include <unordered_set>
#define OBSTALE -1
using namespace std;
//#define PRINT_INPUT
//#define DEBUG


int goal[3][3][3];
char cgoal[3][3][3];
int targetPos[27];
bool operator<(const Node &lhs, const Node &rhs)
{
	return lhs.f > rhs.f;
}
void play(char source[][3][3], char target[][3][3])
{
	Node initNode;
	Node chosenNode;
	char action[6] = { 'U','D','L','R','F','B' };
	priority_queue<Node, vector<Node>> fringe;
	unordered_set<string> closed;
	unordered_set<string> inFringe;
	string stmp;
	//targetPos 0-24存储25块的位置，25，26存储障碍物位置
	for (int i=0;i<3;i++)
	{
		int obstale = 25;
		for (int j=0;j<3;j++)
		{
			for (int k=0;k<3;k++)
			{
				if (-1+'A' == target[i][j][k] && obstale < 27)
				{
					targetPos[obstale] = 9 * i + 3 * j + k;
					obstale++;
				}
				targetPos[target[i][j][k]-'A'] = 9 * i + 3 * j + k;
			}
		}
	}
	//计算初始节点h
	initNode.h = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				if (source[i][j][k]!=-1&& source[i][j][k] != 0)
				{
					initNode.h += abs(targetPos[source[i][j][k]] / 9 - i) + abs(targetPos[source[i][j][k]] % 9 / 3 - j) + abs(targetPos[source[i][j][k]] % 9 % 3 - k);
				}
				if (source[i][j][k] == 0)
				{
					initNode.blank = 9 * i + 3 * j + k;
				}
				
			}
		}
	}
	initNode.g = 0;
	initNode.f = initNode.h;
	memcpy(initNode.state, source, sizeof(initNode.state));
	for (int i = 0; i < 27; i++)
	{
		initNode.state[i] += 'A';
	}
	initNode.state[27] = 0;
#ifdef DEBUG
	cout << "目标位置"<<endl;
	for (int i = 0; i < 27; i++)
	{
		cout <<i<<' ';
		cout << targetPos[i] / 9 << ' ' << targetPos[i] % 9 / 3 << ' ' << targetPos[i] % 9 % 3 << endl;
	}
	cout << "h=" << initNode.h << endl;
#endif
	fringe.push(initNode);
	stmp = initNode.state;
	inFringe.insert(stmp);
	
	int count=0;
	while (true)
	{
		
		count++;
		if (fringe.empty())
		{
			cout << "Can't find solution!" << endl;
			break;
		}

		chosenNode=fringe.top();
		//cout << chosenNode.f << endl;
		fringe.pop();
		stmp = chosenNode.state;
		inFringe.erase(stmp);
		/*if (inFringe.find(initNode.state) == inFringe.end())
		{
			cout << "!!!" << endl;
		}*/
		if (goaltest(chosenNode))
		{
			cout << chosenNode.path << endl;
			cout<<"步数: "<<chosenNode.g<<endl;
			cout << "Node explored: " << count << endl;
			break;
		}
		
		closed.insert(stmp);
		

#ifdef DEBUG
		if (chosenNode.move('R'))
		{
			cout << endl << "h=" << chosenNode.h << endl;
			cout << endl << "移动结果" << endl;
			for (int i = 0; i < 27; i++)
			{
				if (i != 0 && i % 3 == 0)
				{
					cout << endl;
				}
				if (i != 0 && i % 9 == 0)
				{
					cout << endl;
				}
				cout << chosenNode.state[i] - 'A' << '\t';

			}
			cout << endl;

		}
		else
		{
			cout << "can not move" << endl;
		}

#endif//_DEBUG
		
		//expand the chosenNode
		Node tmp = chosenNode;
		for (int i=0;i<6;i++)
		{
			//移动成功需要恢复临时节点到移动前状态
			if (tmp.move(action[i]))
			{

				stmp = tmp.state;
				if ((inFringe.find(stmp) == inFringe.end()) && (closed.find(stmp) == closed.end()))
				{
					fringe.push(tmp);
					inFringe.insert(stmp);
					//cout << 'h' << tmp.h << endl;
				}
				tmp = chosenNode;
			}
		}
		

	}

}


int main()
{
	ifstream source("source.txt");
	ifstream target("target.txt");
	//int PosBuffer[25][3];
	if (!source)
	{
		cerr << "Can't open source.txt\n" << endl;
		exit(-1);
	}
	
	char cinput[3][3][3];
	int input[3][3][3];
	//int CurrentState[3][3][3];
	int BlankPosx = 0, BlankPosy = 0, BlankPosz = 0;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			source >> input[i][j][0] >> input[i][j][1] >> input[i][j][2];

			cinput[i][j][0] = input[i][j][0];
			cinput[i][j][1] = input[i][j][1];
			cinput[i][j][2] = input[i][j][2];

		}
	}

	source.close();

	if (!target)
	{
		cerr << "Can't open target.txt\n" << endl;
		exit(-1);
	}

	

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			target >> goal[i][j][0] >> goal[i][j][1] >> goal[i][j][2];
			cgoal[i][j][0] = goal[i][j][0]+'A';
			cgoal[i][j][1] = goal[i][j][1]+'A';
			cgoal[i][j][2] = goal[i][j][2]+'A';
		}
	}
	target.close();
#ifdef PRINT_INPUT
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				cout << input[i][j][k] << ' ';
			}
			cout << endl;
		}
		cout << endl;
	}
#endif // PRINT_INPUT
	LARGE_INTEGER  frec, start, end;
	QueryPerformanceFrequency(&frec);
	QueryPerformanceCounter(&start);

	play(cinput, cgoal);

	QueryPerformanceCounter(&end);
	 		auto during = end.QuadPart - start.QuadPart;
			cout << (double)during*1000 / frec.QuadPart<<"ms"<<endl;
	system("pause");
	return 0;
}



