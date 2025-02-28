#include "VisitMap.h"

VisitMap::VisitMap(const std::vector<bool>& truthTable, size_t rows, size_t columns)
{
    // Validate dimensions
    if (truthTable.size() != rows * columns)
    {
        throw std::invalid_argument("Truth table size does not match the specified dimensions");
    }

    this->truthTable = truthTable;
    this->rows = rows;
    this->columns = columns;
}

VisitMap::VisitMap(size_t rows, size_t columns)
    : truthTable(rows * columns, false), rows(rows), columns(columns)
{
}

void VisitMap::markVisited(size_t row, size_t col)
{
    truthTable[row * columns + col] = true;
}

bool VisitMap::isVisited(size_t row, size_t col) const
{
    return truthTable[row * columns + col]; // use operator[] for efficiency, instead of .at()
}
