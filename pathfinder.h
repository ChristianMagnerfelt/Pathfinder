#pragma once

#include<deque>
#include<vector>
#include<string>

class Pathfinder
{
	typedef std::pair<unsigned int, unsigned int> Position;

	public:
		Pathfinder() : 
			playerTile('@'), 
			playerOnGoalTile('+'), 
			wallTile('#'), 
			boxTile('$'),
			playerOnGoal(false){};
		void addLineAsRow(std::string && line);
		void findStartPosition(std::string & line);
		void printStartPosition() const;
		void printMaze() const;
	private:
		std::vector<std::string> maze;

		Position playerStart;
		bool playerOnGoal;

		const char playerTile;
		const char playerOnGoalTile;
		const char wallTile;
		const char boxTile;
};

