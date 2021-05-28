#include "Robot.h"
int Robot::robotCounter = 0;
Robot::Robot(int row, int col)
{
	this->row = row;
	this->col = col;
	id = robotCounter++;
	alive = true;
	symbol = 'R';

}
Robot::Robot()
{
	row = -1;
	col = -1;
}
void Robot::move(int playerrow, int playercol)
{
	if (alive)
	{
		if (playerrow < row && playercol < col) // robots follow the player blindly
		{
			row -= 1;
			col -= 1;
		}
		else if (playerrow < row && playercol == col)
		{
			row -= 1;
		}
		else if (playerrow < row && playercol > col)
		{
			row -= 1;
			col += 1;
		}
		else if (playerrow == row && playercol < col)
		{
			col -= 1;
		}
		else if (playerrow == row && playercol > col)
		{
			col += 1;
		}
		else if (playerrow > row && playercol < col)
		{
			row += 1;
			col -= 1;
		}
		else if (playerrow > row && playercol == col)
		{
			row += 1;
		}
		else if (playerrow > row && playercol > col)
		{
			row += 1;
			col += 1;
		}
	}
}

