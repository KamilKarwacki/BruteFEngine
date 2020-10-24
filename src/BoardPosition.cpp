#include "BoardPosition.h"
#include "MoveList.h"

BoardPosition::BoardPosition(){
    piecePositions[0] = std::make_pair<Piece,Color>(Piece::ROOK,Color::WHITE);
    piecePositions[1] = std::make_pair<Piece,Color>(Piece::KNIGHT,Color::WHITE);
    piecePositions[2] = std::make_pair<Piece,Color>(Piece::BISHOP,Color::WHITE);
    piecePositions[3] = std::make_pair<Piece,Color>(Piece::KING,Color::WHITE);
    piecePositions[4] = std::make_pair<Piece,Color>(Piece::QUEEN,Color::WHITE);
    piecePositions[5] = std::make_pair<Piece,Color>(Piece::BISHOP,Color::WHITE);
    piecePositions[6] = std::make_pair<Piece,Color>(Piece::KNIGHT,Color::WHITE);
    piecePositions[7] = std::make_pair<Piece,Color>(Piece::ROOK,Color::WHITE);
    for(int i = 8; i < 16; i++)
        piecePositions[i] = std::make_pair<Piece,Color>(Piece::PAWN, Color::WHITE);
    for(int i = 16; i < 16 + 8*4; i++)
        piecePositions[i] = std::make_pair<Piece,Color>(Piece::NONE, Color::NONE);
    for(int i = 48; i < 56 + 8; i++)
        piecePositions[i] = std::make_pair<Piece,Color>(Piece::PAWN, Color::BLACK);

    piecePositions[56] = std::make_pair<Piece,Color>(Piece::ROOK,Color::BLACK);
    piecePositions[57] = std::make_pair<Piece,Color>(Piece::KNIGHT,Color::BLACK);
    piecePositions[58] = std::make_pair<Piece,Color>(Piece::BISHOP,Color::BLACK);
    piecePositions[59] = std::make_pair<Piece,Color>(Piece::KING,Color::BLACK);
    piecePositions[60] = std::make_pair<Piece,Color>(Piece::QUEEN,Color::BLACK);
    piecePositions[61] = std::make_pair<Piece,Color>(Piece::BISHOP,Color::BLACK);
    piecePositions[62] = std::make_pair<Piece,Color>(Piece::KNIGHT,Color::BLACK);
    piecePositions[63] = std::make_pair<Piece,Color>(Piece::ROOK,Color::BLACK);
}

std::ostream& operator<<(std::ostream& os, const BoardPosition& BP)
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            switch(BP.piecePositions[j + i*8].first){
                case Piece::NONE:
                    os << "0"; break;
                case Piece::PAWN:
                    os << "P"; break;
                case Piece::KNIGHT:
                    os << "N"; break;
                case Piece::BISHOP:
                    os << "B"; break;
                case Piece::ROOK:
                    os << "R"; break;
                case Piece::QUEEN:
                    os << "Q"; break;
                case Piece::KING:
                    os << "K"; break;
            }
        }
        os << std::endl;
    }
    return os;
}

void BoardPosition::Move(const struct Move& move) // simply move piece from one place to another it has to be made sure that that move is possible
{
    int fromX = move.from%10;
    int fromY = move.from/10;
    int toX = move.to%10;
    int toY = move.to/10;

    piecePositions[toX + toY*8] = {piecePositions[fromX + fromY*8].first, piecePositions[fromX + fromY*8].second};
    piecePositions[fromX + fromY*8].first = Piece ::NONE;
    piecePositions[fromX + fromY*8].second = Color::NONE;
}
