#include "boggle_tester.h"

#include "Board.h"

#include <iomanip>
#include <iostream>

// Print the Boggle board
[[maybe_unused]] void printBoard(const Board& board)
{
    for (size_t i = 0; i < board.rows; ++i)
    {
        for (size_t j = 0; j < board.columns; ++j)
        {
            std::cout << board.getLetter(i, j) << " ";
        }
        std::cout << std::endl;
    }
}

// Print a list of words (string_view version)
void printWords(const std::vector<std::string_view>& words)
{
    for (const auto& word : words)
    {
        std::cout << word << " ";
    }
    std::cout << std::endl;
}

// Print a list of words (string version)
void printWords(const std::vector<std::string>& words)
{
    for (const auto& word : words)
    {
        std::cout << word << " ";
    }
    std::cout << std::endl;
}

// Count occurrences of each word in a list (string version)
std::unordered_map<std::string, int> countWordOccurrences(const std::vector<std::string>& words)
{
    std::unordered_map<std::string, int> wordCounts;
    for (const auto& word : words)
    {
        wordCounts[word]++;
    }
    return wordCounts;
}

// Verify Boggle results by comparing expected words with found words
VerificationResult verifyBoggleResults(const std::vector<std::string_view>& expectedWords,
                                       const std::vector<std::string>& foundWords)
{
    VerificationResult result;
    result.allExpectedWordsFound = true;
    result.extraWordsFound = false;
    result.duplicatesFound = false;

    // Count word occurrences
    result.wordCounts = countWordOccurrences(foundWords);

    // Check for duplicates
    for (const auto& [word, count] : result.wordCounts)
    {
        if (count > 1)
        {
            result.duplicatesFound = true;
            break;
        }
    }

    // Convert expected words to strings and then to a set for easier checking
    std::unordered_set<std::string> expectedWordsSet;
    for (const auto& word : expectedWords)
    {
        expectedWordsSet.insert(std::string(word));
    }

    // Convert found words to a set to check coverage
    std::unordered_set<std::string> foundWordsSet;
    for (const auto& [word, count] : result.wordCounts)
    {
        foundWordsSet.insert(word);
    }

    // Check missing words
    for (const auto& word : expectedWordsSet)
    {
        if (foundWordsSet.find(word) == foundWordsSet.end())
        {
            result.missingWords.push_back(word);
            result.allExpectedWordsFound = false;
        }
    }

    // Check extra words
    for (const auto& word : foundWordsSet)
    {
        if (expectedWordsSet.find(word) == expectedWordsSet.end())
        {
            result.extraWords.push_back(word);
            result.extraWordsFound = true;
        }
    }

    return result;
}

// Print detailed verification results
void printVerificationResults(const VerificationResult& result)
{
    std::cout << "\nVerification results:" << std::endl;

    // Print words that appear multiple times
    if (result.duplicatesFound)
    {
        std::cout << "Words found multiple times:" << std::endl;
        for (const auto& [word, count] : result.wordCounts)
        {
            if (count > 1)
            {
                std::cout << "  " << word << " (found " << count << " times)" << std::endl;
            }
        }
    }
    else
    {
        std::cout << "No duplicate words found." << std::endl;
    }

    // Print missing words
    if (!result.missingWords.empty())
    {
        std::cout << "Missing expected words:" << std::endl;
        for (const auto& word : result.missingWords)
        {
            std::cout << "  " << word << std::endl;
        }
    }

    // Print extra words
    if (!result.extraWords.empty())
    {
        std::cout << "Extra words found:" << std::endl;
        for (const auto& word : result.extraWords)
        {
            std::cout << "  " << word << std::endl;
        }
    }

    // Final verification result
    if (result.allExpectedWordsFound && !result.extraWordsFound)
    {
        std::cout << "\nTest PASSED: All expected words were found!" << std::endl;
        if (result.duplicatesFound)
        {
            std::cout << "Note: Some words were found multiple times through different paths."
                      << std::endl;
        }
    }
    else
    {
        std::cout << "\nTest FAILED: There are discrepancies between expected and found words."
                  << std::endl;
    }
}
