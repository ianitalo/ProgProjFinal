#pragma once
#include <chrono>
#include <iostream>
class timing
{
public:

	timing() { };

	void TimeStart(); // starting time in seconds

	void TimeEnd(); // end time in seconds

	double Score(); // score = end time - starting time


private:
	std::chrono::high_resolution_clock::time_point start;
	std::chrono::high_resolution_clock::time_point end;
	std::chrono::duration<double> score;
};
