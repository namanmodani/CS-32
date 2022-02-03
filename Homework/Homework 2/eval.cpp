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

int paranthesesTest(string& infix, int index, int& endIndex)
{
    int count = 0;
    for (int i = index + 1; i < infix.size(); i++)
    {
        switch (infix[i])
        {
            case ' ':
                break;
            case '/':
            case '*':
            case '-':
            case '+':
                count--;
                break;
            case '(':
            {
                if (count != 0)
                    return 1;
                int end;
                int result = paranthesesTest(infix, i, end);
                if (result == 1)
                    return 1;
                count++;
                i = end;
                break;
            }
            case ')':
            {
                if (count != 1)
                    return 1;
                endIndex = i;
                return 0;
                default:
                    if (isalpha(infix[i]) && islower(infix[i]))
                    {
                        count++;
                    }
                    else
                        return 1;
            }

        }
    }
    return 1;
}

 