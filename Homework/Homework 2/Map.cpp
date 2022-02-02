// Map.cpp

#include "Map.h"

Map::Map()
        : m_size(0)
{
    // create dummy node
    m_head = new Node;
    m_head->m_next = m_head;
    m_head->m_prev = m_head;
}

Map::~Map()
{
    // Delete the m_size non-dummy nodes plus the dummy node

    for (Node* p = m_head->m_prev ; m_size >= 0; m_size--)
    {
        Node* toBeDeleted = p;
        p = p->m_prev;
        delete toBeDeleted;
    }
}

Map::Map(const Map& other)
        : m_size(other.m_size)
{
    // Create dummy node; don't initialize its pointers

    m_head = new Node;

    // Initialize prev to last node created

    Node* prev = m_head;

    // Copy each non-dummy node from the other list; each iteration will set
    // the m_next of the previous node copied

    for (Node* p = other.m_head->m_next ; p != other.m_head; p = p->m_next)
    {
        // Create a copy of the node p points to
        Node* pnew = new Node;
        pnew->m_key = p->m_key;
        pnew->m_value = p->m_value;

        // Connect the new node to the previous one
        pnew->m_prev = prev;
        prev->m_next = pnew;

        // Reset prev to last node created
        prev = pnew;
    }

    // Connect last node created to m_head
    m_head->m_prev = prev;
    prev->m_next = m_head;
}

Map& Map::operator=(const Map& rhs)
{
    if (this != &rhs)
    {
        Map temp(rhs);
        swap(temp);
    }
    return *this;
}

bool Map::erase(const KeyType& key)
{
    Node* p = findFirstAtLeast(key);

    if (p == m_head  ||  p->m_key != key)  // not found
        return false;

    // unlink the node from the list and destroy it

    p->m_prev->m_next = p->m_next;
    p->m_next->m_prev = p->m_prev;
    delete p;

    m_size--;
    return true;
}

bool Map::get(const KeyType& key, ValueType& value) const
{
    Node* p = findFirstAtLeast(key);

    if (p == m_head  ||  p->m_key != key)  // not found
        return false;
    value = p->m_value;
    return true;
}

bool Map::get(int i, KeyType& key, ValueType& value) const
{
    if (i < 0  ||  i >= m_size)
        return false;

    // If i is closer to the head of the list, go forward to reach that
    // position; otherwise, start from tail and go backward.

    Node* p;
    if (i < m_size / 2)  // closer to head
    {
        p = m_head->m_next;
        for (int k = 0; k != i; k++)
            p = p->m_next;
    }
    else  // closer to tail
    {
        p = m_head->m_prev;
        for (int k = m_size-1; k != i; k--)
            p = p->m_prev;
    }

    key = p->m_key;
    value = p->m_value;
    return true;
}

void Map::swap(Map& other)
{
    // swap head pointers
    Node* tempHead = m_head;
    m_head = other.m_head;
    other.m_head = tempHead;

    // swap sizes
    int t = m_size;
    m_size = other.m_size;
    other.m_size = t;
}

Map::Node* Map::findFirstAtLeast(const KeyType& key) const
{
    // Do a linear search through the list

    Node* p;
    for (p = m_head->m_next; p != m_head && p->m_key < key; p = p->m_next)
        ;
    return p;
}

bool Map::doInsertOrUpdate(const KeyType& key, const ValueType& value,
                           bool mayInsert, bool mayUpdate)
{
    Node* p = findFirstAtLeast(key);

    if (p != m_head  &&  p->m_key == key)  // found
    {
        if (mayUpdate)
            p->m_value = value;
        return mayUpdate;
    }
    if (!mayInsert)  // not found, and not allowed to insert
        return false;

    // Create a new node
    Node* newp = new Node;
    newp->m_key = key;
    newp->m_value = value;

    // Insert new node before p, which points to the node with the
    // least key > newp's key

    //     Connect it to p's predecessor
    newp->m_prev = p->m_prev;
    newp->m_prev->m_next = newp;

    //     Connect it to p
    newp->m_next = p;
    p->m_prev = newp;

    m_size++;
    return true;
}

bool merge(const Map& m1, const Map& m2, Map& result)
{
    // For better performance, the bigger map should be the basis for
    // the result, and we should iterate over the elements of the
    // smaller one, adjusting the result as required.

    const Map* bigger;
    const Map* smaller;
    if (m1.size() >= m2.size())
    {
        bigger = &m1;
        smaller = &m2;
    }
    else
    {
        bigger = &m2;
        smaller = &m1;
    }

    // Guard against the case that result is an alias for m1 or m2
    // (i.e., that result is a reference to the same map that m1 or m2
    // refers to) by building the answer in a local variable res.  When
    // done, swap res with result; the old value of result (now in res) will
    // be destroyed when res is destroyed.

    bool status = true;
    Map res(*bigger);               // res starts as a copy of the bigger map
    for (int n = 0; n < smaller->size(); n++)  // for each pair in smaller
    {
        KeyType k;
        ValueType vsmall;
        smaller->get(n, k, vsmall);
        ValueType vbig;
        if (!res.get(k, vbig))      // key in smaller doesn't appear in bigger
            res.insert(k, vsmall);  //     so add it to res
        else if (vbig != vsmall)    // same key, different value
        {                           //     so pair shouldn't be in res
            res.erase(k);
            status = false;
        }
    }
    result.swap(res);
    return status;
}

void reassign(const Map& m, Map& result)
{
    // Guard against the case that result is an alias for m (i.e., that
    // result is a reference to the same map that m refers to) by building
    // the answer in a local variable res.  When done, swap res with result;
    // the old value of result (now in res) will be destroyed when res is
    // destroyed.

    Map res;

    if (!m.empty())
    {
        KeyType prevKey;
        ValueType value0;

        // Get pair 0, which must succeed since m is not empty

        m.get(0, prevKey, value0);

        // For each pair i after pair 0, insert into res a pair with
        // pair i-1's key and pair i's value.  (This loop executes 0 times
        // if m has only one pair.)

        for (int i = 1; i < m.size(); i++)
        {
            KeyType k;
            ValueType v;
            m.get(i, k, v);
            res.insert(prevKey, v);
            prevKey = k;
        }

        // Insert a final pair with last pair's key and pair 0's value.

        res.insert(prevKey, value0);
    }

    result.swap(res);
}