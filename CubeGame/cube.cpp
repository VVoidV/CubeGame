#include "stdafx.h"
#include "cube.h"

using namespace std;

Cube::Cube()
{

}

void Cube::setState(int input[][3][3])
{
	memcpy(state, input, sizeof(int) * 27);
	setIndex();
	cout << "set done!" << endl;
}

void Cube::getState(int dest[][3][3],int PosBuffer[][3])
{
	memcpy(PosBuffer, posIndex, sizeof(posIndex));
	memcpy(dest, state, sizeof(int)*27);
}

void Cube::setIndex()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				posIndex[state[i][j][k]][0] = i;
				posIndex[state[i][j][k]][1] = j;
				posIndex[state[i][j][k]][2] = k;
				pos_x = posIndex[0][0];
				pos_y = posIndex[0][1];
				pos_z = posIndex[0][2];
				
			}
		}
	}
}

int Cube::move(const char action)
{
	
	switch (action)
	{
	case 'U':
		if (pos_y > 0 && -1 != state[pos_x][pos_y - 1][pos_z])
		{
			
			state[pos_x][pos_y][pos_z] = state[pos_x][pos_y - 1][pos_z];
			posIndex[state[pos_x][pos_y - 1][pos_z]][1]++;

			state[pos_x][pos_y - 1][pos_z] = 0;
			posIndex[0][1]--;
			pos_y --;
		}
		else
		{
			cerr << "now UP is illegal move" << endl;
		}
		break;

	case 'D':
		if (pos_y < 2 && -1 != state[pos_x][pos_y + 1][pos_z])
		{
			
			state[pos_x][pos_y][pos_z] = state[pos_x][pos_y + 1][pos_z];
			posIndex[state[pos_x][pos_y + 1][pos_z]][1]--;

			state[pos_x][pos_y + 1][pos_z] = 0;
			posIndex[0][1]++;
			pos_y ++;
		}
		else
		{
			cerr << "now Down is illegal move" << endl;
		}		
		break;

	case 'L':
		if (pos_z > 0 && -1 != state[pos_x][pos_y][pos_z - 1])
		{
			
			state[pos_x][pos_y][pos_z] = state[pos_x][pos_y][pos_z - 1];
			posIndex[state[pos_x][pos_y][pos_z - 1]][2]++;
			
			state[pos_x][pos_y][pos_z - 1] = 0;
			posIndex[0][2]--;
			pos_z--;
		}
		else
		{
			cerr << "now Left is illegal move" << endl;
		}
		break;

	case 'R':
		if (pos_z < 2 && -1 != state[pos_x][pos_y][pos_z + 1])
		{
			
			state[pos_x][pos_y][pos_z] = state[pos_x][pos_y][pos_z + 1];
			posIndex[state[pos_x][pos_y][pos_z + 1]][2]--;

			state[pos_x][pos_y][pos_z + 1] = 0;
			posIndex[0][2]++;
			pos_z++;
		}
		else
		{
			cerr << "now Right is illegal move" << endl;
		}
		break;

	case 'F':
		if (pos_x > 0 && -1 != state[pos_x - 1][pos_y][pos_z])
		{
			state[pos_x][pos_y][pos_z] = state[pos_x - 1][pos_y][pos_z];
			posIndex[state[pos_x - 1][pos_y][pos_z]][0]++;

			state[pos_x - 1][pos_y][pos_z] = 0;
			posIndex[0][0]--;
			pos_x--;
		}
		else
		{
			cerr << "now Forward is illegal move" << endl;
		}
		break;

	case 'B':
		if (pos_x < 2 && -1 != state[pos_x + 1][pos_y][pos_z])
		{
			state[pos_x][pos_y][pos_z] = state[pos_x + 1][pos_y][pos_z];
			posIndex[state[pos_x + 1][pos_y][pos_z]][0]--;
			

			state[pos_x + 1][pos_y][pos_z] = 0;
			posIndex[0][0]++;
			pos_x++;
		}
		else
		{
			cerr << "now Back is illegal move" << endl;
		}
		break;
	default:
		cerr << "invalid action!" << endl;

	}
	return 0;
}

void Cube::show()
{
	for (int i = 0; i < 3; i++)
	{
		cout << i <<"��" <<endl;
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				cout << state[i][j][k] << ' ';
			}
			cout << endl;
		}
		cout << endl;
	}
}

void Cube::getPos(int dest[][3])
{
	memcpy(dest, posIndex, sizeof(posIndex));
}

Cube::Cube(int input[][3][3])
{
	memcpy(state, input, sizeof(int)*27);
	setIndex();
	cout << "init!" << endl;
}
