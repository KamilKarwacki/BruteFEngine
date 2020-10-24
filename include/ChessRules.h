#pragma once
#include "BoardPosition.h"
#include <vector>


namespace ChessRule
{
    std::vector<Move> AllPossibleMoves(const BoardPosition& position);
    std::vector<Move> PawnMoves(const BoardPosition& position, int pos);
    std::vector<Move> KnightMoves(const BoardPosition& position, int pos);
    std::vector<Move> BishopMoves(const BoardPosition& position, int pos);
    std::vector<Move> RookMoves(const BoardPosition& position, int pos);
    std::vector<Move> QueenMoves(const BoardPosition& position, int pos);
    std::vector<Move> KingMoves(const BoardPosition& position, int pos);
    std::vector<Move> CastleMoves(const BoardPosition& position, int pos);

    [[nodiscard]] inline bool isFree(const BoardPosition& position, int x, int y);
    [[nodiscard]] inline bool isOfColor(const BoardPosition& position, int x, int y, Color color);
}

