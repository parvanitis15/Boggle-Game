#ifndef BOGGLE_BOARDS_H
#define BOGGLE_BOARDS_H

#include "Board.h"

#include <array>
#include <vector>

// 3x3 Small board
inline Board createSmallBoard()
{
    Board board;
    board.rows = 3;
    board.columns = 3;
    board.table = {'C', 'A', 'T', 'R', 'E', 'D', 'S', 'I', 'N'};
    return board;
}

// 4x4 Medium board (standard Boggle size)
inline Board createMediumBoard()
{
    Board board;
    board.rows = 4;
    board.columns = 4;
    board.table = {'T', 'A', 'P', 'S', 'O', 'N', 'E', 'D', 'R', 'A', 'T', 'I', 'M', 'S', 'E', 'G'};
    return board;
}

// 5x5 Large board
inline Board createLargeBoard()
{
    Board board;
    board.rows = 5;
    board.columns = 5;
    board.table = {'W', 'O', 'R', 'L', 'D', 'H', 'E', 'A', 'R', 'T', 'S', 'T', 'A',
                   'R', 'S', 'P', 'L', 'A', 'N', 'E', 'B', 'O', 'A', 'R', 'D'};
    return board;
}

// 6x6 Huge board
inline Board createHugeBoard()
{
    Board board;
    board.rows = 6;
    board.columns = 6;
    board.table = {'S', 'T', 'A', 'R', 'T', 'S', 'H', 'E', 'A', 'R', 'T', 'H',
                   'O', 'T', 'H', 'E', 'R', 'S', 'W', 'O', 'R', 'L', 'D', 'S',
                   'P', 'L', 'A', 'N', 'E', 'T', 'S', 'P', 'A', 'C', 'E', 'S'};
    return board;
}

#endif // BOGGLE_BOARDS_H
