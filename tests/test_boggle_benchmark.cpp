#include "Board.h"
#include "Trie.h"
#include "boggle_algorithm.h"
#include "create_boggle_board.h"
#include "word_list.h"

#include <chrono>
#include <functional>
#include <gtest/gtest.h>
#include <iomanip>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

class BoggleBenchmarkTest : public ::testing::Test
{
protected:
    using Clock = std::chrono::high_resolution_clock;
    using Duration = std::chrono::microseconds;
    using AlgorithmFunction = std::function<std::vector<std::string>(const Trie&, const Board&)>;

    // Map of algorithm names to their implementations
    std::unordered_map<std::string, AlgorithmFunction> algorithms
        = {{"Recursive", findValidWordsInBoardRecursive},
           {"Iterative", findValidWordsInBoardIterative}};

    // Measure performance of a single algorithm run
    Duration measureAlgorithmPerformance(const AlgorithmFunction& algorithmFunc,
                                         const Trie& wordsTrie, const Board& board,
                                         std::vector<std::string>& foundWords)
    {
        auto start = Clock::now();
        foundWords = algorithmFunc(wordsTrie, board);
        auto end = Clock::now();

        return std::chrono::duration_cast<Duration>(end - start);
    }

    // Run benchmark with multiple iterations and calculate mean execution time
    void runBenchmark(const std::string& boardName, const Board& board, const std::string& listName,
                      const auto& wordList, int numIterations = 10)
    {
        Trie wordsTrie{wordList};

        // Store results for each algorithm
        struct AlgorithmResult
        {
            std::vector<Duration> durations{};
            Duration meanDuration{};
            std::vector<std::string> foundWords{};

            // Default constructor with member initialization
            AlgorithmResult() : durations{}, meanDuration{}, foundWords{}
            {
            }
        };

        std::unordered_map<std::string, AlgorithmResult> results;

        // Run each algorithm multiple times and collect results
        for (const auto& [algorithmName, algorithmFunc] : algorithms)
        {
            AlgorithmResult result;

            std::cout << "\nRunning " << numIterations << " iterations for " << algorithmName
                      << " algorithm on " << boardName << " with " << listName << "...\n";

            // Run the algorithm numIterations times
            for (int i = 0; i < numIterations; ++i)
            {
                std::vector<std::string> foundWords;
                auto duration
                    = measureAlgorithmPerformance(algorithmFunc, wordsTrie, board, foundWords);

                // Store the duration
                result.durations.push_back(duration);

                // Store the found words (only need to do this once)
                if (result.foundWords.empty())
                {
                    result.foundWords = foundWords;
                }

                std::cout << "  Iteration " << (i + 1) << ": " << duration.count()
                          << " microseconds\n";
            }

            // Calculate mean duration
            auto totalDuration
                = std::accumulate(result.durations.begin(), result.durations.end(), Duration(0),
                                  [](const Duration& a, const Duration& b)
                                  { return Duration(a.count() + b.count()); });
            result.meanDuration = Duration(totalDuration.count() / numIterations);

            results[algorithmName] = result;

            std::cout << "\nResults for " << algorithmName << " algorithm:\n"
                      << "  Board size: " << board.rows << "x" << board.columns << "\n"
                      << "  Mean execution time: " << result.meanDuration.count()
                      << " microseconds\n"
                      << "  Words found: " << result.foundWords.size() << "\n";
        }

        // Calculate and print the ratio of recursive to iterative execution times
        if (results.count("Recursive") > 0 && results.count("Iterative") > 0)
        {
            // Use static_cast to explicitly convert to double and avoid conversion warnings
            double recursiveTime = static_cast<double>(results["Recursive"].meanDuration.count());
            double iterativeTime = static_cast<double>(results["Iterative"].meanDuration.count());
            double ratio = recursiveTime / iterativeTime;

            std::cout << "\nPerformance comparison:\n"
                      << "  Recursive mean time: " << recursiveTime << " microseconds\n"
                      << "  Iterative mean time: " << iterativeTime << " microseconds\n"
                      << "  Ratio (Recursive/Iterative): " << std::fixed << std::setprecision(2)
                      << ratio << "\n";

            // Determine which algorithm is faster
            std::cout << "  " << (ratio > 1.0 ? "Iterative" : "Recursive") << " algorithm is "
                      << std::fixed << std::setprecision(2) << std::abs(ratio - 1.0) * 100.0
                      << "% faster\n";
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

// Benchmark test for Huge Board with Extended Word List
TEST_F(BoggleBenchmarkTest, HugeBoard_ExtendedList_Benchmark)
{
    runBenchmark("Huge Board (32x32)", createBoggleBoard<32, 32>(), "Extended Word List",
                 EXTENDED_WORD_LIST, 10);
}
