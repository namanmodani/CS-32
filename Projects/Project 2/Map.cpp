//
// CS 32 Project 2
// Naman Modani
// Map.cpp
//

#include "Map.h"

Map::Map()
{
    head = nullptr;
    tail = nullptr;
    m_size = 0;
}

// Destructor
Map::~Map()
{
    Node* p = head;
    p = head;
    while (p != nullptr)
    {
        Node* n = p->next;
        delete p;
        p = n;
    }
}

// Copy Constructor
Map::Map(const Map &src)
{
    head = nullptr;
    tail = nullptr;
    m_size = 0;

    for (Node *p = src.head; p != nullptr; p = p->next)
    {
        insert(p->key, p->value);
    }
}

// Assignment Operator
Map& Map::operator=(const Map& obj)
        {
            // Assignment only if objects are difference
            if (this != &obj)
            {
                Map temp(obj); // Copy & Swap
                swap(temp);
            }
            return *this;
        }

bool Map::empty() const
{
    return m_size == 0;
}

int Map::size() const
{
    return m_size;
}

bool Map::insert(const KeyType& key, const ValueType& value)
{
    // If the key is unequal to all keys presently in the map, and if the key/value pair can be added to the map, then do so and return true.

    // Iterate through the map looking for matching keys
    Node* p = head;
    while (p != nullptr) {
        if (p->key == key) {
            return false; // If so, return false
        }
        p = p->next;
    }

    // Create a pointer to a new node
    Node* n = new Node;

    // Insert new key and value
    n->key = key;
    n->value = value;

    n->next = nullptr;

    // The pointer prev points to current tail, or a nullptr if empty
    if (m_size == 0)
    {
        n->prev = nullptr;
        head = n; // If map is empty, set head to new node
    }
    else
    {
        // Otherwise, make the current tail's 'next' point to the new Node
        n->prev = tail;
        tail->next = n;
    }

    // Tail must now point to new node
    tail = n;
    // Increase m_size
    m_size++;

    return true;
}

bool Map::update(const KeyType& key, const ValueType& value)
{
    // Return true if key is equal to a key currently in the map.
    // This means that the key no longer maps to the value that it currently maps to. Instead, map to the value of the second parameter.

    Node* p = head;
    while (p != nullptr)
    {
        if (p->key == key)
        {
            p->value = value;
            return true;
        }
        p = p->next;
    }

    // Otherwise, leave map unchanged and return false.
    return false;
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value) {
    // If key is equal to a key currently in the map, then make that key map to the value of the second parameter.
    // Return true in this case.
    // If the key/value pair can be added to the map, then do so and return true.

    if (insert(key, value))
        return true;
    else if (update(key, value))
        return true;

    // Otherwise, make no change to the map and return false.
    return false;
}

bool Map::erase(const KeyType& key) {
    // If key is equal to a key currently in the map, remove the key/value pair with that key from the map and return true.

    Node* p = head;
    while (p != nullptr)
    {
        // If key is equal to key in map
        if (p->key == key)
        {
            // If there is a previous pointer, set its next to current p's next Node
            if (p->prev != nullptr)
                p->prev->next = p->next;
            else
                // p is currently equal to the head pointer
                // Set head pointer to second Node
                head = p->next;
            // If there is a next pointer, set its prev to current p's prev
            if (p->next != nullptr)
                p->next->prev = p->prev;
            else
                // p is currently equal to the tail pointer
                // Set tail pointer to second-to-last Node
                tail = p->prev;
            delete p;
            m_size--;
            return true;
        }
        p = p->next;
    }

    // Otherwise, leave map unchanged and return false.
    return false;
}

bool Map::contains(const KeyType& key) const
{
    // Return true if key is equal to a key currently in the map. Return false otherwise.
    Node* p = head;
    while (p != nullptr)
    {
        if (p->key == key)
            return true;
        p = p->next;
    }
    return false;
}

bool Map::get(const KeyType& key, ValueType& value) const
{
    // If key is equal to a key currently in the map, set value to the value in the map which that key maps to. Return true.
    Node* p = head;
    while (p != nullptr)
    {
        if (p->key == key)
        {
            value = p->value;
            return true;
        }
        p = p->next;
    }

    // Otherwise, leave value parameter of this function unchanged and return false.
    return false;
}

bool Map::get(int i, KeyType& key, ValueType& value) const
{
    // In case of 0 <= i < size()
    // Copy into the key and value parameters the key and value of the pair in the map whose key is strictly greater than exactly i keys in the map.
    // Return true

    // If i is invalid
    if (i < 0 || i >= m_size)
    {
        return false;
    }

    // Iterate through map
    for (Node *p = head; p != nullptr; p = p->next)
    {
        int count_below = 0;
        // Determine for each element in Map how many keys it is greater than
        for (Node *q = head; q != nullptr; q = q->next)
        {
            if (p->key > q->key)
                count_below++;

        }
        // If key count in the map less than p is equal to i, set values and return true
        if (count_below == i)
        {
            key = p->key;
            value = p->value;
            return true;
        }
    }

    // Otherwise, leave the key and value parameters unchanged and return false.
    return false;
}

