//
// CS 32 Homework 1
// Naman Modani
// newMap.cpp
//

#include "newMap.h"

Map::Map()
{
    map_pairs = new Pair[DEFAULT_MAX_ITEMS];
    map_maxItems = DEFAULT_MAX_ITEMS;
}

Map::~Map()
{
    delete [] map_pairs;
}

Map::Map(int size)
{
    map_pairs = new Pair[size];
    map_maxItems = size;
}

Map::Map(const Map &src)
{
    map_pairs = new Pair[src.map_maxItems];

    for (int i = 0; i < src.map_size; i++)
    {
        map_pairs[i].key = src.map_pairs[i].key;
        map_pairs[i].value = src.map_pairs[i].value;
    }

    map_size = src.map_size;
    map_maxItems = src.map_maxItems;
}

Map& Map::operator=(const Map &src)
        {
            delete map_pairs;
            map_pairs = new Pair[src.map_maxItems];
            for (int i = 0; i < src.map_size; i++)
            {
                map_pairs[i].key = src.map_pairs[i].key;
                map_pairs[i].value = src.map_pairs[i].value;
            }

            map_size = src.map_size;
            map_maxItems = src.map_maxItems;
            return *this;
        }

bool Map::empty() const
{
    if (map_size == 0)
        return true;
    else
        return false;
}

int Map::size() const
{
    return map_size;
}

bool Map::insert(const KeyType &key, const ValueType &value)
{
    if (map_size >= map_maxItems)
        return false;

    int index = 0;

    while (index < map_size)
    {
        if (map_pairs[index].key == key)
            return false;
        if (map_pairs[index].key > key)
        {
            break;
        }
        index++;
    }

    for (int i = map_size; i > index; i--)
    {
        map_pairs[i].key = map_pairs[i - 1].key;
        map_pairs[i].value = map_pairs[i - 1].value;
    }

    map_pairs[index].key = key;
    map_pairs[index].value = value;
    map_size += 1;
    return true;
}

bool Map::update(const KeyType &key, const ValueType &value)
{
    for (int i = 0; i < map_size; i++)
    {
        if (map_pairs[i].key == key)
        {
            map_pairs[i].value = value;
            return true;
        }

        if (map_pairs[i].key > key)
            break;
    }
    return false;
}

bool Map::insertOrUpdate(const KeyType &key, const ValueType &value)
{
    for (int i = 0; i < map_size; i++)
    {
        if (map_pairs[i].key == key)
        {
            map_pairs[i].value = value;
            return true;
        }

        if (map_pairs[i].key > key)
            break;
    }

    return insert(key, value);
}

bool Map::erase(const KeyType &key)
{
    for (int i = 0; i < map_size; i++)
    {
        if (map_pairs[i].key == key)
        {
            for (int j = i; j < map_size - 1; j++)
            {
                map_pairs[j].key = map_pairs[j + 1].key;
                map_pairs[j].value = map_pairs[j + 1].value;
            }
            map_size -= 1;
            return true;
        }
    }
    return false;
}

bool Map::contains(const KeyType &key) const
{
    for (int i = 0; i < map_size; i++)
    {
        if (map_pairs[i].key == key)
            return true;
    }
    return false;
}

bool Map::get(const KeyType &key, ValueType &value) const {
    for (int i = 0; i < map_size; i++)
    {
        if (map_pairs[i].key == key)
        {
            value = map_pairs[i].value;
            return true;
        }
    }
    return false;
}

bool Map::get(int i, KeyType &key, ValueType &value) const
{
    if (i < 0 || i >= size())
        return false;

    key = map_pairs[i].key;
    value = map_pairs[i].value;
    return true;
}

void Map::swap(Map &other)
{
    Pair* temp = map_pairs;
    map_pairs = other.map_pairs;
    other.map_pairs = temp;

    int size = map_size;
    map_size = other.map_size;
    other.map_size = size;

    int max = map_maxItems;
    map_maxItems = other.map_maxItems;
    other.map_maxItems = max;
}

void Map::dump() const {}