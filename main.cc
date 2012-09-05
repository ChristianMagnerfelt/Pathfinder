#include <iostream>
#include <cstdlib>
#include <string>
#include "csocket.h"
#include "pathfinder.h"

bool hasSolution = false;

int main(int pArgC, char* pArgs[])
{
    if(pArgC<4)
    {
        std::cerr << "usage: " << pArgs[0] << " host port boardnum" << std::endl;
        return -1;
    }

    soko::CSocket lSocket(pArgs[1],pArgs[2]);

    lSocket.WriteLine(pArgs[3]);
    
    std::string lNumRows;

    // Read number of rows
    lSocket.ReadLine(lNumRows);
    int numRows=atoi(lNumRows.c_str());

	Pathfinder pathfinder;
    
    //read each row
    for(int i=0;i<numRows;i++)
    {
		std::string lLine;
        lSocket.ReadLine(lLine);
        //here, we would store the row somewhere, to build our board
        //in this demo, we just print it
		pathfinder.addLineAsRow(std::move(lLine));
        //std::cout << lLine << " : " << lLine.length() << std::endl;
    }
    pathfinder.printMaze();
    //now, we should find a path from the player to any goal

	pathfinder.findSolution();

	pathfinder.printMaze();
    //we've found our solution    
	std::string lMySol("U R R U U L D L L U L L D R R R R L D D R U R U D L L U R");
	//these formats are also valid:
	//std::string lMySol("URRUULDLLULLDRRRRLDDRURUDLLUR");
    //std::string lMySol("0 3 3 0 0 2 1 2 2 0 2 2 1 3 3 3 3 2 1 1 3 0 3 0 1 2 2 0 3");

	
	if(hasSolution)
	{
		//send the solution to the server
		lSocket.WriteLine(lMySol);
		
		//read answer from the server
		std::string answer;
		lSocket.ReadLine(answer);
    
		std::cout << answer << std::endl;
	}
    return 0;
}

