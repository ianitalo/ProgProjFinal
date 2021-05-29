#pragma once
#include <vector>
#include <string>
#include <string>
#include <fstream>
#include <iostream>
#include "Maze.h"
#include "Player.h"
#include "Robot.h"
#include "Score.h"
#include "leaderboard.h"
#ifndef Movement_struct
#define Movement_struct
struct Movement
{
	int dRow, dCol; // displacement, taking into account the chosen movement
};
#endif
class Game {
public:
	Game(const std::string& filename);// gets info about maze's starting state.

	bool play(); // main method.

	bool isvalid(Movement& move); //this will also check if player suicide.

	void showGameDisplay(); // shows maze state in screen.

	void gameover(bool play); //method that handles everything post-game.

	void collide(Robot& oldrobot, Robot& testrobot); // checks for robot collision.

	void kill_backstabed_robots(); // makes sure both robots are killed if one collides from behind.

	Movement getinput(); // handles player movement.
private:
	std::string filename;
	timing score;
	Maze maze;
	Player player;
	std::vector<Robot>robots;
	bool over;
};
