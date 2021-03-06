#pragma once
class Post {
public:

	Post(int row, int col, char type) { this->row = row; this->col = col; this->type = type; };

	int getRow() const { return row; };

	int getCol() const { return col; };

	char getSymbol() const { return type; }; 

	bool isElectrified() const { return type == '*'; };

private:
	int row, col;
	char type; // '*' - electrified; '+'- non-electrified // 'O' - gate
};



