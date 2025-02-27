#ifndef TRIE_H
#define TRIE_H

#include <vector>
#include <string_view>
#include "Node.h"

enum inTrie {
    doesntExist,
    existsButNotWord,
    isWord
};


// Search tree data structure used to store and retrieve strings from a dictionary or set
// Unlike a binary search tree, nodes in a trie do not store their associated key. Instead, 
// each node's position within the trie determines its associated key, with the connections
// between nodes defined by individual characters rather than the entire key.
// source: https://en.wikipedia.org/wiki/Trie#:~:text=In%20computer%20science%2C%20a%20trie,from%20a%20dictionary%20or%20set.
class Trie
{
private:
    Node m_root{};

public:
    // Constructor from array of strings
    // The trie is constructed as following:
    // 1. Initialize empty root node
    // 2. Iterate over each word:
    //  i)      Initiate current node to root node
    //  ii)     Initiate current word to ''
    //  iii)    Iterate over letters:
    //              - Add letter to current word
    //              - Check if the key of the current word belongs to any of the current node's children
    //                  - Yes:  traverse to the child node with the key in question
    //                  - No:   create the child node with the key in question and traverse to it
    //  iv)      Is the word complete?
    //              - Yes:  set node as valid word
    //              - No:   nothing (continue to next letter)
    Trie(const std::vector<std::string_view> &words);

    // Function to add a single word to the trie
    void addWord(std::string_view word);

    // Function to check whether trie contains a certain string and that is a valid word
    // 1. Initialize current node to root node
    // 2. Initialize word prefix as empty string
    // 3. Iterate over letters of word:
    //      i) Add letter to word prefix
    //      ii) Check if the word prefix matches any children node's keys
    //          - No:   Return doesntExist
    //          - Yes:  Make that child the current node
    // 4. Return whether the current node contains a valid word (isWord) or not (existsButNotWord)
    inTrie contains(const std::string_view& word) const;
};

#endif // TRIE_H
