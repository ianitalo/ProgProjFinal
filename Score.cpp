#include "Score.h"

using namespace std;

void timing::TimeStart()
{
	start = std::chrono::high_resolution_clock::now();
}

void timing::TimeEnd()
{
	end = std::chrono::high_resolution_clock::now();
}

double timing::Score()
{
	score = end - start;
	return score.count();
}