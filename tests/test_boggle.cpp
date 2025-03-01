#include "Board.h"
#include "Trie.h"
#include "boggle_algorithm.h"

#include <algorithm>
#include <chrono>
#include <gtest/gtest.h>
#include <unordered_set>

class BoggleTest : public ::testing::Test
{
protected:
    BoggleTest() : wordsList{}, expectedWords{}, board{} // Initialize all members in constructor
    {
    }

    // Test fixture setup
    [[maybe_unused]] void SetUp() override
    {
        wordsList = {"TAPS", "ONE",   "RAT",   "TONE",   "PATS", "RATE", "RATES", "SEAT", "SEA",
                     "SET",  "SETS",  "TEN",   "TENS",   "SEND", "SENT", "SEG",   "SEAM", "TEAM",
                     "TEAR", "TEARS", "STARE", "STARED", "STAR", "TAR",  "TORE",  "TEAS", "POEM",
                     "NOTE", "NOTES", "TONES", "PAT",    "SAP",  "SAPS", "DENS",  "DEN",  "TEND",
                     "ENDS", "NEAT",  "STEM",  "MIST",   "MATS", "PAST", "PANE"};

        expectedWords = {"DEN", "MATS", "NEAT", "ONE",   "PANE", "PAT", "RAT",  "RATE", "RATES",
                         "SEA", "SEAM", "SEAT", "SEG",   "SENT", "SET", "SETS", "STAR", "TAPS",
                         "TAR", "TEAM", "TEAR", "TEARS", "TEAS", "TEN", "TONE", "TONES"};

        // Initialize the board
        board.rows = 4;
        board.columns = 4;
        board.table
            = {'T', 'A', 'P', 'S', 'O', 'N', 'E', 'D', 'R', 'A', 'T', 'I', 'M', 'S', 'E', 'G'};
    }

    // Helper function to verify found words against expected words
    void verifyFoundWords(const std::vector<std::string>& foundWords,
                          const std::string& algorithmName)
    {
        // Convert to sets to ignore duplicates in comparison
        std::unordered_set<std::string> foundSet;
        for (const auto& word : foundWords)
        {
            foundSet.insert(std::string(word));
        }

        std::unordered_set<std::string> expectedSet;
        for (const auto& word : expectedWords)
        {
            expectedSet.insert(std::string(word));
        }

        EXPECT_EQ(foundSet.size(), expectedSet.size())
            << algorithmName << " algorithm found " << foundSet.size() << " words, expected "
            << expectedSet.size();

        for (const auto& word : expectedSet)
        {
            EXPECT_TRUE(foundSet.contains(word))
                << algorithmName << " algorithm missing expected word: " << word;
        }
    }

    std::vector<std::string_view> wordsList;
    std::vector<std::string_view> expectedWords;
    Board board;
};

TEST_F(BoggleTest, RecursiveAlgorithmCorrectWordsFinding)
{
    Trie wordsTrie{wordsList};
    auto foundWords = findValidWordsInBoardRecursive(wordsTrie, board);
    verifyFoundWords(foundWords, "Recursive");
}

TEST_F(BoggleTest, IterativeAlgorithmCorrectWordsFinding)
{
    Trie wordsTrie{wordsList};
    auto foundWords = findValidWordsInBoardIterative(wordsTrie, board);
    verifyFoundWords(foundWords, "Iterative");
}

TEST_F(BoggleTest, AlgorithmsProduceSameResults)
{
    Trie wordsTrie{wordsList};

    // Get results from both algorithms
    auto recursiveWords = findValidWordsInBoardRecursive(wordsTrie, board);
    auto iterativeWords = findValidWordsInBoardIterative(wordsTrie, board);

    // Sort both results for comparison
    std::sort(recursiveWords.begin(), recursiveWords.end());
    std::sort(iterativeWords.begin(), iterativeWords.end());

    // Check that both algorithms found the same number of words
    EXPECT_EQ(recursiveWords.size(), iterativeWords.size())
        << "Recursive and iterative algorithms found different number of words";

    // Check that both algorithms found the same words
    EXPECT_TRUE(recursiveWords == iterativeWords)
        << "Recursive and iterative algorithms found different words";

    // If the vectors are different, print the differences for debugging
    if (recursiveWords != iterativeWords)
    {
        std::cout << "Words found only by recursive algorithm:" << std::endl;
        for (const auto& word : recursiveWords)
        {
            if (std::find(iterativeWords.begin(), iterativeWords.end(), word)
                == iterativeWords.end())
            {
                std::cout << "  " << word << std::endl;
            }
        }

        std::cout << "Words found only by iterative algorithm:" << std::endl;
        for (const auto& word : iterativeWords)
        {
            if (std::find(recursiveWords.begin(), recursiveWords.end(), word)
                == recursiveWords.end())
            {
                std::cout << "  " << word << std::endl;
            }
        }
    }
}

TEST_F(BoggleTest, PerformanceMeasurement)
{
    Trie wordsTrie{wordsList};

    auto start = std::chrono::high_resolution_clock::now();
    auto foundWords = findValidWordsInBoardRecursive(wordsTrie, board);
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;
    std::cout << "Found " << foundWords.size() << " words" << std::endl;

    // You might want to set a reasonable threshold based on your requirements
    EXPECT_LT(duration.count(), 1000000); // Expect less than 1 second
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
