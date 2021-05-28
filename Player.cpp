#include "Player.h"
Player::Player(int row, int col, char symbol)
{
	this->row = row;
	this->col = col;
	this->symbol = symbol;
	alive = true;
}
Player::Player()
{
	row = -1;
	col = -1;
	symbol = 'H';
	alive = true;
}
void Player::move(Movement& delta)
{
	row += delta.dRow;
	col += delta.dCol;
}
