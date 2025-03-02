#ifndef VISITMAP_H
#define VISITMAP_H

#include <stdexcept>
#include <vector>

// Class similar to Board, indicating whether an index in a table (board) has been visited
class VisitMap
{
private:
    std::vector<bool> truthTable{}; // row-major
    size_t rows{0};
    size_t columns{0};

public:
    VisitMap() = delete; // Delete default constructor (and create a modified one which ensures
                         // adherence to class invariant)

    // Modified original constructor with validation
    VisitMap(const std::vector<bool>& truthTable, size_t rows, size_t columns);

    // New constructor that initializes truthTable with all false values
    VisitMap(size_t rows, size_t columns);

    void markVisited(size_t row, size_t col);

    // Function to unmark a position as visited
    void unmarkVisited(size_t row, size_t col);

    // Function to get whether a position has been visited
    bool isVisited(size_t row, size_t col) const;
};

#endif // VISITMAP_H
