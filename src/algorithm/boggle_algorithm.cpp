#include "boggle_algorithm.h"

#include "Board.h"
#include "Trie.h"
#include "VisitMap.h"

#include <cassert>
#include <stack>
#include <string>
#include <vector>

ContinueTraversing checkBoardIndex(const Trie& wordsTrie, const Board& board,
                                   const VisitMap& visitMap, const std::string& currentWord, int r,
                                   int c, std::vector<std::string>& wordsFound)
{
    // Check bounds
    if ((r < 0) || (r >= static_cast<int>(board.rows)) || (c < 0)
        || (c >= static_cast<int>(board.columns)))
    {
        return ContinueTraversing::no;
    }

    // Skip index if visited
    if (visitMap.isVisited(static_cast<size_t>(r), static_cast<size_t>(c)))
    {
        return ContinueTraversing::no;
    }

    // Get current word + new letter from board index
    auto currentWordPlusNewLetter{
        currentWord + board.getLetter(static_cast<size_t>(r), static_cast<size_t>(c))};

    // Check whether word is in Trie and whether it's a valid word
    auto wordInTrie = wordsTrie.contains(currentWordPlusNewLetter);

    // If it doesn't exist, begin new traversal
    if (wordInTrie == inTrie::doesntExist)
    {
        return ContinueTraversing::no;
    }

    // If it's a word, append to findValidWords
    if (wordInTrie == inTrie::isWord)
    {
        wordsFound.emplace_back(currentWordPlusNewLetter);
    }

    return ContinueTraversing::yes;
}

void traverseBoardRecursively(const Trie& wordsTrie, const Board& board, VisitMap& visitMap,
                              const std::string& currentWord, int rStart, int cStart,
                              std::vector<std::string>& wordsFound)
{
    for (int r{rStart - 1}; r <= rStart + 1; r++)
    {
        for (int c{cStart - 1}; c <= cStart + 1; c++)
        {
            if (checkBoardIndex(wordsTrie, board, visitMap, currentWord, r, c, wordsFound)
                == ContinueTraversing::yes)
            {
                // Mark index as visited
                visitMap.markVisited(static_cast<size_t>(r), static_cast<size_t>(c));

                // Add the letter to the actual word for continuing traversal
                auto newCurrentWord{
                    currentWord + board.getLetter(static_cast<size_t>(r), static_cast<size_t>(c))};

                // Recursive call with the same VisitMap
                traverseBoardRecursively(wordsTrie, board, visitMap, newCurrentWord, r, c,
                                         wordsFound);

                // Unmark the cell after returning from recursion
                visitMap.unmarkVisited(static_cast<size_t>(r), static_cast<size_t>(c));
            }
        }
    }
}

std::vector<std::string> findValidWordsInBoardRecursive(const Trie& wordsTrie, const Board& board)
{
    std::vector<std::string> wordsFound{};

    // Important: we're looping over the major dimension first for better memory caching of our
    // row-major structs
    for (int r{0}; r < static_cast<int>(board.rows); r++)
    {
        for (int c{0}; c < static_cast<int>(board.columns); c++)
        {
            // Create a single VisitMap for this starting position
            VisitMap visitMap(board.rows, board.columns);

            std::string currentWord{}; // Store current word (letters for each traversal)

            // Check first index here
            // This is important because we want the starting index to be exactly the one from this
            // double-loop and not in the inner traversal loop
            if (checkBoardIndex(wordsTrie, board, visitMap, currentWord, r, c, wordsFound)
                == ContinueTraversing::yes)
            {
                // Mark index as visited
                visitMap.markVisited(static_cast<size_t>(r), static_cast<size_t>(c));

                // Add the letter to the actual word for continuing traversal
                currentWord += board.getLetter(static_cast<size_t>(r), static_cast<size_t>(c));

                // Recursive call with the same VisitMap
                traverseBoardRecursively(wordsTrie, board, visitMap, currentWord, r, c, wordsFound);

                // No need to unmark here as we're done with this starting position
            }
        }
    }

    return wordsFound;
}

// Helper function to check a position and push new state onto stack if valid
void pushNewStateIfValid(const Trie& wordsTrie, const Board& board, const std::string& currentWord,
                         int r, int c, VisitMap& visitMap, std::vector<std::string>& wordsFound,
                         std::stack<SearchState>& stateStack)
{
    if (checkBoardIndex(wordsTrie, board, visitMap, currentWord, r, c, wordsFound)
        == ContinueTraversing::yes)
    {
        // Mark index as visited
        visitMap.markVisited(static_cast<size_t>(r), static_cast<size_t>(c));

        // Add the letter to the actual word for continuing traversal
        auto newCurrentWord{currentWord
                            + board.getLetter(static_cast<size_t>(r), static_cast<size_t>(c))};

        // Push new state to stack
        stateStack.push({r, c, 0, newCurrentWord});
    }
}

std::vector<std::string> findValidWordsInBoardIterative(const Trie& wordsTrie, const Board& board)
{
    std::vector<std::string> wordsFound{};

    // Define the 8 possible directions to traverse from any cell
    constexpr size_t nDirections = 8;
    constexpr std::array<std::array<int, 2>, nDirections> directionSteps = {
        {{-1, -1},
         {-1, 0},
         {-1, 1}, // Above cells
         {0, -1},
         {0, 1}, // Adjacent cells
         {1, -1},
         {1, 0},
         {1, 1}} // Below cells
    };

    // Iterate through each cell in the board as a starting position
    // Important: we're looping over the major dimension first for better memory caching of our
    // row-major structs
    for (int rInit{0}; rInit < static_cast<int>(board.rows); rInit++)
    {
        for (int cInit{0}; cInit < static_cast<int>(board.columns); cInit++)
        {
            // Create a single VisitMap for this starting position
            VisitMap visitMap(board.rows, board.columns);

            // Skip invalid starting positions
            std::string emptyWord{};
            if (checkBoardIndex(wordsTrie, board, visitMap, emptyWord, rInit, cInit, wordsFound)
                != ContinueTraversing::yes)
            {
                continue;
            }

            // Mark initial position as visited
            visitMap.markVisited(static_cast<size_t>(rInit), static_cast<size_t>(cInit));

            // Initial letter for the current word
            std::string initialLetter(
                1, board.getLetter(static_cast<size_t>(rInit), static_cast<size_t>(cInit)));

            // Initialize a single stack for DFS traversal
            std::stack<SearchState> stateStack;

            // Push initial state
            stateStack.push({rInit, cInit, 0, initialLetter});

            // DFS traversal
            while (!stateStack.empty())
            {
                // Get current state - use reference to avoid copying
                SearchState& currentState = stateStack.top();

                // If all directions from current cell are explored, backtrack
                if (currentState.directionIndex >= nDirections)
                {
                    // Unmark the current cell before popping
                    visitMap.unmarkVisited(static_cast<size_t>(currentState.r),
                                           static_cast<size_t>(currentState.c));

                    stateStack.pop();
                    continue;
                }

                // Get next direction to explore
                size_t dirIndex = currentState.directionIndex++;
                int newR = currentState.r + directionSteps[dirIndex][0];
                int newC = currentState.c + directionSteps[dirIndex][1];

                // Try to move in the current direction
                pushNewStateIfValid(wordsTrie, board, currentState.currentWord, newR, newC,
                                    visitMap, wordsFound, stateStack);
            }
        }
    }

    return wordsFound;
}
