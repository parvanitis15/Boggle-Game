#include "Board.h"
#include "Trie.h"
#include "boggle_algorithm.h"
#include "create_boggle_board.h"
#include "word_list.h"

#include <chrono>
#include <gtest/gtest.h>
#include <string>

class BogglePerformanceTest : public ::testing::Test
{
protected:
    using Clock = std::chrono::high_resolution_clock;
    using Duration = std::chrono::microseconds;

    void measurePerformance(const std::string& boardName, const Board& board,
                            const std::string& listName, const auto& wordList)
    {
        Trie wordsTrie{wordList};

        auto start = Clock::now();
        auto foundWords = findValidWordsInBoard(wordsTrie, board);
        auto end = Clock::now();

        auto duration = std::chrono::duration_cast<Duration>(end - start);

        std::cout << "\nPerformance for " << boardName << " with " << listName << ":\n"
                  << "Board size: " << board.rows << "x" << board.columns << "\n"
                  << "Time: " << duration.count() << " microseconds\n"
                  << "Words found: " << foundWords.size() << "\n";

        EXPECT_LT(duration.count(), 1000000); // 1 second timeout
    }
};

TEST_F(BogglePerformanceTest, SmallBoardBasicList)
{
    measurePerformance("Small Board (4x4)", createBoggleBoard<4, 4>(), "Basic Word List",
                       WORD_LIST);
}

TEST_F(BogglePerformanceTest, SmallBoardExtendedList)
{
    measurePerformance("Small Board (4x4)", createBoggleBoard<4, 4>(), "Extended Word List",
                       EXTENDED_WORD_LIST);
}

TEST_F(BogglePerformanceTest, MediumBoardBasicList)
{
    measurePerformance("Medium Board (8x8)", createBoggleBoard<8, 8>(), "Basic Word List",
                       WORD_LIST);
}

TEST_F(BogglePerformanceTest, MediumBoardExtendedList)
{
    measurePerformance("Medium Board (8x8)", createBoggleBoard<8, 8>(), "Extended Word List",
                       EXTENDED_WORD_LIST);
}

TEST_F(BogglePerformanceTest, LargeBoardBasicList)
{
    measurePerformance("Large Board (16x16)", createBoggleBoard<16, 16>(), "Basic Word List",
                       WORD_LIST);
}

TEST_F(BogglePerformanceTest, LargeBoardExtendedList)
{
    measurePerformance("Large Board (16x16)", createBoggleBoard<16, 16>(), "Extended Word List",
                       EXTENDED_WORD_LIST);
}

TEST_F(BogglePerformanceTest, HugeBoardBasicList)
{
    measurePerformance("Huge Board (32x32)", createBoggleBoard<32, 32>(), "Basic Word List",
                       WORD_LIST);
}

TEST_F(BogglePerformanceTest, HugeBoardExtendedList)
{
    measurePerformance("Huge Board (32x32)", createBoggleBoard<32, 32>(), "Extended Word List",
                       EXTENDED_WORD_LIST);
}
