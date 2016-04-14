#ifndef CUBE_H
#define CUBE_H
class Cube
{
private:
	int state[3][3][3];
	int pos_x, pos_y, pos_z; 
	int posIndex[25][3];
	void setIndex();
public:
	Cube(int input[][3][3]);
	Cube();
	void setState(const int input[][3][3]);
	void getState(int dest[][3][3], int PosBuffer[][3]);
	bool move(const char action);
	void show();
	void getPos(int dest[][3]);
};
#endif
