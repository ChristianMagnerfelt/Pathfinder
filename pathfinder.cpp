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

void Pathfinder::findSolution()
{
	breadFirstSearch();
}

void Pathfinder::breadFirstSearch()
{
	queue.push_front(playerStart);
	while(!queue.empty())
	{	
		if(foundSolution)
			return;
		Position pos = queue.front();
		queue.pop_front();

		std::cout << "Current Position " << pos.first << "," << pos.second << std::endl;

		checkUp(pos);
		checkRight(pos);
		checkDown(pos);
		checkLeft(pos);
	}
	std::cout << "Found no solution" << std::endl;
}

void Pathfinder::checkUp(Position & pos)
{
	if(pos.second == 0)
		return;
	if(maze[pos.second - 1][pos.first] == goalTile)
	{
		foundSolution = true;
		std::cout << "Found solution" << std::endl;
		return;
	}
	if(maze[pos.second - 1][pos.first] != emptySpace)
		return;
	std::cout << "U" << std::endl;

	// Mark position as visited
	maze[pos.second - 1][pos.first] = upC;

	// Add new position to queue
	queue.emplace_back(Position(pos.first, pos.second - 1));
}
void Pathfinder::checkRight(Position & pos)
{
	if(pos.first == (maze[pos.second].length() - 1))
		return;
	if(maze[pos.second][pos.first + 1] == goalTile)
	{
		foundSolution = true;
		std::cout << "Found solution" << std::endl;
		return;
	}
	if(maze[pos.second][pos.first + 1] != emptySpace)
		return;
	std::cout << "R" << std::endl;

	// Mark position as visited
	maze[pos.second][pos.first + 1] = rightC;

	// Add new position to queue
	queue.emplace_back(Position(pos.first + 1, pos.second));
}
void Pathfinder::checkDown(Position & pos)
{
	if(pos.second == (maze.size() - 1))
		return;
	if(maze[pos.second + 1][pos.first] == goalTile)
	{
		foundSolution = true;
		std::cout << "Found solution" << std::endl;
		return;
	}
	if(maze[pos.second + 1][pos.first] != emptySpace)
		return;
	std::cout << "D" << std::endl;

	// Mark position as visited
	maze[pos.second + 1][pos.first] = downC;

	// Add new position to queue
	queue.emplace_back(Position(pos.first, pos.second + 1));
}
void Pathfinder::checkLeft(Position & pos)
{
	if(pos.first == 0)
		return;
	if(maze[pos.second][pos.first - 1] == goalTile)
	{
		foundSolution = true;
		std::cout << "Found solution" << std::endl;
		return;
	}
	if(maze[pos.second][pos.first - 1] != emptySpace)
		return;
	std::cout << "L" << std::endl;

	// Mark position as visited
	maze[pos.second][pos.first - 1] = leftC;

	// Add new position to queue
	queue.emplace_back(Position(pos.first - 1, pos.second));
}

