#include <iostream>
#include <vector>


struct Board 
{
    std::vector<char> table;
    size_t rows;
    size_t columns;

    char get_letter(size_t row, size_t col)
    {
        // Don't use vector.at() for efficiency
        return table[row*columns + col]; // row-major
    }
};

// A node contains
//  1) key: a sequence of characters
//  2) validWord: a bool indicating whether it's a valid word
//  3) children: a vector of pointers to children nodes
class Node
{
    private:
        std::string key{};
        bool validWord{false};
        std::vector<Node*> children{};

    public:
        // Constructor from another Node + char
        Node(Node parent, char letter) 
        {
            this->key = parent.getKey() + letter;
        } 

        std::string getKey() const 
        {
            return this->key;
        }

        void setValidWord() 
        {
            this->validWord = true;
        }
};

// Search tree data structure used to store and retrieve strings from a dictionary or set
// Unlike a binary search tree, nodes in a trie do not store their associated key. Instead, 
// each node's position within the trie determines its associated key, with the connections
// between nodes defined by individual characters rather than the entire key.
// source: https://en.wikipedia.org/wiki/Trie#:~:text=In%20computer%20science%2C%20a%20trie,from%20a%20dictionary%20or%20set.
struct trie
{
    Node* root{};
    // The trie would be constructed as following using a number of words:
    // 1. Initialize empty root node
    // 2. Iterate over each word:
    //  i)      Initiate current node to root node
    //  ii)     Initiate current word to ''
    //  iii)    Iterate over letters:
    //              - Add letter to current word
    //              - Check if the key of the active word belongs to any of the current node's children
    //                  - Yes: traverse to the child node with the key in question
    //                  - No: create the child node with the key in question and traverse to it
    // iv)      Is the word complete?
    //              - Yes: set node as valid word
    //              - No: nothing (continue to next letter)
};


struct ValidWords 
{
    trie words;

    int isValidWord(const std::string& word) 
    {
        // TODO: return 0 if it's a completed word, 1 if it's completed word and leaf, -1 if it's not valid
    }
};


std::vector<std::string> findValidWordsInBoard(const ValidWords& validWords, const Board& board)
{
    for (auto r{0}; r < board.rows; r++)
    {
        // store indices in board that been already traversed
        // std::vector<

        for (auto c{0}; c < board.columns; c++)
        {
            // TODO: check if letter is valid

            // traverse in every direction
        }
    }
}


int main() 
{
    


    return 0;
}
