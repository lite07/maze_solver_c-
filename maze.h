/*
Subprogram that contains functions for a maze solving algortihm.
Created with the goal of fulfilling a task for a university course.
Zaky Yudha Rabbani
20217322
github:lite07
*/

#ifndef _GRIDH_
#define _GRIDH_

#include <vector>
#include <string>
//=====================================================================================================//
//grid class to symbolize each square of the maze
class grid
{
	public:
	bool visited;
	bool passable;
	
	grid()
	{
		visited = false;
		passable = true;
	}
};

//=====================================================================================================//
//object class to symbolize the moving object
class object
{
	public:
	int xPosition;
	int yPosition;	
	
	object(int initialY, int initialX)
	{
		xPosition=initialX;
		yPosition=initialY;
	}
	
	void moveLeft()
	{
		xPosition =  xPosition - 1;
	}

	void moveRight()
	{
		xPosition =  xPosition + 1;
	}

	void moveUp()
	{
		yPosition = yPosition - 1;
	}

	void moveDown()
	{
		yPosition = yPosition + 1;
	}
};

//=====================================================================================================//
//a function to setup the maze.
void setupMaze(std::vector<std::vector<grid> >& maze)
{
	for(int i = 0; i<9; i++)
	{
		std::vector<grid> inputForVector;
		for(int j = 0; j<6; j++)
		{
			grid newGrid;
			inputForVector.push_back(newGrid);
		}
		maze.push_back(inputForVector);
	}
	maze[0][4].passable = false;
	maze[1][1].passable = false;
	maze[1][2].passable = false;
	maze[2][4].passable = false;
	maze[3][0].passable = false;
	maze[3][2].passable = false;
	maze[3][4].passable = false;
	maze[4][2].passable = false;
	maze[5][2].passable = false;
	maze[5][3].passable = false;
	maze[5][4].passable = false;
	maze[7][0].passable = false;
	maze[7][2].passable = false;
	maze[7][3].passable = false;
	maze[7][5].passable = false;
}

//=====================================================================================================//
//a function to draw the maze and the object current position.
void drawMaze(object player, std::vector<std::vector<grid> > maze)
{
	for(int i = 0; i < maze.size(); i++)
	{
		for(int j = 0; j < maze[0].size(); j++)
		{
			if(!maze[i][j].passable||maze[i][j].visited)
			{
				if(!maze[i][j].passable)
				{
					std::cout << "# ";
				}
				if(maze[i][j].visited)
				{
					std::cout << "X ";
				}
			}
			else
			{
				if(player.xPosition==j&&player.yPosition==i)
				{
					std::cout << "P ";
				}
				else
				{
					std::cout << "O ";
				}
			}
		}
		std::cout << "\n";
	}
	std::cout << "\n\n\n";
}
//=====================================================================================================//
//function to get a list of all the possible move from the current square
std::vector<char> getPossibleMove(object player, std::vector<std::vector<grid> > maze)
{
	std::vector<char> possibleMove;
	int x = player.xPosition;
	int y = player.yPosition;
	
	if(x!=0)
	{
		if(maze[y][x-1].passable&&!maze[y][x-1].visited)
		{
			possibleMove.push_back('L');
		}
	}
	
	if(y!=0)
	{
		if(maze[y-1][x].passable&&!maze[y-1][x].visited)
		{
			possibleMove.push_back('U');
		}
	}
	
	if(x!=maze[0].size()-1)
	{
		if(maze[y][x+1].passable&&!maze[y][x+1].visited)
		{
			possibleMove.push_back('R');
		}
	}
	
	if(y!=maze.size()-1)
	{
		if(maze[y+1][x].passable&&!maze[y+1][x].visited)
		{
			possibleMove.push_back('D');
		}
	}
	return possibleMove;
}
//=====================================================================================================//
//a recursive function to navigate the object in the maze. it follows a depth-first search
void traverseMaze(object player, std::vector<std::vector<grid> > maze, std::string trace, int moveCount
, char whereToMove, int& minMoves, std::string& shortestPath, int& possiblePath)
{
	switch(whereToMove)
	{
		case 'L':
			maze[player.yPosition][player.xPosition].visited = true;
			player.moveLeft();
			trace+="L ";
			break;
			
		case 'U':
			maze[player.yPosition][player.xPosition].visited = true;
			player.moveUp();
			trace+="U ";
			break;
			
		case 'R':
			maze[player.yPosition][player.xPosition].visited = true;
			player.moveRight();
			trace+="R ";
			break;
			
		case 'D':
			maze[player.yPosition][player.xPosition].visited = true;
			player.moveDown();
			trace+="D ";
			break;
	}
	moveCount++;
	
	std::vector<char> possibleMove = getPossibleMove(player,maze);
	if(player.xPosition==0&&player.yPosition==8)
	{
		possiblePath++;
		if(minMoves==0)
		{
			minMoves = moveCount ;
			shortestPath = trace;
		}
		else
		{
			if(moveCount == minMoves)
			{
				shortestPath = shortestPath + "\n" + trace;
			}
			
			if(moveCount < minMoves)
			{
				minMoves = moveCount;
				shortestPath = trace;
			}
		}
		std::cout << "Path Found! ";
		std::cout << trace << "(Number of steps: " << moveCount << ")\n";
		//drawMaze(player, maze); //Decomment this line to see the visualization of the path.
		return;
	}
	
	if(possibleMove.size()==0)
	{
		return;
	}
	
	for(char nextMove : possibleMove) //only works with c++11
	{
		traverseMaze(player, maze, trace, moveCount, nextMove, minMoves, shortestPath, possiblePath);
	}
	
}
//=====================================================================================================//
//The start of the recursive function.
void startTraversing(object player, std::vector<std::vector<grid> > maze)
{
	std::string shortestPath;
	int minMoves = 0;
	int moveCount = 0;
	int possiblePath = 0;
	std::string trace = "";
	std::vector<char> possibleMove = getPossibleMove(player,maze);
	
	for(char nextMove : possibleMove) //only works with c++11
	{
		switch(nextMove)
		{
			case 'L':
				trace="L ";
				traverseMaze(player, maze, trace, moveCount, nextMove, minMoves, shortestPath, possiblePath);
				break;
				
			case 'U':
				trace="U ";
				traverseMaze(player, maze, trace, moveCount, nextMove, minMoves, shortestPath, possiblePath);
				break;
				
			case 'R':
				trace="R ";
				traverseMaze(player, maze, trace, moveCount, nextMove, minMoves, shortestPath, possiblePath);
				break;
				
			case 'D':
				trace="D ";
				traverseMaze(player, maze, trace, moveCount, nextMove, minMoves, shortestPath, possiblePath);
				break;
		}
	}
	std::cout << "There are " << possiblePath << " number of possible path.\n";
	std::cout << "The shortest path(s):\n" << shortestPath << "\nwith " << minMoves << " number of moves.\n";
}


#endif
