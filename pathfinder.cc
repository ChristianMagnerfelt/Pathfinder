#include "pathfinder.h"

#include <algorithm>
#include <iostream>
#include <sstream>

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
			foundSolution = true;
			printStartPosition();
		}
	}
}
void Pathfinder::printStartPosition() const
{
	if(playerOnGoal)
	{
		//std::cout << "Player on Goal" << std::endl;
	}
	//std::cout << "Start :" << playerStart.first << "," << playerStart.second << std::endl;
}
void Pathfinder::printMaze() const
{
	std::for_each(maze.begin(),maze.end(),[](const std::string & row)
	{
		//std::cout << row << std::endl;	
	});
}

void Pathfinder::findSolution()
{
	if(playerOnGoal || foundSolution)
	{
		//std::cout << "Already found solution" << std::endl;
	}
	else
	{
		breadFirstSearch();
	}
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

		//std::cout << "Current Position " << pos.first << "," << pos.second << std::endl;

		checkUp(pos);
		checkRight(pos);
		checkDown(pos);
		checkLeft(pos);
	}
	//std::cout << "Found no solution" << std::endl;
}

void Pathfinder::checkUp(Position & pos)
{
	if(pos.second == 0)
		return;
	if(maze[pos.second - 1][pos.first] == goalTile)
	{
		maze[pos.second - 1][pos.first] = upC;
		playerGoal = Position(pos.first, pos.second - 1);
		foundSolution = true;
		//std::cout << "Found solution" << std::endl;
		return;
	}
	if(maze[pos.second - 1][pos.first] != emptySpace)
		return;
	//std::cout << "U" << std::endl;

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
		maze[pos.second][pos.first + 1] = rightC;
		playerGoal = Position(pos.first + 1, pos.second);
		foundSolution = true;		
		//std::cout << "Found solution" << std::endl;
		return;
	}
	if(maze[pos.second][pos.first + 1] != emptySpace)
		return;
	//std::cout << "R" << std::endl;

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
		maze[pos.second + 1][pos.first] = downC;
		playerGoal = Position(pos.first, pos.second + 1);
		foundSolution = true;
		//std::cout << "Found solution" << std::endl;
		return;
	}
	if(maze[pos.second + 1][pos.first] != emptySpace)
		return;
	//std::cout << "D" << std::endl;

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
		maze[pos.second][pos.first - 1] = leftC;
		playerGoal = Position(pos.first - 1, pos.second);
		foundSolution = true;
		//std::cout << "Found solution" << std::endl;
		return;
	}
	if(maze[pos.second][pos.first - 1] != emptySpace)
		return;
	//std::cout << "L" << std::endl;

	// Mark position as visited
	maze[pos.second][pos.first - 1] = leftC;

	// Add new position to queue
	queue.emplace_back(Position(pos.first - 1, pos.second));
}
std::string Pathfinder::constructSolution()
{
	//std::cout << "Contructing solution" << std::endl;
	if(playerOnGoal || !foundSolution)
	{
		return std::string("");
	}
	else
	{
		Position currentPos(playerGoal);
		//std::cout << maze[currentPos.second][currentPos.first] << std::endl;
		//std::cout << "Current position" << currentPos.first << "," << currentPos.second << std::endl;
		std::stringstream out(std::stringstream::out);
		while(currentPos != playerStart)
		{
			out << maze[currentPos.second][currentPos.first];
			//std::cout << maze[currentPos.second][currentPos.first] << std::endl;
			getNextPosition(currentPos);
		}
		std::string solution(out.str());
		std::reverse(solution.begin(), solution.end());
		return solution;
	}
}
void Pathfinder::getNextPosition(Position & pos)
{
	if(maze[pos.second][pos.first] == upC)
	{
		pos.second += 1;
	}
	else if(maze[pos.second][pos.first] == rightC)
	{
		pos.first -= 1;
	}
	else if(maze[pos.second][pos.first] == downC)
	{
		pos.second -= 1;
	}
	else if(maze[pos.second][pos.first] == leftC)
	{
		pos.first += 1;
	}
	else
	{
		//Do nothing
	}
}
bool Pathfinder::hasSolution()
{
	return foundSolution;
}
