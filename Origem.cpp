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
	unsigned short answer;
	bool error = false;
	cout << ">======>                >=>                   >=>          >=>       >=>                                " << endl;
	cout << ">=>    >=>              >=>                   >=>          >> >=>   >>=>                                " << endl;
	cout << ">=>    >=>      >=>     >=>         >=>     >=>>==>        >=> >=> > >=>    >=> >=>  >====>>=>   >==>   " << endl;
	cout << ">> >==>       >=>  >=>  >=>>==>   >=>  >=>    >=>          >=>  >=>  >=>  >=>   >=>       >=>  >>   >=> " << endl;
	cout << ">=>  >=>     >=>    >=> >=>  >=> >=>    >=>   >=>          >=>   >>  >=> >=>    >=>     >=>    >>===>>=>" << endl;
	cout << ">=>    >=>    >=>  >=>  >=>  >=>  >=>  >=>    >=>          >=>       >=>  >=>   >=>    >=>     >>       " << endl;
	cout << ">=>      >=>    >=>     >=>>==>     >=>        >=>         >=>       >=>   >==>>>==> >=======>  >====>  " << endl;
	do
	{
		cout <<
			"                                                                                                        " << endl <<
			"                                           0~/~~<~~~~~|/~~~~<~~0                                        " << endl <<
			"                                           |       _____       |                                        " << endl <<
			"                                          .'______'     '______'.                                       " << endl <<
			"                                         |  ____    > <    ____- |                                      " << endl <<
			"                                        '   |   l         /   |   '                                     " << endl <<
			"                                        |   |____l       /____|   |                                     " << endl <<
			"                                        |                         |                                     " << endl <<
			"                                        |       vvvvvvvvvvv       |                                     " << endl <<
			"                                 __-__  |       ^^^^^^^^^^^       |  __-__                              " << endl <<
			"--------------------------------|  |  |-----------------------------|  |  |-----------------------------" << endl <<
			"|                               |  |  |                             |  |  |                            |" << endl <<
			"|                                -- --            choose :           -- --                             |" << endl <<
			"|                                               1 for Rules                                            |" << endl <<
			"|                                                2 to Play                                             |" << endl <<
			"|                                            3 for leaderboards                                        |" << endl <<
			"|                                                0 to Exit                                             |" << endl <<
			"|                                                                                                      |" << endl <<
			"--------------------------------------------------------------------------------------------------------" << endl;
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
			cout << "--------------------------------------------------------------------------------------------------------" << endl <<
				"|                                                RULES                                                 |" << endl <<
				"--------------------------------------------------------------------------------------------------------" << endl <<
				"|You will be placed in a maze made up of high-voltage fences.                                          |" << endl <<
				"|There are robots that will try to destroy you.                                                        |" << endl <<
				"|The only way you have to destroy them (and win the game)                                              |" << endl <<
				"|is to make them crash with each other or make them crash                                              |" << endl <<
				"|with the eletric fences (sorry, you can not punch them).                                              |" << endl <<
				"|If you are the one hiting the robots or colliding with the fences you die.                            |" << endl <<
				"|Every time you move the robots will also make a move going to your direction by the shortest path     |" << endl <<
				"|(thats how you trick them). The robots have no vision sensors but                                     |" << endl <<
				"|they have an accurate odour sensor that allows them to follow the player!                             |" << endl <<
				"|                                                                                                      |" << endl <<
				"|                                                                                                      |" << endl <<
				"|you can only move to one of the 8 neighbour cells of your current cell.                               |" << endl <<
				"|these are the letters you can use to move :                                                           |" << endl <<
				"|                                     Q           W            E                                       |" << endl <<
				"|                                                                                                      |" << endl <<
				"|                                     A          you           D                                       |" << endl <<
				"|                                                                                                      |" << endl <<
				"|                                     Z           X            C                                       |" << endl <<
				"|                                                                                                      |" << endl <<
				"|you can also stay in the same place by choosing 'S'.                                                  |" << endl <<
				"--------------------------------------------------------------------------------------------------------" << endl;
			int reload;
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
			return;
		}
		else if (answer == 3)
		{
			error = false;
			Leaderboard MenuLeaderboard;
			MenuLeaderboard.OpenInMenu();
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
	//int num;
	//Time score;
	//score.TimeStart();
	//cout << "input";
	//cin >> num;
	//score.TimeEnd();
	//score.Score();
}