#include "stdafx.h"
#include "cube.h"

extern char cgoal[3][3][3];
extern int targetPos[27];
bool goaltest(Node chosenNode)
{
	return 0 == memcmp(chosenNode.state, cgoal, sizeof(chosenNode.state));
}




bool Node::move(char action)
{

	bool isLeagal = false;
	int testblockPos;
	switch (action)
	{
	case 'U':
		if (blank % 9 / 3 > 0 && -1 + 'A' != state[blank - 3])//blank的正上坐标为blank-3
		{
			isLeagal = true;
			testblockPos = targetPos[state[blank - 3] - 'A'];//受影响的块在Goal中坐标
			state[blank] = state[blank - 3];
			state[blank - 3] = 'A';
			blank = blank - 3;
			//blank 为受影响块原来的坐标
			if (testblockPos % 9 / 3 > blank % 9 / 3)//空格向上移动时相当于受影响块向下移动，只有当目标状态该块的y坐标大于当前状态该块的坐标才会减小h，否则h增加
			{
				h--;
			}
			else
			{
				h++;
			}
		}
		else
		{
			//cerr << "now UP is illegal move" << endl;
		}
		break;

	case 'D':
		if (blank % 9 / 3 < 2 && -1 + 'A' != state[blank + 3])
		{

			isLeagal = true;
			testblockPos = targetPos[state[blank + 3] - 'A'];//受影响的块在Goal中坐标
			state[blank] = state[blank + 3];
			state[blank + 3] = 'A';
			blank = blank + 3;

			if (testblockPos % 9 / 3 < blank % 9 / 3)
			{
				h--;
			}
			else
			{
				h++;
			}

		}
		else
		{
			//cerr << "now Down is illegal move" << endl;
		}
		break;

	case 'L':
		if (blank % 9 % 3 > 0 && -1 + 'A' != state[blank - 1])
			//pos_z > 0 && -1 != state[pos_x][pos_y][pos_z - 1])
		{

			isLeagal = true;
			testblockPos = targetPos[state[blank - 1] - 'A'];//受影响的块在Goal中坐标
			state[blank] = state[blank - 1];
			state[blank - 1] = 'A';
			blank = blank - 1;

			if (testblockPos % 9 % 3 > blank % 9 % 3)
			{
				h--;
			}
			else
			{
				h++;
			}

		}
		else
		{
			//cerr << "now Left is illegal move" << endl;
		}
		break;

	case 'R':
		if (blank % 9 % 3 < 2 && -1 + 'A' != state[blank + 1])
			//pos_z < 2 && -1 != state[pos_x][pos_y][pos_z + 1])
		{

			isLeagal = true;

			//计算h
			testblockPos = targetPos[state[blank + 1] - 'A'];//受影响的块在Goal中坐标



			state[blank] = state[blank + 1];
			state[blank + 1] = 'A';
			blank = blank + 1;
			if (testblockPos % 9 % 3 < blank % 9 % 3)
			{
				h--;
			}
			else
			{
				h++;
			}



		}
		else
		{
			//cerr << "now Right is illegal move" << endl;
		}
		break;

	case 'F':
		if (blank / 9 > 0 && -1 + 'A' != state[blank - 9])
			//pos_x > 0 && -1 != state[pos_x - 1][pos_y][pos_z])
		{
			isLeagal = true;
			testblockPos = targetPos[state[blank - 9] - 'A'];//受影响的块在Goal中坐标

			state[blank] = state[blank - 9];
			state[blank - 9] = 'A';
			blank = blank - 9;

			if (testblockPos / 9 > blank / 9)
			{
				h--;
			}
			else
			{
				h++;
			}

		}
		else
		{
			//cerr << "now Forward is illegal move" << endl;
		}
		break;

	case 'B':
		if (blank / 9 < 2 && -1 + 'A' != state[blank + 9])
			//pos_x < 2 && -1 != state[pos_x + 1][pos_y][pos_z])
		{
			isLeagal = true;
			testblockPos = targetPos[state[blank + 9] - 'A'];//受影响的块在Goal中坐标




			state[blank] = state[blank + 9];
			state[blank + 9] = 'A';
			blank = blank + 9;

			if (testblockPos / 9 < blank / 9)
			{
				h--;
			}
			else
			{
				h++;
			}

		}
		else
		{
			//cerr << "now Back is illegal move" << endl;
		}
		break;
	default:
		//cerr << "invalid action!" << endl;
		;
	}
	if (isLeagal)
	{
		path.push_back(action);
		f = h + g;
		g++;
	}

	return isLeagal;
}
