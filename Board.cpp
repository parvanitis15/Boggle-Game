#include "Board.h"

#include <vector>

char Board::get_letter(size_t row, size_t col)
{
    // Don't use vector.at() for efficiency
    return table[row*columns + col]; // row-major
}
