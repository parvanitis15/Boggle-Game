#include <iostream>
#include <vector>

#include "Trie.h"


// struct ValidWords 
// {
//     Trie words;

//     // int isValidWord(const std::string& word) 
//     // {
//     //     // TODO: return 0 if it's a completed word, 1 if it's completed word and leaf, -1 if it's not valid
//     // }
// };


// std::vector<std::string> findValidWordsInBoard(const ValidWords& validWords, const Board& board)
// {
//     for (auto r{0}; r < board.rows; r++)
//     {
//         // store indices in board that been already traversed
//         // std::vector<

//         for (auto c{0}; c < board.columns; c++)
//         {
//             // TODO: check if letter is valid

//             // traverse in every direction
//         }
//     }
// }


int main() 
{
    // Test case 1: few valid words, small board
    std::vector<std::string_view> wordsList{"gragas", "vladimir", "lucifer", "ashe", "ashes", "dust"};

    Trie trieOfWords{wordsList};

    std::string_view wordTest{"ash"};
    // std::cout << "The trie structure " 
    //     << ((trieOfWords.contains(wordTest)) ? "contains " : "does not contain ")
    //     << "the word " << wordTest << '\n';
    std::cout << "The word " << wordTest << " is " << ((trieOfWords.contains(wordTest)) ? "" : "NOT ")
              << "a valid word in the Trie structure." << '\n';

    return 0;
}
