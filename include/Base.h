#pragma once
#include <string>

enum class Piece{
    NONE, PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING
};

enum class Color{
    NONE, WHITE, BLACK
};

struct Move{
    Move(int f, int t) : from(f), to(t){};
    int from; // 11 is square 1,1 needs to be decompressed
    int to;
};

struct SpecialMove : public Move{ // they use from, to info to calculate the new board position
    SpecialMove(int f, int t) : Move(f, t){};
    std::string name;
};

struct Castle : public SpecialMove{
    Castle(int f, int t): SpecialMove(f, t) {name = "Castle";};
};

struct EnPassant : public SpecialMove{
    EnPassant(int f, int t) : SpecialMove(f, t) {name = "EnPassant";};
};

struct EnPassantCreating : public SpecialMove{
    EnPassantCreating(int f, int t) : SpecialMove(f, t) {name = "EnPassantCreating";};
};

struct Promotion : public SpecialMove{
    Promotion(int f, int t) : SpecialMove(f, t) {name = "Promotion";};
    Promotion& Into(Piece p){piece = p; return *this;}; // fluid API
    Piece piece;
};
