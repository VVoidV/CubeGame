// CubeGame.cpp : 定义控制台应用程序的入口点。
//

//#define PRINT_INPUT

#include "stdafx.h"
#include "cube.h"
#include <fstream>
#include <vector>
#include "Player.h"
#include<time.h>




using namespace std;

int main()
{
	time_t begin, end;
// 	LARGE_INTEGER  frec,start,end;
// 	QueryPerformanceFrequency(&frec);
// 	QueryPerformanceCounter(&start);
	begin=clock();
	ifstream source("source.txt");
	ifstream target("target.txt");
	//int PosBuffer[25][3];
	if (!source) 
	{
		cerr << "Can't open source.txt\n" << endl;
		exit(-1);
	}
	char cgoal[3][3][3];
	char cinput[3][3][3];
	int input[3][3][3];
	//int CurrentState[3][3][3];
	int BlankPosx=0, BlankPosy=0,BlankPosz=0;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			/*这里有一个读取文件的问题，不知道为什么
			memset(buffer, 0, 16);
			source.getline(buffer, 10);
			while(0 == strlen(buffer)&&!source.eof())
			{
				source.getline(buffer, 10);
			}
			cout <<"***"<< buffer << endl;
			sscanf_s(buffer, "%d%d%d", &input[i][j][0], &input[i][j][1], &input[i][j][2]);*/
			source >> input[i][j][0] >> input[i][j][1] >> input[i][j][2];

			cinput[i][j][0] = input[i][j][0];
			cinput[i][j][1] = input[i][j][1];
			cinput[i][j][2] = input[i][j][2];

		}
	}

	if (!target)
	{
		cerr << "Can't open target.txt\n" << endl;
		exit(-1);
	}

	int goal[3][3][3];

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			target >> goal[i][j][0] >> goal[i][j][1] >> goal[i][j][2];
			cgoal[i][j][0] = goal[i][j][0];
			cgoal[i][j][1] = goal[i][j][1];
			cgoal[i][j][2] = goal[i][j][2];

		}
}
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


	/*Cube cube(input);
	cube.getState(CurrentState, PosBuffer);

	cube.show();
	int pos[25][3];
	cube.getPos(pos);
	for (int i = 0; i < 25;i++)
	{
		for (int j = 0; j < 3;j++)
		{
			cout << pos[i][j];
		}
		cout << endl;
	}

	cube.move('L');
	cube.move('B');
	cube.show();
	cube.getPos(pos);
	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << PosBuffer[i][j];
		}
		cout << endl;
	}*/

	//Player play;
	//play.setGoal(cgoal);
	//play.init(cinput);
	//play.playAS('1');
// 	QueryPerformanceCounter(&end);
// 		double during = end - start;
// 		cout<<(end-start)/frec

	Cube cube;
	cube.setState(input);
	char c;
	ifstream test("test.txt");
	string path;
	if (!test)
	{
		cout << "can not open test.txt" << endl;
	}
	test >> path;
	cout << path;
	for (int i=0;i<path.size();i++)
	{
		c = path[i];
		cube.move(c);
	}
	cube.show();
	
	end = clock();
	cout << end - begin << endl;
	system("pause");
    return 0;
}

