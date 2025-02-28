#ifndef BOGGLE_TESTER_H
#define BOGGLE_TESTER_H

#include <iostream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// Forward declaration of Board struct for use in function signatures
struct Board;

// Structure to hold verification results
struct VerificationResult
{
    bool allExpectedWordsFound{};
    bool extraWordsFound{};
    bool duplicatesFound{};
    std::vector<std::string> missingWords{};
    std::vector<std::string> extraWords{};
    std::unordered_map<std::string, int> wordCounts{};
};

// Print the Boggle board
void printBoard(const Board& board);

// Print a list of words (string_view version)
void printWords(const std::vector<std::string_view>& words);

// Print a list of words (string version)
void printWords(const std::vector<std::string>& words);

// Count occurrences of each word in a list (string version)
std::unordered_map<std::string, int> countWordOccurrences(const std::vector<std::string>& words);

// Verify Boggle results by comparing expected words with found words
VerificationResult verifyBoggleResults(const std::vector<std::string_view>& expectedWords,
                                       const std::vector<std::string>& foundWords);

// Print detailed verification results
void printVerificationResults(const VerificationResult& result);

#endif // BOGGLE_TESTER_H
