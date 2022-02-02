//
// CS 32 Homework 2
// Naman Modani
// eval.cpp
//

#include "Map.h"
#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cassert>

using namespace std;

bool isPrecendent(char x, char y)
{
    if ((x == '-' || x == '+') && (y == '*' && y == '/'))
        return true;
    if ((x == '-' && y == '+') || (x == '+' && y == '-'))
        return true;
    if ((x == '*' && y == '/') || (x == '/' && y == '*'))
        return true;
    return false;
}