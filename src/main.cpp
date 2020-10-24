#include "BoardPosition.h"
#include "ChessRules.h"
#include "MoveList.h"

#include <algorithm>

int main()
{
    BoardPosition pos;

    std::vector<Move> MovesForWhite = ChessRule::AllPossibleMoves(pos);
    std::cout << "possible moves at the beginning:" << MovesForWhite.size() << std::endl;

	std::for_each(MovesForWhite.begin(), MovesForWhite.end(), [](auto i){ std::cout << i.from << " " << i.to << std::endl;});


	return 0;
}
