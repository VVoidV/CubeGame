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

	if (path.size() != 0)
	{
		switch (action)
		{
		case 'U':
			if (path[path.size() - 1] == 'D')
			{
				return false;
			}
			break;
		case'D':
			if (path[path.size() - 1] == 'U')
			{
				return false;
			}
			break;
		case'L':
			if (path[path.size() - 1] == 'R')
			{
				return false;
			}
			break;
		case 'R':
			if (path[path.size() - 1] == 'L')
			{
				return false;
			}
			break;
		case 'B':
			if (path[path.size() - 1] == 'F')
			{
				return false;
			}
			break;
		case 'F':
			if (path[path.size() - 1] == 'B')
			{
				return false;
			}
			break;
		default:
			return false;
		}
	}
	switch (action)
	{
	case 'U':
		if (blank % 9 / 3 > 0 && -1 + 'A' != state[blank - 3])//blank����������Ϊblank-3
		{
			isLeagal = true;
			testblockPos = targetPos[state[blank - 3] - 'A'];//��Ӱ��Ŀ���Goal������
			state[blank] = state[blank - 3];
			state[blank - 3] = 'A';
			blank = blank - 3;
			//blank Ϊ��Ӱ���ԭ��������
			if (testblockPos % 9 / 3 > blank % 9 / 3)//�ո������ƶ�ʱ�൱����Ӱ��������ƶ���ֻ�е�Ŀ��״̬�ÿ��y������ڵ�ǰ״̬�ÿ������Ż��Сh������h����
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
			testblockPos = targetPos[state[blank + 3] - 'A'];//��Ӱ��Ŀ���Goal������
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
			testblockPos = targetPos[state[blank - 1] - 'A'];//��Ӱ��Ŀ���Goal������
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

			//����h
			testblockPos = targetPos[state[blank + 1] - 'A'];//��Ӱ��Ŀ���Goal������



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
			testblockPos = targetPos[state[blank - 9] - 'A'];//��Ӱ��Ŀ���Goal������

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
			testblockPos = targetPos[state[blank + 9] - 'A'];//��Ӱ��Ŀ���Goal������




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
