#include "Maze.h"
Maze::Maze(int nRows, int nCols)
{
	numCols = nCols;
	numRows = nRows;
}
Maze::Maze()
{
	numCols = 0;
	numRows = 0;
}
void Maze::addPost(const Post& post)
{
	posts.push_back(post);
}
