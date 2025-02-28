#ifndef BOGGLE_ALGORITHM_H
#define BOGGLE_ALGORITHM_H

#include "Board.h"
#include "Trie.h"
#include "VisitMap.h"

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
void traverseBoardRecursively(const Trie& wordsTrie, const Board& board, VisitMap visitMap,
                              const std::string& currentWord, int rStart, int cStart,
                              std::vector<std::string>& wordsFound);

// Main function to find valid words in board (Boggle function)
std::vector<std::string> findValidWordsInBoard(const Trie& wordsTrie, const Board& board);

#endif // BOGGLE_ALGORITHM_H
