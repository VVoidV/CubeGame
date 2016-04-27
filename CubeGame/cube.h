#ifndef CUBE_H
#define CUBE_H
class Cube
{
private:
	char state[3][3][3];
	char pos_x, pos_y, pos_z; 
	char posIndex[25][3];
	void setIndex();
public:
	Cube(char input[][3][3]);
	Cube();
	void setState(const char input[][3][3]);
	void getState(char dest[][3][3], char PosBuffer[][3]);
	bool move(const char action);
	void show();
	void getPos(char dest[][3]);
};
#endif
