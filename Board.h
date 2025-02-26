#ifndef BOARD_H
#define BOARD_H

#include <vector>

struct Board 
{
    std::vector<char> table;
    size_t rows;
    size_t columns;

    // Function to get letter at row and col from Board
    char get_letter(size_t row, size_t col);
};

#endif // BOARD_H
