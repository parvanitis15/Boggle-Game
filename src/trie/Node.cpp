#include "Node.h"

// Constructor from another (parent) Node + letter
Node::Node(const Node& parent, const char letter) : m_key(parent.getKey() + letter)
{
}

// Copy constructor
Node::Node(const Node &other) : m_key(other.m_key), m_validWord(other.m_validWord)
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
Node::Node(Node &&other) noexcept
    : m_key(std::move(other.m_key)),
      m_validWord(other.m_validWord),
      m_children(std::move(other.m_children))
{
    other.m_children.clear(); // Prevent double-deletion
}

// Copy assignment operator
Node &Node::operator=(const Node &other)
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
Node &Node::operator=(Node &&other) noexcept
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
Node::~Node()
{
    for (Node *child : m_children)
    {
        delete child;
    }
}

std::string Node::getKey() const
{
    return m_key;
}

void Node::setValidWord()
{
    m_validWord = true;
}

bool Node::isValidWord() const
{
    return m_validWord;
}

Node *Node::getChildAtIndex(size_t index) const
{
    return m_children[index]; // use operator[] (instead of .at()) for better performance
}

int Node::getIndexOfChildWithKey(const std::string_view key) const
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

Node *Node::addChildNode(Node &&childNode)
{
    // Create a new node on the heap, moving resources
    Node *newNode = new Node(std::move(childNode));
    m_children.push_back(newNode);
    return newNode;
}

Node *Node::addChildNode(const Node &childNode)
{
    Node *newNode = new Node(childNode);
    m_children.push_back(newNode);
    return newNode;
}