void Map::swap(Map& other)
{
    // Exchange contents of one map with another.

    // Switch sizes
    int temp_size = other.m_size;
    other.m_size = m_size;
    m_size = temp_size;

    // Switch head pointers
    Node *temp = head;
    head = other.head;
    other.head = temp;

    // Switch tail pointers
    temp = tail;
    tail = other.tail;
    other.tail = temp;
}

bool merge(const Map& m1, const Map& m2, Map& result) {

    bool valid_merge = true;

    // Aliasing check
    if (&result == &m1)
    {
        // Iterate through m2
        for (int i = 0; i < m2.size(); i++)
        {
            KeyType currentKey;
            ValueType currentValue;
            // Obtain current key and value
            m2.get(i, currentKey, currentValue);

            // If current key matches a key in m1
            if (m1.contains(currentKey))
            {
                ValueType m1_val;
                // Obtain the corresponding value for m1
                m1.get(currentKey, m1_val);

                // If values are different for the same key
                if (currentValue != m1_val)
                {
                    // Delete the Node from result. Change return value to false.
                    result.erase(currentKey);
                    valid_merge = false;
                }
            }
            else
            {
                // If key is different, insert it into result
                result.insert(currentKey, currentValue);
            }

        }
    }
    else
    {
        result = m2;
        // Loop through m1
        for (int i = 0; i < m1.size(); i++)
        {
            KeyType currentKey;
            ValueType currentValue;
            // Get current key and value
            m1.get(i, currentKey, currentValue);

            // If current key matches a key in m1
            if (m2.contains(currentKey)) {
                ValueType m2_val;
                // Get the corresponding value for m1
                m2.get(currentKey, m2_val);

                // If values are different for the same key
                if (currentValue != m2_val) {
                    // Delete the Node from result. Change return value to false.
                    result.erase(currentKey);
                    valid_merge = false;
                }
            }
            else
            {
                // If key is different, insert it into result.
                result.insert(currentKey, currentValue);
            }

        }
    }
    return valid_merge;
}

void reassign(const Map& m, Map& result)
{
    if(&m == &result)
    {
        // In case both m and result point to the same address
        Map newResult; // Create a newResult map

        // If m has only one pair, then result must contain simply a copy of that pair.
        if(m.size() == 1)
        {
            KeyType key;
            ValueType val;
            m.get(0, key, val);
            newResult.insert(key, val);
            return;
        }

        if(m.size() % 2 == 0)
        {
            // If size is even, switch between groups of 2
            for(int j = 0; j <= m.size() - 2; j += 2)
            {
                KeyType key1;
                ValueType val1;
                m.get(j, key1, val1);
                KeyType key2;
                ValueType val2;
                m.get(j + 1, key2, val2);
                newResult.insert(key1, val2);
                newResult.insert(key2, val1);
            }
        }

        else
        {
            // If size is odd, iterate down to switch
            // Hold
            ValueType tempVal;
            KeyType key0;
            ValueType val0;
            m.get(0, key0, val0);
            tempVal = val0;

            // Iterate through linked list
            for(int k = 1; k < m.size(); k++)
            {
                KeyType key;
                ValueType val;
                m.get(k, key, val);
                newResult.insert(key, tempVal);
                tempVal = val;
            }
            // Set first
            newResult.insert(key0, tempVal);
        }

        result = newResult; // Set the result to newResult
        return;
    }

    // Result may not be empty. Set it to empty.
    while(result.empty() == false)
    {
        KeyType key;
        ValueType val;
        result.get(0, key, val);
        result.erase(key);
    }

    // If m has only one pair, then make the result simply contain a copy of that pair
    if(m.size() == 1)
    {
        KeyType key;
        ValueType val;
        m.get(0, key, val);
        result.insert(key, val);
        return;
    }

    if(m.size() % 2 == 0)
    {
        // Upon sizes being even, switch between groups of 2
        for(int j = 0; j <= m.size() - 2; j += 2)
        {
            KeyType key1;
            ValueType val1;
            m.get(j, key1, val1);
            KeyType key2;
            ValueType val2;
            m.get(j + 1, key2, val2);
            result.insert(key1, val2);
            result.insert(key2, val1);
        }
    }

    else
    {
        // If size is odd, iterate down to switch
        // Hold
        ValueType tempVal;
        KeyType key0;
        ValueType val0;
        m.get(0, key0, val0);
        tempVal = val0;

        // Iterate through linked list
        for(int k = 1; k < m.size(); k++)
        {
            KeyType key;
            ValueType val;
            m.get(k, key, val);
            result.insert(key, tempVal);
            tempVal = val;
        }

        // Set first
        result.insert(key0, tempVal);
    }
}