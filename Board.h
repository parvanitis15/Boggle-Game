#ifndef BOARD_H
#define BOARD_H

#include <vector>

struct Board 
{
    std::vector<char> table{}; // row-major
    size_t rows{0};
    size_t columns{0};
    // TODO: use static_assert to assert that number of rows and columns can fit into the size_t

    // Function to get letter at row and col from Board
    char getLetter(size_t row, size_t col) const;
};

#endif // BOARD_H
