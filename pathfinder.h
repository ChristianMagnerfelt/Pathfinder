#include<deque>
#include<vector>
#include<string>

class Pathfinder
{
	public:
		Pathfinder();
		void addLineAsRow(std::string && line);
		void printMaze();
	private:
		std::vector<std::string> maze;
};

