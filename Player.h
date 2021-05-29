#pragma once
#ifndef Movement_struct
#define Movement_struct
struct Movement
{
	int dRow, dCol; // displacement, taking into account the chosen movement
};
#endif

class Player {
public:

	Player();

	Player(int row, int col, char symbol);

	int getRow() const { return row; };

	int getCol() const { return col; };

	char getSymbol() const { return symbol; };

	bool isAlive() const { return alive; };

	void setAsDead() { alive = false; symbol = 'h'; };

	void move(Movement& delta);

private:
	int row, col;
	bool alive;
	char symbol;
};

