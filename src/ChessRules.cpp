#include <algorithm>
#include "ChessRules.h"

// make a compression utilities function library
// with a function decompress which takes int pos and returns a C++17 packed double return value
inline std::pair<int, int> decompressPosition(int pos){ return std::make_pair<int,int>(pos%10, pos/10);}
inline int compressPosition(int x, int y){return x + 10*y;}

namespace ChessRule
{
    std::vector<Move> AllPossibleMoves(const BoardPosition& position)
    {
        std::vector<Move> result;
        std::vector<Move> temp;

        for(int i = 0; i < 8; i++)
        {
            for(int j = 0; j < 8; j++)
            {
                int coordinate = compressPosition(j, i);
                const auto& piece = position.piecePositions[i*8 + j];
                if(piece.second == position.toMove)
                {
                    switch(piece.first)
                    {
                        default: break;
                        case Piece::PAWN:
                            temp = PawnMoves(position, coordinate);
                            break;
                        case Piece::KNIGHT:
                            temp = KnightMoves(position, coordinate);
                            break;
                        case Piece::BISHOP:
                            temp = BishopMoves(position, coordinate);
                            break;
                        case Piece::ROOK:
                            temp = RookMoves(position, coordinate);
                            break;
                        case Piece::QUEEN:
                            temp = QueenMoves(position, coordinate);
                            break;
                        case Piece::KING:
                            temp = KingMoves(position, coordinate);
                            break;
                    }
                    result.insert(result.begin(), temp.begin(), temp.end());
                }
            }
        }
        return std::move(result);
    }

    std::vector<Move> PawnMoves(const BoardPosition& position, int pos)
    {
        auto [X,Y] = decompressPosition(pos);

        std::vector<Move> result;

        int multiplyer = (position.toMove == Color::WHITE ? 1 : -1);
        Color notMe = position.toMove == Color::WHITE ? Color::BLACK : Color::WHITE;

        // handle promotion
        if ((Y == 6 and isFree(position, X, Y + 1)) or (Y == 1 and isFree(position, X, Y - 1)))
        {
            result.push_back(Promotion(compressPosition(X,Y), compressPosition(X, Y + multiplyer)).Into(Piece::KNIGHT));
            result.push_back(Promotion(compressPosition(X,Y), compressPosition(X, Y + multiplyer)).Into(Piece::BISHOP));
            result.push_back(Promotion(compressPosition(X,Y), compressPosition(X, Y + multiplyer)).Into(Piece::ROOK));
            result.push_back(Promotion(compressPosition(X,Y), compressPosition(X, Y + multiplyer)).Into(Piece::QUEEN));
        }

        // handle movement by 1 or 2
        if(isFree(position, X, Y + multiplyer))
        {
            result.emplace_back(compressPosition(X,Y), compressPosition(X, Y + multiplyer));
            if(isFree(position, X, Y + 2*multiplyer) and (Y - multiplyer == 0 or Y - multiplyer == 7))
                result.push_back(EnPassantCreating(compressPosition(X,Y), compressPosition(X, Y + 2*multiplyer)));
        }

        // handle taking other figures
        if(X < 7 and isOfColor(position,  X + 1, Y + multiplyer, notMe)) // if other color on diagonal
        {
            result.emplace_back(compressPosition(X,Y), compressPosition(X+1, Y + multiplyer));
        }
        if(X > 0 and isOfColor(position, X - 1, Y + multiplyer, notMe))
        {
            result.emplace_back(compressPosition(X,Y), compressPosition(X-1, Y + multiplyer));
        }

        // handle Enpassant
        auto [EnX,EnY] = decompressPosition(position.enPassantSquare);
        if(EnY == Y + multiplyer and (EnX == X + 1 or EnX == X - 1))
            result.push_back(EnPassant(compressPosition(X,Y), compressPosition(EnX, EnY)));

        return result;
    }

    std::vector<Move> KnightMoves(const BoardPosition& position, int pos)
    {
        auto [X,Y] = decompressPosition(pos);
        // declare all possible increments that can be done for a knight
        std::vector<std::pair<int, int>> increments{{1,2}, {1,-2}, {2,1}, {2,-1},
                                              {-1,2}, {-1,-2}, {-2,1}, {-2,-1}};

        std::vector<Move> result;

        for(const auto& inc : increments)
        {
            // if the new point is inside the board
            if(X + inc.first >= 0 and X + inc.first < 8 and Y + inc.second >= 0 and Y + inc.second < 8)
                if(!isOfColor(position, X + inc.first, Y + inc.second, position.piecePositions[X + 8*Y].second))
                    result.emplace_back(compressPosition(X,Y), compressPosition(X+inc.first, Y+inc.second));
        }

        return result;
    }


