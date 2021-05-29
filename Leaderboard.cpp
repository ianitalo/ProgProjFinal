#include "leaderboard.h"
using namespace std;

void Leaderboard::OpenInMenu()
{
	string screen_string;
	int number;

	cout << "choose which map's leaderboard (01 to 99): ";
	do
	{
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cin >> number;

		if (cin.eof())
		{
			return;
		}

		if (!cin.good())
		{
			cout << "not a valid leaderboard number, please try again." << endl;
		}
	} while (!cin.good());


	if (number >= 0 && number < 10)
	{
		ifstream screen;
		screen.open("MAZE_0" + to_string(number) + "_WINNERS.TXT");

		if (screen.is_open())
		{
			while (getline(screen, screen_string))
			{
				cout << screen_string << endl;
			}
		}
		else
		{
			cout << endl << "Empty list." << endl << endl;
			return;
		}
	}
	else
	{
		ifstream screen;
		screen.open("MAZE_" + to_string(number) + "_WINNERS.TXT");

		if (screen.is_open())
		{
			while (getline(screen, screen_string))
			{
				cout << screen_string << endl; //display leaderboard
			}
		}
		else
		{
			cout << endl << "Empty list." << endl << endl;
			return;
		}
	}
}

string Leaderboard::SetUp(timing score)
{
	string name;

	cin.ignore(INT_MAX, '\n');
	getline(cin, name);

	while (name.size() > 15 || name.size() < 1)
	{
		if (cin.eof())
		{
			return"";
		}
		cout << "Invalid name size! please try again." << endl;
		getline(cin, name);
	}

	int num_spaces = 15 - name.size(); // 
	string spaces(num_spaces, ' ');    //  fill name with " " untill desired length ( so it fits the leaderboard )
	name = name + spaces;              //

	double rounded_time = round(score.Score() * 1000.0) / 1000.0; // rounding time to 3 digits
	string rounded_string = to_string(rounded_time);

	for (int i = rounded_string.size() - 1; i > 0; i--) // even after rounding, a few of the 0s to the right are considered in the .size() function, this for loop is a work-around.
	{
		if (rounded_string[i] == '0')
		{
			rounded_string.pop_back();
		}
		else
		{
			break;
		}
	}

	int time_size = rounded_string.size();
	num_spaces = 0;                                 // 
	num_spaces = 6 - time_size;                     // num of " " to get desired length 
	string time_spaces(num_spaces, ' ');			//
	string leader_string = name + "-" + time_spaces + rounded_string;

	return leader_string;
}

void Leaderboard::PostGameLeaderboard(const std::string& filename, string leader_string, timing score)
{
	if (cin.eof())
	{
		return;
	}
	string LeaderBoardName;
	vector<string> leaderboard_string;
	string score_line, time, trash1, trash2, screen_string;
	vector<double> ScoresVec;
	double rounded_time = round(score.Score() * 1000.0) / 1000.0;

	LeaderBoardName = "MAZE_" + filename.substr(5, 2) + "_WINNERS.TXT";

	ofstream check(LeaderBoardName, ios::app); // check if the file exists without altering it, if it doesnt, create one
	check.close();

	ifstream collect(LeaderBoardName);
	if (!collect)
	{
		cout << "cannot open leaderboard."; //fail-safe
		return;
	}

	if (collect.is_open())
	{
		getline(collect, trash1);// ignore header
		getline(collect, trash2);//

		while (getline(collect, score_line))
		{
			leaderboard_string.push_back(score_line); // fill vector with relevant info from the leaderboard (previous names + scores)
		}
		for (size_t i = 0; i < leaderboard_string.size(); i++)// allows us to get the actual score value from the leaderboard's strings
		{
			for (int j = 21; j >= 16; j--)
			{
				if (leaderboard_string[i][j] == ' ' || leaderboard_string[i][j] == '-')
				{
					break;
				}
				else
				{
					time = leaderboard_string[i][j] + time;
				}
			}
			ScoresVec.push_back(stod(time));// each score is added to a vector
			time = "";
		}
	}

	if (leaderboard_string.size() == 0)// in case the file exists but is empty
	{
		leaderboard_string.push_back(leader_string);
	}

	bool last_score = false;

	for (size_t i = 0; i < ScoresVec.size(); i++)// check if current time is better than each of the times on the leader board, if it is add it to the 
	{										// vector on that position. This automatically sorts the board.
		if (rounded_time <= ScoresVec[i])
		{
			leaderboard_string.insert(leaderboard_string.begin() + i, leader_string);
			break;
		}
		if (i == ScoresVec.size() - 1)
		{
			last_score = true;
		}
	}

	if (last_score)
	{
		leaderboard_string.push_back(leader_string); // in case the current time is the worst one it will be added to the bottom of the vector
	}

	ofstream updated("MAZE_" + filename.substr(5, 2) + "_WINNERS.TXT");
	updated <<
		"Player         -  Time" << endl <<
		"----------------------" << endl;
	for (size_t i = 0; i < leaderboard_string.size(); i++)
	{
		updated << leaderboard_string[i] << endl; //write updated file with info from vector
	}
	updated.close();

	ifstream screen("MAZE_" + filename.substr(5, 2) + "_WINNERS.TXT");
	while (getline(screen, screen_string))
	{
		cout << screen_string << endl;  //display leaderboard
	}
}



