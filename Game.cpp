#include "Game.h"
#include <string>
#include <fstream>
#include <iostream>
using namespace std;
Game::Game(const std::string& filename)
{
	this->filename = filename;
	over = false;
	std::ifstream map(filename);
	int maze_height, maze_length, number_of_robots = 0;
	char x, filechar;
	std::string newline;
	map >> maze_height >> x >> maze_length;
	maze = Maze(maze_height, maze_length);
	map >> std::noskipws;
	for (int i = 0; i < maze_height; i++) //this puts the maze into the vector
	{
		getline(map, newline);
		for (int j = 0; j < maze_length; j++)
		{
			map >> filechar;
			if (filechar == 'R') // find robots
			{
				robots.push_back(Robot(i, j)); //this way of creating will put the robots in order of their id in the vector
			}
			else if (filechar == 'H') // finds the hero and saves its position
			{
				player = Player(i, j, 'H');
			}
			else if (filechar == '*' || filechar == '+' || filechar == 'O')
			{
				maze.addPost(Post(i, j, filechar));
			}
		}
	}
	map.close();
}
void Game::gameover(bool play)
{
	if (!cin.eof())
	{
		showGameDisplay();
		if (player.isAlive())
		{
			score.TimeEnd();
			cout << endl << "You have outsmarted the robots in " << score.Score() << " seconds! You are safe... for now." << endl << endl <<
				"Please write your name so we can add you to the leaderboard" << endl;
			Leaderboard LdrBrd;
			LdrBrd.PostGameLeaderboard(filename, LdrBrd.SetUp(score), score);
		}
		else
		{
			//algo como perdeu
		}
	}
}
void Game::showGameDisplay()
{
	bool gotsomething = false;
	std::string display = "";
	for (int i = 0; i < maze.getnumRows(); i++)
	{
		for (int j = 0; j < maze.getnumCols(); j++)
		{
			for (unsigned k = 0; k < robots.size(); k++)
			{
				if (robots[k].getRow() == i && robots[k].getCol() == j)
				{
					display += robots[k].getsymbol();
					gotsomething = true;
					break;
				}
			}
			if (player.getRow() == i && player.getCol() == j && !gotsomething)
			{
				display += player.getSymbol();
				gotsomething = true;
			}
			if (!gotsomething)
			{
				for (int k = 0; k < maze.postssize(); k++)
				{
					if (maze.getpost(k).getRow() == i && maze.getpost(k).getCol() == j)
					{
						display += maze.getpost(k).getSymbol();
						gotsomething = true;
						break;
					}
				}
			}
			if (!gotsomething)
			{
				display += " ";
			}
			gotsomething = false;
		}
		display += '\n';
	}
	std::cout << display << std::endl;
}
void Game::kill_backstabed_robots()
{
	for (unsigned int i = 0; i < robots.size(); i++)
	{
		if (robots[i].isalive())
		{
			for (unsigned int j = i + 1; j < robots.size(); j++)
			{
				if (robots[i].getCol() == robots[j].getCol() && robots[i].getRow() == robots[j].getRow())
				{
					robots[i].setAsDead();
					robots[j].setAsDead();
				}
			}
		}
	}
}
void Game::collide(Robot& oldrobot, Robot& testrobot)
{
	for (int i = 0; i < maze.postssize(); i++)
	{
		if ((maze.getpost(i).getRow() == testrobot.getRow()) && (maze.getpost(i).getCol() == testrobot.getCol()))
		{
			if (maze.getpost(i).getSymbol() == '+')
			{
				testrobot.setAsDead();

				return;
			}
			else
			{
				testrobot = oldrobot;//get old position
				testrobot.setAsDead();
				return;
			}
		}
	}
	if (testrobot.getRow() == player.getRow() && testrobot.getCol() == player.getCol()) //robot killing the player
	{
		player.setAsDead();
		over = true;
		testrobot = oldrobot;//get old position
	}
}
bool Game::isvalid(Movement& move)
{
	if (over == true) //in case user types cntrl z
	{
		return true;
	}
	int playermovex = player.getCol() + move.dCol;
	int playermovey = player.getRow() + move.dRow;
	for (int k = 0; k < maze.postssize(); k++) //check if player is trying to move to a cell occupied by non-electrified post
	{
		if ((maze.getpost(k).getRow() == playermovey) && (maze.getpost(k).getCol() == playermovex))
		{
			if (maze.getpost(k).getSymbol() == '+')
			{
				std::cout << "invalid move" << std::endl;
				return false;
			}

			else if (maze.getpost(k).getSymbol() == '*')
			{
				player.setAsDead(); //player suicide (but is a valid move)
				over = true;
				return true;
			}
			else
			{
				player.move(move); //player reached gate
				over = true;
			}
		}
	}
	for (unsigned k = 0; k < robots.size(); k++)
	{
		if (robots[k].getRow() == playermovey && robots[k].getCol() == playermovex) //cant move to dead/stuck robots
		{
			if (robots[k].getsymbol() == 'r')
			{
				std::cout << "invalid move" << std::endl;
				return false;
			}
			else //player tries to punch the living robot?
			{
				player.setAsDead(); //player suicide (but is a valid move)
				cout << "Player used 'Punch Robot!', it's not very effective..." << endl;
				over = true;

				return true;
			}
		}
	}
	return true;
}
Movement Game::getinput()
{
	bool error = true;
	char inp;
	Movement move;
	move.dCol = 0;
	move.dRow = 0;
	while (error)
	{
		error = false;
		cout << "your move: ";
		cin >> inp;
		if (cin.eof()) //surrender
		{
			over = true;
			player.setAsDead();
			return move;
		}
		else if (!cin.good() || (cin.peek() != EOF && cin.peek() != '\n')) //checks if player inputs only one char
		{
			cout << "invalid input, try again." << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			error = true;
		}
		else
		{
			switch (inp)
			{
			case 'q': case 'Q': move.dRow = -1; move.dCol = -1; break;
			case 'w': case 'W': move.dRow = -1; break;
			case 'e': case 'E': move.dCol = 1; move.dRow = -1; break;
			case 'a': case 'A': move.dCol = -1; break;
			case 's': case 'S': break;
			case 'd': case 'D': move.dCol = 1; break;
			case 'z': case 'Z': move.dCol = -1; move.dRow = 1; break;
			case 'x': case 'X': move.dRow = 1; break;
			case 'c': case 'C': move.dRow = 1; move.dCol = 1; break;
			default: cout << "invalid input, try again." << endl;
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				error = true;
			}
		}
	}
	return move;
}
bool Game::play()
{
	Movement playermove;
	Robot testsrobot;
	score.TimeStart();
	while (!over)
	{
		showGameDisplay();
		do
		{
			playermove = getinput();
		} while (!isvalid(playermove)); //game could be over if player suicides here
		if (!over && player.isAlive()) //the game being over while the playes still alive = gate reach, so player still needs to move
		{
			player.move(playermove);
		}
		if (!over)
		{
			for (unsigned k = 0; k < robots.size(); k++)
			{
				if (robots[k].isalive())
				{
					testsrobot = robots[k];
					testsrobot.move(player.getRow(), player.getCol());
					collide(robots[k], testsrobot);
					robots[k] = testsrobot;

				}
			}
			kill_backstabed_robots();
		}
	}
	return player.isAlive();
}


