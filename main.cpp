#include <iostream>
#include <vector>
#include <unordered_map>
#include <string_view>

#include "Trie.h"
#include "Board.h"
#include "VisitMap.h"
#include "boggle_tester.h"


// struct ValidWords 
// {
//     Trie words;

//     // int isValidWord(const std::string& word) 
//     // {
//     //     // TODO: return 0 if it's a completed word, 1 if it's completed word and leaf, -1 if it's not valid
//     // }
// };



enum ContinueTraversing
{
    yes,
    no
};


ContinueTraversing checkBoardIndex(const Trie& wordsTrie, const Board& board, VisitMap& visitMap,
    std::string currentWord, int r, int c, std::vector<std::string>& wordsFound)
{
    // Check bounds
    if ((r < 0) || (r >= static_cast<int>(board.rows)) 
        || (c < 0) || (c >= static_cast<int>(board.columns)))
    {
        return ContinueTraversing::no;
    }

    // Skip index if visited
    if (visitMap.isVisited(static_cast<size_t>(r), static_cast<size_t>(c)))
    {
        return ContinueTraversing::yes;
    }

    // Mark index as visited
    visitMap.markVisited(static_cast<size_t>(r), static_cast<size_t>(c)); // static_cast<size_t> is safe as long as the int is not negative and we've checked for that in bounds checking

    // Append letter to current word
    currentWord += board.getLetter(static_cast<size_t>(r), static_cast<size_t>(c));

    // Check whether word is in Trie and whether it's a valid word
    auto wordInTrie = wordsTrie.contains(currentWord);

    // If it doesn't exist, begin new traversal
    if (wordInTrie == inTrie::doesntExist)
    {
        return ContinueTraversing::no;
    }

    // If it's a word, append to findValidWords
    if (wordInTrie == inTrie::isWord)
    {
        wordsFound.emplace_back(currentWord);
    }

    return ContinueTraversing::yes;
}

// Recursion function to traverse adjacent index in board
// while the Trie contains the current word
void traverseBoardRecursively(const Trie& wordsTrie, const Board& board, VisitMap& visitMap,
     std::string currentWord, int rStart, int cStart, std::vector<std::string>& wordsFound)
{
    for (int r{rStart-1}; r <= rStart + 1; r++)
    {
        for (int c{cStart-1}; c <= cStart + 1; c++)
        {
            // Shouldn't be much faster than simply using the VisitMap
            // // Check whether it's the starting point
            // if ((r == rStart) && (c == cStart))
            // {
            //     continue;
            // }
            
            if (checkBoardIndex(wordsTrie, board, visitMap, currentWord, r, c, wordsFound) == ContinueTraversing::yes)
            {
                traverseBoardRecursively(wordsTrie, board, visitMap, currentWord, r, c, wordsFound);
            }
        }
    }
}


std::vector<std::string> findValidWordsInBoard(const Trie& wordsTrie, const Board& board)
{
    std::vector<std::string> wordsFound{};

    // Important: we're looping over the major dimension first for better memory caching of our row-major structs
    for (int r{0}; r < static_cast<int>(board.rows); r++)
    {
        for (int c{0}; c < static_cast<int>(board.columns); c++)
        {
            // Store indices that have been already traversed in board
            // Use a VisitMap
            VisitMap visitMap(board.rows, board.columns);

            std::string currentWord{}; // Store current word (letters for each traversal)

            // Check first index here
            // This is important because we want the starting index to be exactly the one from this double-loop
            // and not in the inner traversal loop
            if (checkBoardIndex(wordsTrie, board, visitMap, currentWord, r, c, wordsFound) == ContinueTraversing::yes)
            {
                traverseBoardRecursively(wordsTrie, board, visitMap, currentWord, r, c, wordsFound);
            }
        }
    }

    return wordsFound;
}


int main() 
{
    // Test case 1: few valid words, small board

    // List of words to search for in the Boggle board
    std::vector<std::string_view> wordsList = {
        "TAPS", "ONE", "RAT", "TONE", "PATS", "RATE", "RATES", "SEAT", "SEA", 
        "SET", "SETS", "TEN", "TENS", "SEND", "SENT", "SEG", "SEAM", "TEAM",
        "TEAR", "TEARS", "STARE", "STARED", "STAR", "TAR", "TORE", "TEAS",
        "POEM", "NOTE", "NOTES", "TONES", "PAT", "SAP", "SAPS", "DENS", "DEN"
    };
    
    std::cout << "\nWords to find:" << std::endl;
    for (const auto& word : wordsList) {
        std::cout << word << " ";
    }
    std::cout << std::endl;

    // Construct Trie using words
    Trie wordsTrie{wordsList};

    // std::string_view wordTest{"ash"};
    // std::cout << "The word '" << wordTest << "' is " << ((wordsTrie.contains(wordTest)) ? "" : "NOT ")
    //           << "a valid word in the Trie structure." << '\n';

    // Create a 4x4 Boggle board
    Board board;
    board.rows = 4;
    board.columns = 4;
    board.table = {
        'T', 'A', 'P', 'S',
        'O', 'N', 'E', 'D',
        'R', 'A', 'T', 'I',
        'M', 'S', 'E', 'G'};

    // Print the board for visual reference
    std::cout << "Boggle Board:" << std::endl;
    for (size_t i = 0; i < board.rows; ++i) {
        for (size_t j = 0; j < board.columns; ++j) {
            std::cout << board.getLetter(i, j) << " ";
        }
        std::cout << std::endl;
    }

    // Words that should be found in this board (the expected solution)
    std::vector<std::string_view> expectedWords = {
        "TAPS", "ONE", "RAT", "TONE", "PATS", "RATE", "SEAT", "SEA",
        "SET", "TEN", "SEND", "SENT", "SEG", "TEAM", "TEAR", "STAR",
        "TAR", "NOTE", "PAT", "SAP", "DENS", "DEN"};

    // Your Boggle solver implementation would go here
    auto foundWords = findValidWordsInBoard(wordsTrie, board);
    
    // Validate the results
    std::cout << "\nWords found by your implementation:" << std::endl;
    printWords(foundWords);  // This will use the string version of printWords
    
    // Run detailed verification
    VerificationResult result = verifyBoggleResults(expectedWords, foundWords);
    
    // Print verification results
    printVerificationResults(result);
    
    // Print expected solution for reference
    std::cout << "\nExpected solution (words that should be found):" << std::endl;
    printWords(expectedWords);  // This will use the string_view version of printWords

    return 0;
}
