#pragma once
#include <vector>
#include "Post.h"
class Maze {
public:

	Maze();

	Maze(int nRows, int nCols);

	void addPost(const Post& post); // add post to post vector

	int getnumRows() const { return numRows; };

	int getnumCols() const { return numCols; };

	int postssize() const { return posts.size(); }

	Post getpost(int indice) { return posts[indice]; }

private:

	int numRows, numCols;
	std::vector<Post> posts;
};
