#pragma once

#include<deque>
#include<vector>
#include<string>

class Pathfinder
{
	public:
		typedef std::pair<unsigned int, unsigned int> Position;
		
		const char playerTile;
		const char playerOnGoalTile;
		const char wallTile;
		const char boxTile;
		const char goalTile;
		const char emptySpace;
		const char upC;
		const char rightC;
		const char downC;
		const char leftC;

		Pathfinder() :
			playerOnGoal(false),
			foundSolution(false),
			playerTile('@'), 
			playerOnGoalTile('+'), 
			wallTile('#'), 
			boxTile('$'),
			goalTile('.'),
			emptySpace(' '),
			upC('U'),
			rightC('R'),
			downC('D'),
			leftC('L'){};

		void addLineAsRow(std::string && line);
		void findStartPosition(std::string & line);
		void printStartPosition() const;
		void printMaze() const;
		void findSolution();
		std::string constructSolution();
		bool hasSolution();

	private:
		std::vector<std::string> maze;
		std::deque<Position> queue;
		Position playerStart;
		Position playerGoal;
		bool playerOnGoal;
		bool foundSolution;

		void breadFirstSearch();
		void checkUp(Position & pos);
		void checkRight(Position & pos);
		void checkDown(Position & pos);
		void checkLeft(Position & pos);
		void getNextPosition(Position & pos);
};

