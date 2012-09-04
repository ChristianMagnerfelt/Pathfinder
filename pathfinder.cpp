#include "pathfinder.h"

#include <algorithm>
#include <iostream>

Pathfinder::Pathfinder()
{
	
}
void Pathfinder::addLineAsRow(std::string && line)
{
	maze.push_back(move(line));			
}
void Pathfinder::printMaze()
{
	std::for_each(maze.begin(),maze.end(),[](std::string & row)
	{
		std::cout << row << std::endl; 		
	});
}
