//
// CS 32 Homework 1
// Naman Modani
// testnewMap.cpp
//

#include "newMap.h"
#include <cassert>
#include <iostream>
using namespace std;

int main()
{
    Map a(5);
    Map b(5);

    KeyType key[5] = {"Floyd", "Queen", "Who", "Beatles", "Zeppelin"};
    ValueType value  = 89;

    for (int n = 0; n < 5; n++)
        assert(b.insert(key[n], value));

    assert(!b.insert(key[5], value));

    a.swap(b);
    assert(!a.insert(key[5], value)  &&  b.insert(key[4], value));

    cout << "Passed all tests" << endl;
}