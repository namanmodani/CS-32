//
// CS 32 Project 2
// Naman Modani
// Map.h
//

#ifndef MAP_H
#define MAP_H

#include <string>

using KeyType = std::string;
using ValueType = double;

class Map
{
public:
    Map();
    ~Map(); // Destructor
    Map(const Map& src); // Copy Constructor
    Map& operator = (const Map& obj); // Assignment Operator
    bool empty() const;
    int size() const;
    bool insert(const KeyType& key, const ValueType& value);
    bool update(const KeyType& key, const ValueType& value);
    bool insertOrUpdate(const KeyType& key, const ValueType& value);
    bool erase(const KeyType& key);
    bool contains(const KeyType& key) const;
    bool get(const KeyType& key, ValueType& value) const;
    bool get(int i, KeyType& key, ValueType& value) const;
    void swap(Map& other);

private:
    struct Node
    {
        KeyType key;
        ValueType value;
        Node* next;
        Node* prev;
    };

    int m_size;
    Node* head;
    Node* tail;
};

// Map Algorithms
bool merge(const Map& m1, const Map& m2, Map& result);
void reassign(const Map& m, Map& result);

#endif // MAP_H