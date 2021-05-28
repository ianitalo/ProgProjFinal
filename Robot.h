#pragma once
class Robot {
public:
	Robot();
	Robot(int row, int col);
	int getID() const { return id; };
	int getRow() const { return row; };
	int getCol() const { return col; };
	int isalive() const { return alive; };
	char getsymbol() const { return symbol; };
	void setAsDead() { alive = false; symbol = 'r'; };
	void move(int playerrow, int playercol);

	//other methods
private:
	static int robotCounter; //used to attribute automatically the id to the robots (starts by 1)
	int id;
	int row, col;
	bool alive;
	char symbol;
	// other attributes (?)
};

