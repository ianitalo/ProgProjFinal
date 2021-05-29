#include <iostream>
#include <fstream>
#include "Player.h"
#include "Robot.h"
#include "Game.h"
#include "leaderboard.h"
#include "Score.h"
#include "Maze.h"
#include "Post.h"

using namespace std;
void play(Game game)
{
	bool result = game.play();
	game.gameover(result);
}
void maze_selection()
{
	string file;
	unsigned number;
	bool error = true;
	ifstream map;
	while (error)
	{
		cout << "choose the maze number (01 to 99): ";
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
				cout << "not a valid maze number, please try again." << endl;
			}
		} while (!cin.good());
		if (number >= 0 && number < 10) //this is to make inputs like 1 and 01 to be accepted
		{
			file = "MAZE_0" + to_string(number) + ".TXT";
		}
		else
		{
			file = "MAZE_" + to_string(number) + ".TXT";
		}
		map.open(file);
		if (map.is_open())
		{
			map.close();
			error = false;
			Game game(file);
			play(game);
			return;
		}
		else
		{
			cout << "not a existing maze number, please try again." << endl;
		}
	}
}
void menu()
{
	int reload;
	unsigned short answer;
	bool error = false;
	cout << endl << endl;
	cout << "	>======>                >=>                   >=>          >=>       >=>                                " << endl;
	cout <<	"	>=>    >=>              >=>                   >=>          >> >=>   >>=>                                " << endl;
	cout <<	"	>=>    >=>      >=>     >=>         >=>     >=>>==>        >=> >=> > >=>    >=> >=>  >====>>=>   >==>   " << endl;
	cout << "	>> >==>       >=>  >=>  >=>>==>   >=>  >=>    >=>          >=>  >=>  >=>  >=>   >=>       >=>  >>   >=> " << endl;
	cout << "	>=>  >=>     >=>    >=> >=>  >=> >=>    >=>   >=>          >=>   >>  >=> >=>    >=>     >=>    >>===>>=>" << endl;
	cout << "	>=>    >=>    >=>  >=>  >=>  >=>  >=>  >=>    >=>          >=>       >=>  >=>   >=>    >=>     >>       " << endl;
	cout << "	>=>      >=>    >=>     >=>>==>     >=>        >=>         >=>       >=>   >==>>>==> >=======>  >====>  " << endl << endl << endl;
	do
	{
		cout << 
			"	                                                                                                      " << endl <<
			"	                                           0~/~~<~~~~~|/~~~~<~~0                                        " << endl <<
			"	                                           |       _____       |                                        " << endl <<
			"	                                          .'______'     '______'.                                       " << endl <<
			"	                                         |  ____    > <    ____- |                                      " << endl <<
			"	                                        '   |   l         /   |   '                                     " << endl <<
			"	                                        |   |____l       /____|   |                                     " << endl <<
			"	                                        |                         |                                     " << endl <<
			"	                                        |       vvvvvvvvvvv       |                                     " << endl <<
			"	                                 __-__  |       ^^^^^^^^^^^       |  __-__                              " << endl <<
			"	--------------------------------|  |  |-----------------------------|  |  |-----------------------------" << endl <<
			"	|                               |  |  |                             |  |  |                            |" << endl <<
			"	|                                -- --            choose :           -- --                             |" << endl <<
			"	|                                               1 for Rules                                            |" << endl <<
			"	|                                                2 to Play                                             |" << endl <<
			"	|                                            3 for leaderboards                                        |" << endl <<
			"	|                                                0 to Exit                                             |" << endl <<
			"	|                                                                                                      |" << endl <<
			"	--------------------------------------------------------------------------------------------------------" << endl;
		cin >> answer;
		if (cin.eof())
		{
			return;
		}
		if (!cin.good())
		{
			cout << "this is not a valid choice, please try again." << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			error = true;
		}
		else if (answer == 1)
		{
			string rule;
			ifstream rule_screen("RULES.TXT");

			while (getline(rule_screen, rule))
			{
				cout << rule << endl;  //display leaderboard
			}


			cout << endl << "type 0 to return to menu" << endl;

			cin >> reload;

			while (!cin.good() || reload != 0)
			{
				cout << "this is not a valid choice, please try again." << endl;
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cin >> reload;
			}
			
			error = false;
			menu();
		}
		else if (answer == 2)
		{
			error = false;
			maze_selection();

			cout << endl << "type 0 to return to menu" << endl;

			cin >> reload;

			while (!cin.good() || reload != 0)
			{
				cout << "this is not a valid choice, please try again." << endl;
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cin >> reload;
			}

			menu();
			return;
		}
		else if (answer == 3)
		{
			error = false;
			Leaderboard MenuLeaderboard;
			MenuLeaderboard.OpenInMenu();

			cout << endl << "type 0 to return to menu" << endl;
			cin >> reload;

			while (!cin.good() || reload != 0)
			{
				cout << "this is not a valid choice, please try again." << endl;
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cin >> reload;
			}

			error = false;
			menu();
		}
		else if (answer == 0)
		{
			error = false;
			return;
		}
		else
		{
			cout << "this is not a valid choice, please try again." << endl;
			error = true;
		}
	} while (error);
}
int main()
{
	menu();
}