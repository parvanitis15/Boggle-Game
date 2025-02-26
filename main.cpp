#include <iostream>
#include <vector>


struct Board 
{
    std::vector<char> table;
    size_t rows;
    size_t columns;

    char get_letter(size_t row, size_t col)
    {
        return table[row*columns + col]; // row-major
    }
};


struct trie
{

};


struct ValidWords 
{
    trie words;

    int isValidWord(const std::string& word) 
    {
        // TODO: return 0 if it's a completed word, 1 if it's completed word and leaf, -1 if it's not valid
    }
};


std::vector<std::string> findValidWordsInBoard(const ValidWords& validWords, const Board& board)
{
    for (auto r{0}; r < board.rows; r++)
    {
        // store indices in board that been already traversed
        // std::vector<

        for (auto c{0}; c < board.columns; c++)
        {
            // TODO: check if letter is valid

            // traverse in every direction
        }
    }
}


int main() 
{
    


    return 0;
}
