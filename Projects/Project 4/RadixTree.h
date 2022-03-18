//
// CS 32 Project 4
// Naman Modani
// RadixTree.h
//

#ifndef RADIXTREE_H
#define RADIXTREE_H

#include <map>
#include <vector>
#include <string>

const int MAX_CHILD_COUNT = 128;

template <typename ValueType>
class RadixTree
{
public:
    RadixTree();
    ~RadixTree();
    void insert(std::string key, const ValueType& value);
    ValueType* search(std::string key) const;
private:

    struct RadixNode
    {
        // If lead node, not null
        ValueType* val;
        RadixNode* children[MAX_CHILD_COUNT];
        std::string edge[MAX_CHILD_COUNT];
        RadixNode()
        {
            val = nullptr;
            for (int i = 0; i < MAX_CHILD_COUNT; i++)
                children[i] = nullptr;
        }
        ~RadixNode()
        {
            delete val;
            for (int i = 0; i < MAX_CHILD_COUNT; i++)
            {
                delete children[i];
            }
        }
    };

    RadixNode* m_root;

    void insertHelper(RadixNode* root, std::string, const ValueType& value);
    RadixNode* searchHelper(RadixNode* root, std::string key) const;
};

template <typename ValueType>
RadixTree<ValueType>::RadixTree()
        : m_root(new typename RadixTree<ValueType>::RadixNode)
{}

template <typename ValueType>
RadixTree<ValueType>::~RadixTree()
{
    // If ValueType is already a pointer type, this does not free memory
    delete m_root;
}

template <typename ValueType>
void RadixTree<ValueType>::insertHelper(RadixNode* root, std::string key, const ValueType& value)
{
    // Nothing matches key, ergo add copy of value
    if (key.empty())
    {
        if (root->val != nullptr)
        {
            delete root->val;
        }
        ValueType* toInsert = new ValueType(value);
        root->val = toInsert;
        return;
    }

    // Key forms own unique edge
    int currChar = key[0];
    if (root->children[currChar] == nullptr)
    {
        root->children[currChar] = new RadixNode;
        root->edge[currChar] = key;
        insertHelper(root->children[currChar], "", value);
        return;
    }

    std::string existingEdge = root->edge[currChar];
    int matchLen = 0;
    while (matchLen < existingEdge.length() && matchLen < key.length() && existingEdge[matchLen] == key[matchLen])
    {
        matchLen++;
    }

    // Part of key matches entire existing edge
    if (matchLen == existingEdge.length())
    {
        insertHelper(root->children[currChar], key.substr(matchLen), value);
        return;
    }

    // Entire key matches part of existing edge
    if (matchLen == key.length())
    {
        RadixNode* toAdd = new RadixNode;
        toAdd->children[existingEdge[matchLen]] = root->children[currChar];
        toAdd->edge[existingEdge[matchLen]] = existingEdge.substr(matchLen);
        root->children[currChar] = toAdd;
        root->edge[currChar] = key;
        insertHelper(root->children[currChar], "", value);
        return;
    }

    // Part of key matches part of existing edge
    if (matchLen < existingEdge.length() && matchLen < key.length())
    {
        RadixNode* toAdd = new RadixNode;
        toAdd->children[existingEdge[matchLen]] = root->children[currChar];
        toAdd->edge[existingEdge[matchLen]] = existingEdge.substr(matchLen);
        root->children[currChar] = toAdd;
        root->edge[currChar] = key.substr(0, matchLen);
        insertHelper(root->children[currChar], key.substr(matchLen), value);
        return;
    }
}

template <typename ValueType>
void RadixTree<ValueType>::insert(std::string key, const ValueType& value)
{
    insertHelper(m_root, key, value);
}

template <typename ValueType>
typename RadixTree<ValueType>::RadixNode* RadixTree<ValueType>::searchHelper(typename RadixTree<ValueType>::RadixNode* root, std::string key) const
{
    // Location
    if (key == "")
    {
        if (root->val != nullptr)
        {
            return root;
        }
        return nullptr;
    }

    int currChar = key[0];
    // Unrecognized edge
    if (root->children[currChar] == nullptr)
    {
        return nullptr;
    }
    std::string existingEdge = root->edge[currChar];
    int len;
    // Part of key could match entire edge
    if (existingEdge.length() < key.length())
    {
        len = existingEdge.length();
    }
    // Key could match part of edge or entire edge
    else
    {
        len = key.length();
    }
    // Part of key does not match part of edge
    if (existingEdge.substr(0, len) != key.substr(0, len))
    {
        return nullptr;
    }
    // Edge matches part of key, shorten key
    if (existingEdge.size() == len)
    {
        return searchHelper(root->children[currChar], key.substr(existingEdge.size()));
    }
    // Key does not complete edge
    else
    {
        return nullptr;
    }
}

template <typename ValueType>
ValueType* RadixTree<ValueType>::search(std::string key) const
{
    const RadixNode* node = searchHelper(m_root, key);
    if (node != nullptr)
    {
        return node->val;
    }
    return nullptr;
}

#endif //RADIXTREE_H