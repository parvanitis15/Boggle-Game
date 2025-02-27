#include <gtest/gtest.h>
#include <chrono>
#include "boggle_algorithm.h"
#include "Trie.h"
#include "Board.h"

class BoggleTest : public ::testing::Test {
protected:
    // Test fixture setup
    void SetUp() override {
        wordsList = {
            "TAPS", "ONE", "RAT", "TONE", "PATS", "RATE", "RATES", "SEAT", "SEA", 
            "SET", "SETS", "TEN", "TENS", "SEND", "SENT", "SEG", "SEAM", "TEAM",
            "TEAR", "TEARS", "STARE", "STARED", "STAR", "TAR", "TORE", "TEAS",
            "POEM", "NOTE", "NOTES", "TONES", "PAT", "SAP", "SAPS", "DENS", "DEN",
            "TEND", "ENDS", "NEAT", "STEM", "MIST", "MATS", "PAST", "PANE"
        };

        expectedWords = {
            "DEN", "MATS", "NEAT", "ONE", "PANE", "PAT",
            "RAT", "RATE", "RATES", "SEA", "SEAM", "SEAT",
            "SEG", "SENT", "SET", "SETS", "STAR", "TAPS", "TAR",
            "TEAM", "TEAR", "TEARS", "TEAS", "TEN", "TONE", "TONES"
        };

        // Initialize the board
        board.rows = 4;
        board.columns = 4;
        board.table = {
            'T', 'A', 'P', 'S',
            'O', 'N', 'E', 'D',
            'R', 'A', 'T', 'I',
            'M', 'S', 'E', 'G'
        };
    }

    std::vector<std::string_view> wordsList;
    std::vector<std::string_view> expectedWords;
    Board board;
};

TEST_F(BoggleTest, CorrectWordsFinding) {
    Trie wordsTrie{wordsList};
    auto foundWords = findValidWordsInBoard(wordsTrie, board);
    
    // Sort both vectors for comparison
    std::sort(foundWords.begin(), foundWords.end());
    auto expectedWordsCopy = expectedWords;
    std::sort(expectedWordsCopy.begin(), expectedWordsCopy.end());

    EXPECT_EQ(foundWords.size(), expectedWordsCopy.size());
    EXPECT_EQ(foundWords, expectedWordsCopy);
}

TEST_F(BoggleTest, PerformanceMeasurement) {
    Trie wordsTrie{wordsList};
    
    auto start = std::chrono::high_resolution_clock::now();
    auto foundWords = findValidWordsInBoard(wordsTrie, board);
    auto end = std::chrono::high_resolution_clock::now();
    
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;
    // You might want to set a reasonable threshold based on your requirements
    EXPECT_LT(duration.count(), 1000000); // Expect less than 1 second
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
} 
