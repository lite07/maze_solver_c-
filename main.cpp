/*
This is a program that can solve a given maze.
Created with the goal of fulfilling a task for a university course.
Zaky Yudha Rabbani
20217322
github:lite07
*/

#include <iostream>
#include "maze.h"
#include <vector>
#include <string>

int main()
{
	object Player(0,5);
	std::vector<std::vector<grid> > maze;
	setupMaze(maze);
	startTraversing(Player,maze); 
	std::cout << "This is a debug message!\n";
	return 0;
}