    std::vector<Move> BishopMoves(const BoardPosition& position, int pos)
    {
        auto [X,Y] = decompressPosition(pos);
        int savedX = X;
        int savedY = Y;
        std::vector<Move> result;

        while(X + 1 < 8 and Y + 1 < 8)
        {
            X++; Y++;
            if(isFree(position, X, Y)) // if its free just keep iterating
                result.emplace_back(compressPosition(savedX,savedY), compressPosition(X, Y));
            else if(isOfColor(position ,X, Y, position.piecePositions[X + 8*Y].second)) // if its of the same color stop iterating
                break;
            else { // if its a different color it takes but cant move further
                result.emplace_back(compressPosition(savedX, savedY), compressPosition(X, Y));
                break;
            }
        }
        X = savedX;
        Y = savedY;

        while(X - 1 > 0 and Y - 1 > 0)
        {
            X--; Y--;
            if(isFree(position, X, Y)) // if its free just keep iterating
                result.emplace_back(compressPosition(savedX,savedY), compressPosition(X, Y));
            else if(isOfColor(position ,X, Y, position.piecePositions[X + 8*Y].second)) // if its of the same color stop iterating
                break;
            else { // if its a different color it takes but cant move further
                result.emplace_back(compressPosition(savedX, savedY), compressPosition(X, Y));
                break;
            }
        }
        X = savedX;
        Y = savedY;

        while(X + 1 < 9 and Y - 1 > 0)
        {
            X++; Y--;
            if(isFree(position, X, Y)) // if its free just keep iterating
                result.emplace_back(compressPosition(savedX,savedY), compressPosition(X, Y));
            else if(isOfColor(position ,X, Y, position.piecePositions[X + 8*Y].second)) // if its of the same color stop iterating
                break;
            else { // if its a different color it takes but cant move further
                result.emplace_back(compressPosition(savedX, savedY), compressPosition(X, Y));
                break;
            }
        }
        X = savedX;
        Y = savedY;

        while(X - 1 > 0 and Y + 1 < 9)
        {
            X--; Y++;
            if(isFree(position, X, Y)) // if its free just keep iterating
                result.emplace_back(compressPosition(savedX, savedY), compressPosition(X, Y));
            else if(isOfColor(position ,X, Y, position.piecePositions[X + 8*Y].second)) // if its of the same color stop iterating
                break;
            else { // if its a different color it takes but cant move further
                result.emplace_back(compressPosition(savedX, savedY), compressPosition(X, Y));
                break;
            }
        }
        return std::move(result);
    }


    std::vector<Move> RookMoves(const BoardPosition& position, int pos)
    {
        auto [X,Y] = decompressPosition(pos);
        std::vector<Move> result;

        for(int i = X+1; i < 8; i++)
        {
            if(isFree(position, i, Y)) // if its free just keep iterating
                result.emplace_back(compressPosition(X,Y), compressPosition(i, Y));
            else if(isOfColor(position ,i, Y, position.piecePositions[i + 8*Y].second)) // if its of the same color stop iterating
                break;
            else { // if its a different color it takes but cant move further
                result.emplace_back(compressPosition(X, Y), compressPosition(i, Y));
                break;
            }
        }
        for(int i = X-1; i > 0; i--) // how can i make it one loop or something
        {
            if(isFree(position, i, Y))
                result.emplace_back(compressPosition(X,Y), compressPosition(i, Y));
            else if(isOfColor(position ,i, Y, position.piecePositions[i + 8*Y].second))
                break;
            else {
                result.emplace_back(compressPosition(X, Y), compressPosition(i, Y));
                break;
            }
        }
        for(int i = Y+1; i < 8; i++)
        {
            if(isFree(position, X, i))
                result.emplace_back(compressPosition(X,Y), compressPosition(X, i));
            else if(isOfColor(position ,X, i, position.piecePositions[X + 8*i].second))
                break;
            else {
                result.emplace_back(compressPosition(X, Y), compressPosition(Y, i));
                break;
            }
        }
        for(int i = Y-1; i > 0; i--) // how can i make it one loop or something
        {
            if(isFree(position, X, i))
                result.emplace_back(compressPosition(X,Y), compressPosition(X, i));
            else if(isOfColor(position ,X, i, position.piecePositions[X + 8*i].second))
                break;
            else {
                result.emplace_back(compressPosition(X, Y), compressPosition(X, i));
                break;
            }
        }
        return std::move(result);
    }

    std::vector<Move> QueenMoves(const BoardPosition& position, int pos)
    {
       std::vector<Move> result = BishopMoves(position, pos);
       std::vector<Move> AlsoResult = RookMoves(position, pos);

       result.insert(result.end(), AlsoResult.begin(), AlsoResult.end());
       return std::move(result);
    }

    std::vector<Move> KingMoves(const BoardPosition& position, int pos)
    {
        auto [X,Y] = decompressPosition(pos);

        std::vector<Move> result;
        int lesserX = std::max(X - 1, 0);
        int lesserY = std::max(Y - 1, 0);
        int biggerX = std::min(X + 1, 7);
        int biggerY = std::min(Y + 1, 7);

        if(!isOfColor(position, lesserX, Y, position.piecePositions[X + 8*Y].second)) result.emplace_back(lesserX, Y);
        if(!isOfColor(position, lesserX, lesserY, position.piecePositions[X + 8*Y].second)) result.emplace_back(lesserX, lesserY);
        if(!isOfColor(position, lesserX, biggerY, position.piecePositions[X + 8*Y].second)) result.emplace_back(lesserX, biggerY);
        if(!isOfColor(position, X, lesserY, position.piecePositions[X + 8*Y].second)) result.emplace_back(X, lesserY);
        if(!isOfColor(position, X, biggerY, position.piecePositions[X + 8*Y].second)) result.emplace_back(X, biggerY);
        if(!isOfColor(position, biggerX, Y, position.piecePositions[X + 8*Y].second)) result.emplace_back(biggerX, Y);
        if(!isOfColor(position, biggerX, lesserY, position.piecePositions[X + 8*Y].second)) result.emplace_back(biggerX, lesserY);
        if(!isOfColor(position, biggerX, biggerY, position.piecePositions[X + 8*Y].second)) result.emplace_back(biggerX, biggerY);

        return std::move(result);
    }


    std::vector<Move> CastleMoves(const BoardPosition& position, int pos)
    {

    }


    [[nodiscard]] inline bool isFree(const BoardPosition& position, int x, int y)
    {
        return position.piecePositions[x + 8*y].first == Piece::NONE;
    }

    [[nodiscard]] inline bool isOfColor(const BoardPosition& position, int x, int y, Color color)
    {
        return position.piecePositions[x + 8*y].second == color;
    }

}
