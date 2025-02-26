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

// A Node contains
//  1) key: a sequence of characters
//  2) validWord: a bool indicating whether it's a valid word
//  3) children: a vector of pointers to children nodes
class Node
{
    private:
        std::string m_key{};
        bool m_validWord{false};
        std::vector<Node*> m_children{};

    public:
        // Default "empty-root" constructor
        Node() = default;

        // Constructor from another (parent) Node + letter
        Node(const Node parent, const char letter) 
            : m_key(parent.getKey() + letter) {}

        // Copy constructor
        Node(const Node &other)
            : m_key(other.m_key), m_validWord(other.m_validWord)
        {
            // Deep copy children
            for (const auto *child : other.m_children)
            {
                if (child)
                {
                    m_children.push_back(new Node(*child));
                }
            }
        }

        // Move constructor
        Node(Node &&other) noexcept
            : m_key(std::move(other.m_key)),
              m_validWord(other.m_validWord),
              m_children(std::move(other.m_children))
        {
            other.m_children.clear(); // Prevent double-deletion
        }

        // Copy assignment operator
        Node &operator=(const Node &other)
        {
            if (this != &other)
            {
                // Clean up existing resources
                for (auto *child : m_children)
                {
                    delete child;
                }

                m_key = other.m_key;
                m_validWord = other.m_validWord;
                m_children.clear();

                // Deep copy children
                for (const auto *child : other.m_children)
                {
                    if (child)
                    {
                        m_children.push_back(new Node(*child));
                    }
                }
            }
            return *this;
        }

        // Move assignment operator
        Node &operator=(Node &&other) noexcept
        {
            if (this != &other)
            {
                // Clean up existing resources
                for (auto *child : m_children)
                {
                    delete child;
                }

                m_key = std::move(other.m_key);
                m_validWord = other.m_validWord;
                m_children = std::move(other.m_children);

                other.m_children.clear(); // Prevent double-deletion
            }
            return *this;
        }

        // Destructor to clean up resources (children)
        ~Node()
        {
            for (Node *child : m_children)
            {
                delete child;
            }
        }

        std::string getKey() const
        {
            return m_key;
        }

        void setValidWord()
        {
            m_validWord = true;
        }

        bool isValidWord() const {
            return m_validWord;
        }

        Node* getChildAtIndex(size_t index)
        {
            return m_children[index]; // use operator[] (instead of .at()) for better performance
        }

        // Function to search for key in children
        // If found, returns child index
        // If not found, returns -1
        int getIndexOfChildWithKey(const std::string_view key) const
        {
            for (size_t i{0}; i < m_children.size(); i++)
            {
                if (m_children[i] && m_children[i]->m_key == key)
                {
                    return static_cast<int>(i);
                }
            }
            return -1;
        }

        // Function to add new child node and return it
        // Use move semantics for better performance
        Node* addChildNode(Node&& childNode)
        {
            // Create a new node on the heap, moving resources
            Node *newNode = new Node(std::move(childNode));
            m_children.push_back(newNode);
            return newNode;
        }

        // Overload to add child node via copy
        Node* addChildNode(const Node &childNode)
        {
            Node *newNode = new Node(childNode);
            m_children.push_back(newNode);
            return newNode;
        }
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
    // The trie would be constructed as following using a number of words:
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
    public:
        // Constructor from array of strings
        Trie(const std::vector<std::string_view> &words)
        {
            for (const auto &word : words)
            {
                addWord(word);
            }
        }

        // Method to add a single word to the trie
        void addWord(std::string_view word)
        {
            Node *current_node_ptr = &m_root;
            std::string current_prefix;

            for (const auto &letter : word)
            {
                current_prefix += letter;

                // Check if this prefix exists in the children
                int childIndex = current_node_ptr->getIndexOfChildWithKey(current_prefix);

                if (childIndex < 0) // could be == -1 but wanted to guard against possible conversion of negative int to size_t anyway
                {
                    // Create new node with just the new letter (not the whole prefix)
                    Node newNode(*current_node_ptr, letter);
                    current_node_ptr = current_node_ptr->addChildNode(std::move(newNode));
                }
                else
                {
                    current_node_ptr = current_node_ptr->getChildAtIndex(static_cast<size_t>(childIndex));
                }
            }

            // Mark the final node as a valid word
            current_node_ptr->setValidWord();
        }
};

struct ValidWords 
{
    Trie words;

    // int isValidWord(const std::string& word) 
    // {
    //     // TODO: return 0 if it's a completed word, 1 if it's completed word and leaf, -1 if it's not valid
    // }
};


// std::vector<std::string> findValidWordsInBoard(const ValidWords& validWords, const Board& board)
// {
//     for (auto r{0}; r < board.rows; r++)
//     {
//         // store indices in board that been already traversed
//         // std::vector<

//         for (auto c{0}; c < board.columns; c++)
//         {
//             // TODO: check if letter is valid

//             // traverse in every direction
//         }
//     }
// }


int main() 
{
    // Test case 1: few valid words, small board
    std::vector<std::string_view> wordsList{"gragas", "vladimir", "lucifer", "ashe", "ashes", "dust"};

    Trie trieOfWords{wordsList};

    return 0;
}
