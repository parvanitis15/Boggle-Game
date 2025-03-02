#include "boggle_algorithm.h"

#include "Board.h"
#include "Trie.h"
#include "VisitMap.h"

#include <cassert>
#include <stack>
#include <string>
#include <vector>

// struct ValidWords
// {
//     Trie words;

//     // int isValidWord(const std::string& word)
//     // {
//     //     // TODO: return 0 if it's a completed word, 1 if it's completed word and leaf, -1 if
//     it's not valid
//     // }
// };

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

void traverseBoardRecursively(const Trie& wordsTrie, const Board& board, const VisitMap& visitMap,
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
                auto newVisitMap = visitMap;
                newVisitMap.markVisited(
                    static_cast<size_t>(r),
                    static_cast<size_t>(
                        c)); // static_cast<size_t> is safe as long as the int is not negative and
                             // we've checked for that in bounds checking

                // Add the letter to the actual word for continuing traversal
                auto newCurrentWord{
                    currentWord + board.getLetter(static_cast<size_t>(r), static_cast<size_t>(c))};

                traverseBoardRecursively(wordsTrie, board, newVisitMap, newCurrentWord, r, c,
                                         wordsFound);
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
            // Store indices that have been already traversed in board
            // Use a VisitMap
            VisitMap visitMap(board.rows, board.columns);

            std::string currentWord{}; // Store current word (letters for each traversal)

            // Check first index here
            // This is important because we want the starting index to be exactly the one from this
            // double-loop and not in the inner traversal loop
            if (checkBoardIndex(wordsTrie, board, visitMap, currentWord, r, c, wordsFound)
                == ContinueTraversing::yes)
            {
                // Mark index as visited
                visitMap.markVisited(
                    static_cast<size_t>(r),
                    static_cast<size_t>(
                        c)); // static_cast<size_t> is safe as long as the int is not negative and
                             // we've checked for that in bounds checking

                // Add the letter to the actual word for continuing traversal
                currentWord += board.getLetter(static_cast<size_t>(r), static_cast<size_t>(c));

                traverseBoardRecursively(wordsTrie, board, visitMap, currentWord, r, c, wordsFound);
            }
        }
    }

    return wordsFound;
}

// Helper function to check a position and push new state onto stacks if valid
void pushNewStateIfValid(const Trie& wordsTrie, const Board& board, const std::string& currentWord,
                         int r, int c, const VisitMap& visitMap,
                         std::vector<std::string>& wordsFound, std::stack<int>& rStack,
                         std::stack<int>& cStack, std::stack<std::string>& currentWordStack,
                         std::stack<VisitMap>& visitMapStack,
                         std::stack<size_t>& directionStepsIndexStack)
{

    if (checkBoardIndex(wordsTrie, board, visitMap, currentWord, r, c, wordsFound)
        == ContinueTraversing::yes)
    {
        // Mark index as visited
        auto newVisitMap{visitMap};
        newVisitMap.markVisited(static_cast<size_t>(r), static_cast<size_t>(c));

        // Add the letter to the actual word for continuing traversal
        auto newCurrentWord{currentWord
                            + board.getLetter(static_cast<size_t>(r), static_cast<size_t>(c))};

        // Push to stack
        rStack.emplace(r);
        cStack.emplace(c);
        currentWordStack.emplace(newCurrentWord);
        visitMapStack.emplace(newVisitMap);
        directionStepsIndexStack.emplace(0);
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
            // Skip invalid starting positions
            VisitMap initialVisitMap(board.rows, board.columns);
            std::string emptyWord{};
            if (checkBoardIndex(wordsTrie, board, initialVisitMap, emptyWord, rInit, cInit,
                                wordsFound)
                != ContinueTraversing::yes)
            {
                continue;
            }

            // Mark initial position as visited
            initialVisitMap.markVisited(static_cast<size_t>(rInit), static_cast<size_t>(cInit));

            // Initial letter for the current word
            std::string initialLetter(
                1, board.getLetter(static_cast<size_t>(rInit), static_cast<size_t>(cInit)));

            // Initialize stacks for DFS traversal
            std::stack<int> rStack;
            std::stack<int> cStack;
            std::stack<size_t> directionStepsIndexStack;
            std::stack<std::string> currentWordStack;
            std::stack<VisitMap> visitMapStack;

            // Push initial state
            rStack.push(rInit);
            cStack.push(cInit);
            directionStepsIndexStack.push(0);
            currentWordStack.push(initialLetter);
            visitMapStack.push(initialVisitMap);

            // Current state variables (avoid repeated stack access)
            int r = rInit;
            int c = cInit;
            std::string currentWord = initialLetter;
            VisitMap visitMap = initialVisitMap;
            bool stateChanged = false;

            // DFS traversal
            while (!rStack.empty())
            {
                // Validate stack consistency
                assert(rStack.size() == cStack.size()
                       && rStack.size() == directionStepsIndexStack.size()
                       && rStack.size() == currentWordStack.size()
                       && rStack.size() == visitMapStack.size());

                // Update current state if needed
                if (stateChanged)
                {
                    r = rStack.top();
                    c = cStack.top();
                    currentWord = currentWordStack.top();
                    visitMap = visitMapStack.top();
                    stateChanged = false;
                }

                // If all directions from current cell are explored, backtrack
                if (directionStepsIndexStack.top() >= nDirections)
                {
                    rStack.pop();
                    cStack.pop();
                    directionStepsIndexStack.pop();
                    currentWordStack.pop();
                    visitMapStack.pop();
                    stateChanged = true;
                    continue;
                }

                // Get next direction to explore
                size_t dirIndex = directionStepsIndexStack.top()++;
                int newR = r + directionSteps[dirIndex][0];
                int newC = c + directionSteps[dirIndex][1];

                // Try to move in the current direction
                size_t stackSizeBefore = rStack.size();
                pushNewStateIfValid(wordsTrie, board, currentWord, newR, newC, visitMap, wordsFound,
                                    rStack, cStack, currentWordStack, visitMapStack,
                                    directionStepsIndexStack);

                // Check if a new state was pushed
                stateChanged = (stackSizeBefore != rStack.size());
            }
        }
    }

    return wordsFound;
}
