#pragma once 
#include <vector>
#include "Base.h"

class MoveList {         
public:
	void AddMove(int from, int to)
	{
		moves.emplace_back(from, to);
	}

	void RemoveMove()
    {
	    moves.pop_back();
    }

private:            
	std::vector<Move> moves;
};
