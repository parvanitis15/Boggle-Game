#include "Board.h"
#include "Trie.h"
#include "boggle_algorithm.h"
#include "create_boggle_board.h"
#include "word_list.h"

#include <chrono>
#include <functional>
#include <gtest/gtest.h>
#include <string>
#include <unordered_map>

class BogglePerformanceTest : public ::testing::Test
{
protected:
    using Clock = std::chrono::high_resolution_clock;
    using Duration = std::chrono::microseconds;
    using AlgorithmFunction = std::function<std::vector<std::string>(const Trie&, const Board&)>;

    // Map of algorithm names to their implementations
    std::unordered_map<std::string, AlgorithmFunction> algorithms
        = {{"Recursive", findValidWordsInBoardRecursive},
           {"Iterative", findValidWordsInBoardIterative}};

    // Measure performance of a single algorithm
    Duration measureAlgorithmPerformance(const std::string& algorithmName, const Trie& wordsTrie,
                                         const Board& board, std::vector<std::string>& foundWords)
    {
        // Get the algorithm function from the map
        auto algorithmFunc = algorithms.at(algorithmName);

        auto start = Clock::now();
        foundWords = algorithmFunc(wordsTrie, board);
        auto end = Clock::now();

        return std::chrono::duration_cast<Duration>(end - start);
    }

    // Compare performance of all algorithms on the same board and word list
    void compareAlgorithms(const std::string& boardName, const Board& board,
                           const std::string& listName, const auto& wordList)
    {
        Trie wordsTrie{wordList};

        // Store results for each algorithm
        struct AlgorithmResult
        {
            Duration duration{};                   // Initialize with default constructor
            std::vector<std::string> foundWords{}; // Initialize with default constructor

            // Constructor for initialization
            AlgorithmResult(Duration d, std::vector<std::string> words)
                : duration(d), foundWords(std::move(words))
            {
            }

            // Default constructor required for map
            AlgorithmResult() = default;
        };

        std::unordered_map<std::string, AlgorithmResult> results;

        // Run each algorithm and collect results
        for (const auto& [algorithmName, _] : algorithms)
        {
            std::vector<std::string> foundWords;
            auto duration
                = measureAlgorithmPerformance(algorithmName, wordsTrie, board, foundWords);

            results.insert({algorithmName, AlgorithmResult(duration, foundWords)});

            std::cout << "\nPerformance for " << boardName << " with " << listName << " using "
                      << algorithmName << " algorithm:\n"
                      << "Board size: " << board.rows << "x" << board.columns << "\n"
                      << "Time: " << duration.count() << " microseconds\n"
                      << "Words found: " << foundWords.size() << "\n";

            // Verify that the algorithm completes within a reasonable time
            EXPECT_LT(duration.count(), 1000000) << algorithmName << " algorithm took too long";
        }

        // Verify that all algorithms found the same number of words
        if (algorithms.size() > 1)
        {
            auto firstAlgorithm = algorithms.begin()->first;
            auto firstSize = results.at(firstAlgorithm).foundWords.size();

            for (const auto& [algorithmName, result] : results)
            {
                if (algorithmName != firstAlgorithm)
                {
                    EXPECT_EQ(result.foundWords.size(), firstSize)
                        << algorithmName << " found " << result.foundWords.size() << " words, but "
                        << firstAlgorithm << " found " << firstSize;
                }
            }
        }
    }
};

// Test cases for different board sizes and word lists
TEST_F(BogglePerformanceTest, SmallBoard_BasicList)
{
    compareAlgorithms("Small Board (4x4)", createBoggleBoard<4, 4>(), "Basic Word List", WORD_LIST);
}

TEST_F(BogglePerformanceTest, SmallBoard_ExtendedList)
{
    compareAlgorithms("Small Board (4x4)", createBoggleBoard<4, 4>(), "Extended Word List",
                      EXTENDED_WORD_LIST);
}

TEST_F(BogglePerformanceTest, MediumBoard_BasicList)
{
    compareAlgorithms("Medium Board (8x8)", createBoggleBoard<8, 8>(), "Basic Word List",
                      WORD_LIST);
}

TEST_F(BogglePerformanceTest, MediumBoard_ExtendedList)
{
    compareAlgorithms("Medium Board (8x8)", createBoggleBoard<8, 8>(), "Extended Word List",
                      EXTENDED_WORD_LIST);
}

TEST_F(BogglePerformanceTest, LargeBoard_BasicList)
{
    compareAlgorithms("Large Board (16x16)", createBoggleBoard<16, 16>(), "Basic Word List",
                      WORD_LIST);
}

TEST_F(BogglePerformanceTest, LargeBoard_ExtendedList)
{
    compareAlgorithms("Large Board (16x16)", createBoggleBoard<16, 16>(), "Extended Word List",
                      EXTENDED_WORD_LIST);
}

TEST_F(BogglePerformanceTest, HugeBoard_BasicList)
{
    compareAlgorithms("Huge Board (32x32)", createBoggleBoard<32, 32>(), "Basic Word List",
                      WORD_LIST);
}

TEST_F(BogglePerformanceTest, HugeBoard_ExtendedList)
{
    compareAlgorithms("Huge Board (32x32)", createBoggleBoard<32, 32>(), "Extended Word List",
                      EXTENDED_WORD_LIST);
}
