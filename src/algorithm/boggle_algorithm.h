#ifndef BOGGLE_ALGORITHM_H
#define BOGGLE_ALGORITHM_H

#include "Board.h"
#include "Trie.h"
#include "VisitMap.h"

#include <stack>
#include <string>
#include <vector>

enum ContinueTraversing
{
    yes,
    no
};

// Function to check whether a board index letter, appended to current word, exists (and is a word)
// in the words Trie It also checks whether it has been visited before
ContinueTraversing checkBoardIndex(const Trie& wordsTrie, const Board& board,
                                   const VisitMap& visitMap, const std::string& currentWord, int r,
                                   int c, std::vector<std::string>& wordsFound);

// Recursion function to traverse adjacent index in board
// while the Trie contains the current word
// Important: currentWord is a new copy, because we take a path which we do not want to be alter the
// original word (which also takes other paths) Same with visitMap
void traverseBoardRecursively(const Trie& wordsTrie, const Board& board, const VisitMap& visitMap,
                              const std::string& currentWord, int rStart, int cStart,
                              std::vector<std::string>& wordsFound);

// Helper function to check a position and push new state onto stacks if valid
void pushNewStateIfValid(const Trie& wordsTrie, const Board& board, const std::string& currentWord,
                         int r, int c, const VisitMap& visitMap,
                         std::vector<std::string>& wordsFound, std::stack<int>& rStack,
                         std::stack<int>& cStack, std::stack<std::string>& currentWordStack,
                         std::stack<VisitMap>& visitMapStack,
                         std::stack<size_t>& directionStepsIndexStack);

// Main function to find valid words in board using recursion
std::vector<std::string> findValidWordsInBoardRecursive(const Trie& wordsTrie, const Board& board);

// Main function to find valid words in board using iteration
// Use LIFO queues (stacks) for r, c, directionSteps, currentWord, visitMap
std::vector<std::string> findValidWordsInBoardIterative(const Trie& wordsTrie, const Board& board);

#endif // BOGGLE_ALGORITHM_H
