#include "Board.h"

#include <vector>

char Board::getLetter(size_t row, size_t col) const
{
    // Don't use vector.at() for efficiency
    return table[row * columns + col]; // row-major
}
