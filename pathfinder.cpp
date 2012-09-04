#include "pathfinder.h"

#include <algorithm>
#include <iostream>

void Pathfinder::addLineAsRow(std::string && line)
{
	findStartPosition(line);
	maze.push_back(line);		
}
void Pathfinder::findStartPosition(std::string & line)
{
	for(size_t pos = 0; pos < line.length(); ++pos)
	{
		if(line[pos] == playerTile)
		{
			playerStart.first = pos;
			playerStart.second = maze.size();
			printStartPosition();
		}
		else if(line[pos] == playerOnGoalTile)
		{
			playerStart.first = pos;
			playerStart.second = maze.size();
			playerOnGoal = true;
			printStartPosition();
		}
	}
}
void Pathfinder::printStartPosition() const
{
	if(playerOnGoal)
		std::cout << "Player on Goal" << std::endl;
	std::cout << "Start :" << playerStart.first << "," << playerStart.second << std::endl;
}
void Pathfinder::printMaze() const
{
	std::for_each(maze.begin(),maze.end(),[](const std::string & row)
	{
		std::cout << row << std::endl;	
	});
}

