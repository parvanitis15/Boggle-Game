#ifndef NODE_H
#define NODE_H

#include <vector>
#include <string>
#include <string_view>

// A Node contains
//  1) key: a sequence of characters
//  2) validWord: a bool indicating whether it's a valid word
//  3) children: a vector of pointers to children nodes
class Node
{
private:
    std::string m_key{};
    bool m_validWord{false};
    std::vector<Node *> m_children{};

public:
    // Default "empty-root" constructor
    Node() = default;

    // Constructor from another (parent) Node + letter
    Node(const Node parent, const char letter);

    // Copy constructor
    Node(const Node &other);

    // Move constructor
    Node(Node &&other) noexcept;

    // Copy assignment operator
    Node &operator=(const Node &other);

    // Move assignment operator
    Node &operator=(Node &&other) noexcept;

    // Destructor to clean up resources (children)
    ~Node();

    std::string getKey() const;
    void setValidWord();
    bool isValidWord() const;
    Node *getChildAtIndex(size_t index) const;

    // Function to search for key in children
    // If found, returns child index
    // If not found, returns -1
    int getIndexOfChildWithKey(const std::string_view key) const;

    // Function to add new child node and return it
    // Use move semantics for better performance
    Node *addChildNode(Node &&childNode);

    // Overload to add child node via copy
    Node *addChildNode(const Node &childNode);
};

#endif // NODE_H
