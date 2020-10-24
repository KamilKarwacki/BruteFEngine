#pragma once
#include <iostream>
#include <array>
#include "Base.h"

class BoardPosition {
public:
    BoardPosition();
    void Move(const Move& move);

    friend std::ostream& operator<<(std::ostream& os, const BoardPosition& BP);

    std::array<std::pair<Piece, Color>, 8*8> piecePositions;
    Color toMove = Color::WHITE; // saves who should move from this position
    Color inCheck = Color::NONE; // saves who is in check if there is anyone
    int enPassantSquare = -1;    // saves the square that can be captured by en passant
};
