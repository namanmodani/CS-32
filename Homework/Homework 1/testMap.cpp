//
// CS 32 Homework 1
// Naman Modani
// testMap.cpp
//

#include "Map.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    Map ritchie;  // maps strings to doubles
    assert(ritchie.empty());
    ValueType v = -1234.5;
    assert(!ritchie.get("abc", v) && v == -1234.5); // v unchanged by get failure
    ritchie.insert("xyz", 9876.5);
    assert(ritchie.size() == 1);
    KeyType k = "hello";
    assert(ritchie.get(0, k, v) && k == "xyz" && v == 9876.5);

    Map turing;
    turing.insert("Little Ricky", 3.206);
    turing.insert("Ethel", 3.538);
    turing.insert("Ricky", 3.350);
    turing.insert("Lucy", 2.956);
    turing.insert("Ethel", 3.538);
    turing.insert("Fred", 2.956);
    turing.insert("Lucy", 2.956);
    assert(turing.size() == 5); 
    string x;
    double y;
    turing.get(0, x, y);
    assert(x == "Ethel"); 
    turing.get(4, x, y);
    assert(x == "Ricky");
    turing.get(2, x, y);
    assert(x == "Little Ricky"); 
    assert(y == 3.206);

    Map gosling;
    gosling.insert("Fred", 2.956);
    Map torvalds;
    torvalds.insert("Ethel", 3.538);
    torvalds.insert("Lucy", 2.956);
    gosling.swap(torvalds);
    assert(gosling.size() == 2 && gosling.contains("Ethel") && gosling.contains("Lucy") &&
           torvalds.size() == 1 && torvalds.contains("Fred"));

    Map gpas;
    gpas.insert("Fred", 2.956);
    assert(!gpas.contains(""));
    gpas.insert("Ethel", 3.538);
    gpas.insert("", 4.000);
    gpas.insert("Lucy", 2.956);
    assert(gpas.contains(""));
    gpas.erase("Fred");
    assert(gpas.size() == 3 && gpas.contains("Lucy") && gpas.contains("Ethel") &&
           gpas.contains(""));
    string str;
    double dbl;
    assert(gpas.get(1, str, dbl) && str == "Ethel");
    assert(gpas.get(0, str, dbl) && str == "");

    cout << "Passed all tests" << endl;
}