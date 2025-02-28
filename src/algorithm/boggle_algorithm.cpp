#include "boggle_algorithm.h"

#include "Board.h"
#include "Trie.h"
#include "VisitMap.h"

#include <string>
#include <vector>

// struct ValidWords
// {
//     Trie words;

//     // int isValidWord(const std::string& word)
//     // {
//     //     // TODO: return 0 if it's a completed word, 1 if it's completed word and leaf, -1 if
//     it's not valid
//     // }
// };

ContinueTraversing checkBoardIndex(const Trie &wordsTrie, const Board &board, VisitMap &visitMap,
                                   const std::string &currentWord, int r, int c,
                                   std::vector<std::string> &wordsFound)
{
    // Check bounds
    if ((r < 0) || (r >= static_cast<int>(board.rows)) || (c < 0) ||
        (c >= static_cast<int>(board.columns)))
    {
        return ContinueTraversing::no;
    }

    // Skip index if visited
    if (visitMap.isVisited(static_cast<size_t>(r), static_cast<size_t>(c)))
    {
        return ContinueTraversing::no;
    }

    // Get current word + new letter from board index
    auto currentWordPlusNewLetter{currentWord +
                                  board.getLetter(static_cast<size_t>(r), static_cast<size_t>(c))};

    // Check whether word is in Trie and whether it's a valid word
    auto wordInTrie = wordsTrie.contains(currentWordPlusNewLetter);

    // If it doesn't exist, begin new traversal
    if (wordInTrie == inTrie::doesntExist)
    {
        return ContinueTraversing::no;
    }

    // If it's a word, append to findValidWords
    if (wordInTrie == inTrie::isWord)
    {
        wordsFound.emplace_back(currentWordPlusNewLetter);
    }

    // // Mark index as visited
    // visitMap.markVisited(static_cast<size_t>(r), static_cast<size_t>(c)); // static_cast<size_t>
    // is safe as long as the int is not negative and we've checked for that in bounds checking

    // // Add the letter to the actual word for continuing traversal
    // currentWord = currentWordPlusNewLetter;

    return ContinueTraversing::yes;
}

void traverseBoardRecursively(const Trie &wordsTrie, const Board &board, VisitMap visitMap,
                              std::string currentWord, int rStart, int cStart,
                              std::vector<std::string> &wordsFound)
{
    for (int r{rStart - 1}; r <= rStart + 1; r++)
    {
        for (int c{cStart - 1}; c <= cStart + 1; c++)
        {
            if (checkBoardIndex(wordsTrie, board, visitMap, currentWord, r, c, wordsFound) ==
                ContinueTraversing::yes)
            {
                // Mark index as visited
                auto newVisitMap = visitMap;
                newVisitMap.markVisited(
                    static_cast<size_t>(r),
                    static_cast<size_t>(
                        c)); // static_cast<size_t> is safe as long as the int is not negative and
                             // we've checked for that in bounds checking

                // Add the letter to the actual word for continuing traversal
                auto newCurrentWord{
                    currentWord + board.getLetter(static_cast<size_t>(r), static_cast<size_t>(c))};

                traverseBoardRecursively(wordsTrie, board, newVisitMap, newCurrentWord, r, c,
                                         wordsFound);
            }
        }
    }
}

std::vector<std::string> findValidWordsInBoard(const Trie &wordsTrie, const Board &board)
{
    std::vector<std::string> wordsFound{};

    // Important: we're looping over the major dimension first for better memory caching of our
    // row-major structs
    for (int r{0}; r < static_cast<int>(board.rows); r++)
    {
        for (int c{0}; c < static_cast<int>(board.columns); c++)
        {
            // Store indices that have been already traversed in board
            // Use a VisitMap
            VisitMap visitMap(board.rows, board.columns);

            std::string currentWord{}; // Store current word (letters for each traversal)

            // Check first index here
            // This is important because we want the starting index to be exactly the one from this
            // double-loop and not in the inner traversal loop
            if (checkBoardIndex(wordsTrie, board, visitMap, currentWord, r, c, wordsFound) ==
                ContinueTraversing::yes)
            {
                // Mark index as visited
                visitMap.markVisited(
                    static_cast<size_t>(r),
                    static_cast<size_t>(
                        c)); // static_cast<size_t> is safe as long as the int is not negative and
                             // we've checked for that in bounds checking

                // Add the letter to the actual word for continuing traversal
                currentWord += board.getLetter(static_cast<size_t>(r), static_cast<size_t>(c));

                traverseBoardRecursively(wordsTrie, board, visitMap, currentWord, r, c, wordsFound);
            }
        }
    }

    return wordsFound;
}
