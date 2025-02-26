#ifndef TRIE_H
#define TRIE_H

#include <vector>
#include <string_view>
#include "Node.h"

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
    //                  - Yes: traverse to the child node with the key in question
    //                  - No: create the child node with the key in question and traverse to it
    // iv)      Is the word complete?
    //              - Yes: set node as valid word
    //              - No: nothing (continue to next letter)
    Trie(const std::vector<std::string_view> &words);

    // Method to add a single word to the trie
    void addWord(std::string_view word);

    bool containsWord(const std::string_view& word) const;
};

#endif // TRIE_H
