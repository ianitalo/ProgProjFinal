#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include "score.h"
class Leaderboard
{
public:

	Leaderboard() {};

	void OpenInMenu(); // handles menu leaderboard

	void PostGameLeaderboard(const std::string& filename, std::string leader_string, timing score); //handles post-game leaderboard (also creates one if non existant)

	std::string SetUp(timing score); // returns info string in right format to be used in leaderboard

};