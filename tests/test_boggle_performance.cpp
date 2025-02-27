#include <gtest/gtest.h>
#include <chrono>
#include <string>
#include "boggle_algorithm.h"
#include "Trie.h"
#include "Board.h"
#include "boggle_boards.h"
#include "word_list.h"

class BogglePerformanceTest : public ::testing::Test {
protected:
    using Clock = std::chrono::high_resolution_clock;
    using Duration = std::chrono::microseconds;

    void measurePerformance(const std::string& boardName, const Board& board, 
                          const std::string& listName, const auto& wordList) {
        Trie wordsTrie{wordList};
        
        auto start = Clock::now();
        auto foundWords = findValidWordsInBoard(wordsTrie, board);
        auto end = Clock::now();
        
        auto duration = std::chrono::duration_cast<Duration>(end - start);
        
        std::cout << "\nPerformance for " << boardName << " with " << listName << ":\n"
                  << "Time: " << duration.count() << " microseconds\n"
                  << "Words found: " << foundWords.size() << "\n";
        
        // Optional: Set a reasonable timeout (e.g., 1 second)
        EXPECT_LT(duration.count(), 1000000);
    }
};

TEST_F(BogglePerformanceTest, SmallBoardBasicList) {
    measurePerformance("Small Board (3x3)", createSmallBoard(), 
                      "Basic Word List", WORD_LIST);
}

TEST_F(BogglePerformanceTest, SmallBoardExtendedList) {
    measurePerformance("Small Board (3x3)", createSmallBoard(), 
                      "Extended Word List", EXTENDED_WORD_LIST);
}

TEST_F(BogglePerformanceTest, MediumBoardBasicList) {
    measurePerformance("Medium Board (4x4)", createMediumBoard(), 
                      "Basic Word List", WORD_LIST);
}

TEST_F(BogglePerformanceTest, MediumBoardExtendedList) {
    measurePerformance("Medium Board (4x4)", createMediumBoard(), 
                      "Extended Word List", EXTENDED_WORD_LIST);
}

TEST_F(BogglePerformanceTest, LargeBoardBasicList) {
    measurePerformance("Large Board (5x5)", createLargeBoard(), 
                      "Basic Word List", WORD_LIST);
}

TEST_F(BogglePerformanceTest, LargeBoardExtendedList) {
    measurePerformance("Large Board (5x5)", createLargeBoard(), 
                      "Extended Word List", EXTENDED_WORD_LIST);
}

TEST_F(BogglePerformanceTest, HugeBoardBasicList) {
    measurePerformance("Huge Board (6x6)", createHugeBoard(), 
                      "Basic Word List", WORD_LIST);
}

TEST_F(BogglePerformanceTest, HugeBoardExtendedList) {
    measurePerformance("Huge Board (6x6)", createHugeBoard(), 
                      "Extended Word List", EXTENDED_WORD_LIST);
} 
