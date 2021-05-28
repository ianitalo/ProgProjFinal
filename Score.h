#pragma once
#include <chrono>
#include <iostream>
class timing
{
public:
	timing() { };
	void TimeStart();

	void TimeEnd();

	double Score();


private:
	std::chrono::high_resolution_clock::time_point start;
	std::chrono::high_resolution_clock::time_point end;
	std::chrono::duration<double> score;
};
