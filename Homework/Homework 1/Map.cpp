//
// CS 32 Homework 1
// Naman Modani
// Map.cpp
//

#include "Map.h"

Map::Map() {}

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
    if (map_size >= DEFAULT_MAX_ITEMS)
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
    Map* smallerMap;
    Map* biggerMap;

    if (size() > other.size())
    {
        smallerMap = &other;
        biggerMap = this;
    }
    else
    {
        smallerMap = this;
        biggerMap = &other;
    }

    for (int i = 0; i < smallerMap->size(); i++)
    {
        Pair temp = map_pairs[i];
        map_pairs[i] = other.map_pairs[i];
        other.map_pairs[i] = temp;
    }

    for (int i = smallerMap->size(); i < biggerMap->size(); i++)
    {
        smallerMap->map_pairs[i] = biggerMap->map_pairs[i];
    }

    int temp = map_size;
    map_size = other.map_size;
    other.map_size = temp;
}

void Map::dump() const {}