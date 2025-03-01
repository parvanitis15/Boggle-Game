#include "Board.h"
#include "Trie.h"
#include "VisitMap.h"
#include "boggle_algorithm.h"
#include "boggle_tester.h"
#include "create_boggle_board.h"

#include <algorithm> // For std::sort
#include <chrono>    // For performance measurement
#include <iostream>
#include <set> // For std::set
#include <string_view>
#include <unordered_map>
#include <vector>

int main()
{
    // Test case 1: few valid words, small board

    // List of words to search for in the Boggle board
    std::vector<std::string_view> wordsList
        = {"TAPS", "ONE",   "RAT",   "TONE",   "PATS", "RATE", "RATES", "SEAT", "SEA",
           "SET",  "SETS",  "TEN",   "TENS",   "SEND", "SENT", "SEG",   "SEAM", "TEAM",
           "TEAR", "TEARS", "STARE", "STARED", "STAR", "TAR",  "TORE",  "TEAS", "POEM",
           "NOTE", "NOTES", "TONES", "PAT",    "SAP",  "SAPS", "DENS",  "DEN",  "TEND",
           "ENDS", "NEAT",  "STEM",  "MIST",   "MATS", "PAST", "PANE"};

    std::cout << "\nWords to find:" << std::endl;
    for (const auto& word : wordsList)
    {
        std::cout << word << " ";
    }
    std::cout << std::endl;

    // Construct Trie using words
    Trie wordsTrie{wordsList};

    // Create a 4x4 Boggle board
    Board board;
    board.rows = 4;
    board.columns = 4;
    board.table = {'T', 'A', 'P', 'S', 'O', 'N', 'E', 'D', 'R', 'A', 'T', 'I', 'M', 'S', 'E', 'G'};

    // Board board = createBoggleBoard<4, 4>();

    // Print the board for visual reference
    std::cout << "Boggle Board:" << std::endl;
    for (size_t i = 0; i < board.rows; ++i)
    {
        for (size_t j = 0; j < board.columns; ++j)
        {
            std::cout << board.getLetter(i, j) << " ";
        }
        std::cout << std::endl;
    }

    // Words that should be found in this board (the expected solution - corrected)
    std::vector<std::string_view> expectedWords
        = {"DEN", "MATS", "NEAT", "ONE",   "PANE", "PAT", "RAT",  "RATE", "RATES",
           "SEA", "SEAM", "SEAT", "SEG",   "SENT", "SET", "SETS", "STAR", "TAPS",
           "TAR", "TEAM", "TEAR", "TEARS", "TEAS", "TEN", "TONE", "TONES"};

    // Performance comparison between recursive and iterative methods
    std::cout << "\n=== Performance Comparison ===" << std::endl;

    // Measure recursive method performance
    auto start_recursive = std::chrono::high_resolution_clock::now();
    auto foundWordsRecursive = findValidWordsInBoardRecursive(wordsTrie, board);
    auto end_recursive = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> recursive_duration = end_recursive - start_recursive;

    // Measure iterative method performance
    auto start_iterative = std::chrono::high_resolution_clock::now();
    auto foundWordsIterative = findValidWordsInBoardIterative(wordsTrie, board);
    auto end_iterative = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> iterative_duration = end_iterative - start_iterative;

    // Print performance results
    std::cout << "Recursive method execution time: " << recursive_duration.count() << " ms"
              << std::endl;
    std::cout << "Iterative method execution time: " << iterative_duration.count() << " ms"
              << std::endl;
    std::cout << "Performance ratio (Recursive/Iterative): "
              << recursive_duration.count() / iterative_duration.count() << std::endl;

    // Verify that both methods produce the same results
    std::cout << "\n=== Method Comparison ===" << std::endl;

    // Sort both result sets for easier comparison
    std::sort(foundWordsRecursive.begin(), foundWordsRecursive.end());
    std::sort(foundWordsIterative.begin(), foundWordsIterative.end());

    // Check if results are identical
    bool resultsMatch = (foundWordsRecursive == foundWordsIterative);
    std::cout << "Both methods produce identical results: " << (resultsMatch ? "YES" : "NO")
              << std::endl;

    // If results don't match, show differences
    if (!resultsMatch)
    {
        std::cout << "\nDifferences between methods:" << std::endl;

        // Find words in recursive but not in iterative
        std::cout << "Words found by recursive but not by iterative method:" << std::endl;
        std::set<std::string> recursiveSet(foundWordsRecursive.begin(), foundWordsRecursive.end());
        std::set<std::string> iterativeSet(foundWordsIterative.begin(), foundWordsIterative.end());

        for (const auto& word : recursiveSet)
        {
            if (iterativeSet.find(word) == iterativeSet.end())
            {
                std::cout << word << " ";
            }
        }
        std::cout << std::endl;

        // Find words in iterative but not in recursive
        std::cout << "Words found by iterative but not by recursive method:" << std::endl;
        for (const auto& word : iterativeSet)
        {
            if (recursiveSet.find(word) == recursiveSet.end())
            {
                std::cout << word << " ";
            }
        }
        std::cout << std::endl;
    }

    // Verify only the iterative method against expected words
    std::cout << "\n=== Verification Against Expected Words ===" << std::endl;

    // Print expected solution for reference
    std::cout << "Expected solution (words that should be found):" << std::endl;
    printWords(expectedWords);

    // Print words found by iterative method
    std::cout << "\nWords found by iterative method:" << std::endl;
    printWords(foundWordsIterative);

    // Run detailed verification for iterative method only
    VerificationResult resultIterative = verifyBoggleResults(expectedWords, foundWordsIterative);
    std::cout << "\nVerification results for iterative method:" << std::endl;
    printVerificationResults(resultIterative);

    return 0;
}
