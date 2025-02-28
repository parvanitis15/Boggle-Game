#include "Trie.h"

#include <string>

Trie::Trie(const std::vector<std::string_view> &words)
{
    for (const auto &word : words)
    {
        addWord(word);
    }
}

void Trie::addWord(std::string_view word)
{
    Node *current_node_ptr = &m_root;
    std::string current_prefix;

    for (const auto &letter : word)
    {
        current_prefix += letter;

        // Check if this prefix exists in the children
        int childIndex = current_node_ptr->getIndexOfChildWithKey(current_prefix);

        if (childIndex < 0) // could be == -1 but wanted to guard against possible conversion of
                            // negative int to size_t anyway
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

inTrie Trie::contains(const std::string_view &word) const
{
    const Node *current_node_ptr = &m_root;
    std::string current_prefix;

    for (const auto &letter : word)
    {
        current_prefix += letter;

        // Check if this prefix exists in the children
        int childIndex = current_node_ptr->getIndexOfChildWithKey(current_prefix);

        if (childIndex < 0) // could be == -1 but wanted to guard against possible conversion of
                            // negative int to size_t anyway
        {
            return inTrie::doesntExist;
        }
        else
        {
            current_node_ptr = current_node_ptr->getChildAtIndex(static_cast<size_t>(childIndex));
        }
    }

    return ((current_node_ptr->isValidWord()) ? inTrie::isWord : inTrie::existsButNotWord);
}
