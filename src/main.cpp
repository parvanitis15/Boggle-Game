#include <iostream>
#include <vector>
#include <unordered_map>
#include <string_view>

#include "boggle_algorithm.h"
#include "Trie.h"
#include "Board.h"
#include "VisitMap.h"
#include "boggle_tester.h"


int main() 
{
    // Test case 1: few valid words, small board

    // List of words to search for in the Boggle board
    std::vector<std::string_view> wordsList = {
        "TAPS", "ONE", "RAT", "TONE", "PATS", "RATE", "RATES", "SEAT", "SEA", 
        "SET", "SETS", "TEN", "TENS", "SEND", "SENT", "SEG", "SEAM", "TEAM",
        "TEAR", "TEARS", "STARE", "STARED", "STAR", "TAR", "TORE", "TEAS",
        "POEM", "NOTE", "NOTES", "TONES", "PAT", "SAP", "SAPS", "DENS", "DEN",
        "TEND", "ENDS", "NEAT", "STEM", "MIST", "MATS", "PAST", "PANE"
    };
    
    std::cout << "\nWords to find:" << std::endl;
    for (const auto& word : wordsList) {
        std::cout << word << " ";
    }
    std::cout << std::endl;

    // Construct Trie using words
    Trie wordsTrie{wordsList};

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

    // Words that should be found in this board (the expected solution - corrected)
    std::vector<std::string_view> expectedWords = {
        "DEN", "MATS", "NEAT", "ONE", "PANE", "PAT",
        "RAT", "RATE", "RATES", "SEA", "SEAM", "SEAT",
        "SEG", "SENT", "SET", "SETS", "STAR", "TAPS", "TAR",
        "TEAM", "TEAR", "TEARS", "TEAS", "TEN", "TONE", "TONES"};

    // Your Boggle solver implementation would go here
    auto foundWords = findValidWordsInBoard(wordsTrie, board);

    // Print expected solution for reference
    std::cout << "\nExpected solution (words that should be found):" << std::endl;
    printWords(expectedWords);  // This will use the string_view version of printWords
    
    // Validate the results
    std::cout << "\nWords found:" << std::endl;
    printWords(foundWords);  // This will use the string version of printWords
    
    // Run detailed verification
    VerificationResult result = verifyBoggleResults(expectedWords, foundWords);
    
    // Print verification results
    printVerificationResults(result);

    return 0;
}
