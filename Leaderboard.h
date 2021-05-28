#pragma once
#include "score.h"
#include <string>
class Leaderboard
{
public:
	Leaderboard() {};
	void OpenInMenu();
	void PostGameLeaderboard(const std::string& filename, std::string leader_string, timing score);
	std::string SetUp(timing score);
private:

};