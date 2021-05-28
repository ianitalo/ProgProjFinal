#pragma once
#include <vector>
#include <string>
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
	Game(const std::string& filename);
	bool play();
	bool isvalid(Movement& move); //this will also check if player suicide
	void showGameDisplay();
	void gameover(bool play);
	void collide(Robot& oldrobot, Robot& testrobot);
	void kill_backstabed_robots();
	Movement getinput();
private:
	std::string filename;
	timing score;
	Maze maze;
	Player player;
	std::vector<Robot>robots;
	bool over;
};
