#include <vector>
#include <random>
#include "Board.h"

// Returns a random letter from the alphabet
inline char getRandomLetter(double vowelProbability = 0.35)
{
    static const std::string vowels = "AEIOU";
    static const std::string consonants = "BCDFGHJKLMNPQRSTVWXYZ";
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<std::size_t> vowelDist(0, vowels.size() - 1);
    static std::uniform_int_distribution<std::size_t> consonantDist(0, consonants.size() - 1);
    static std::uniform_real_distribution<double> vowelChance(0.0, 1.0);

    return (vowelChance(gen) < vowelProbability) ? vowels[vowelDist(gen)] : consonants[consonantDist(gen)];
}

// Creates a Boggle board with compile-time dimensions
template <size_t Rows, size_t Columns>
inline Board createBoggleBoard()
{
    Board board;
    board.rows = Rows;
    board.columns = Columns;
    board.table.reserve(Rows * Columns);

    for (size_t i = 0; i < Rows * Columns; ++i)
    {
        board.table.push_back(getRandomLetter());
    }

    return board;
}
