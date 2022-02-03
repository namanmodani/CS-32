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

bool isPrecendent(char x, char y);
int paranthesesTest(string& infix, int index, int& endIndex);
int syntaxTest(string& infix);

int evaluate(string infix, const Map& values, string& postfix, int& result)
{
    //   Evaluates an integer arithmetic expression
    //   If infix is a syntactically valid infix integer expression whose
    //   only operands are single lower case letters (whether or not they
    //   appear in the values map), then postfix is set to the postfix
    //   form of the expression; otherwise postfix may or may not be
    //   changed, result is unchanged, and the function returns 1.  If
    //   infix is syntactically valid but contains at least one lower
    //   case letter operand that does not appear in the values map, then
    //   result is unchanged and the function returns 2.  If infix is
    //   syntactically valid and all its lower case operand letters
    //   appear in the values map, then if evaluating the expression
    //   (using for each letter in the expression the value in the map
    //   that corresponds to it) attempts to divide by zero, then result
    //   is unchanged and the function returns 3; otherwise, result is
    //   set to the value of the expression and the function returns 0.

    if (syntaxTest(infix) == 1)
        return 1;
    postfix = "";
    stack<char> Stack;
    for (char c: infix) {
        switch (c) {
            case ' ':
                break;
            case '/':
            case '*':
            case '-':
            case '+':
                while (!Stack.empty() && Stack.top() != '(' && isPrecendent(c, Stack.top())) {
                    postfix += Stack.top();
                    Stack.pop();
                }
                Stack.push(c);
                break;
            case '(':
                Stack.push(c);
                break;
            case ')':
                while (Stack.top() != '(') {
                    postfix += Stack.top();
                    Stack.pop();
                }
                Stack.pop();
                break;
            case 'a' ... 'z':
                postfix += c;
        }
    }

    while (!Stack.empty())
    {
        postfix += Stack.top();
        Stack.pop();
    }

    for (int i = 0; i < postfix.size(); i++)
    {
        if (isalpha(postfix[i]) && !values.contains(postfix[i]))
            return 2;
    }

    stack<int> resultStack;
    for (char c: postfix)
    {
        if (isalpha(c))
        {
            int cValue;
            values.get(c, cValue);
            resultStack.push(cValue);
        }
        else
        {
            int operand2 = resultStack.top();
            resultStack.pop();
            int operand1 = resultStack .top();
            resultStack.pop();

            switch(c)
            {
                case '/':
                    if (operand2 == 0)
                        return 3;
                    resultStack.push(operand1 / operand2);
                    break;
                case '*':
                    resultStack.push(operand1 * operand2);
                    break;
                case '-':
                    resultStack.push(operand1 - operand2);
                    break;
                case '+':
                    resultStack.push(operand1 + operand2);
                    break;
            }
        }
    }
    result = resultStack.top();
    resultStack.pop();
    return 0;
}

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

int syntaxTest(string& infix) {
    int count = 0;
    if (infix.size() == 0)
        return 1;
    for (int i = 0; i < infix.size(); i++)
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
            case '(': {
                if (count != 0)
                    return 1;
                int endIndex;
                int result = paranthesesTest(infix, i, endIndex);
                if (result == 1)
                    return 1;
                count++;
                i = endIndex;
                break;
            }
            default:
                if (isalpha(infix[i]) && islower(infix[i]))
                    count++;
                else
                    return 1;
        }
        if (count < 0 || count > 1)
            return 1;
    }
    if (count != 1)
        return 1;
    else
        return 0;
}

/*
int main()
{
    char vars[] = { 'a', 'e', 'i', 'o', 'u', 'y', '#' };
    int  vals[] = {  3,  -9,   6,   2,   4,   1  };
    Map m;
    for (int k = 0; vars[k] != '#'; k++)
        m.insert(vars[k], vals[k]);
    string pf;
    int answer;
    assert(evaluate("a+ e", m, pf, answer) == 0  &&
           pf == "ae+"  &&  answer == -6);
    answer = 999;
    assert(evaluate("", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a+", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a i", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("ai", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("()", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("()o", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("y(o+u)", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("y(*o)", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a+E", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("(a+(i-o)", m, pf, answer) == 1  &&  answer == 999);
    // unary operators not allowed:
    assert(evaluate("-a", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a*b", m, pf, answer) == 2  &&
           pf == "ab*"  &&  answer == 999);
    assert(evaluate("y +o *(   a-u)  ", m, pf, answer) == 0  &&
           pf == "yoau-*+"  &&  answer == -1);
    answer = 999;
    assert(evaluate("o/(y-y)", m, pf, answer) == 3  &&
           pf == "oyy-/"  &&  answer == 999);
    assert(evaluate(" a  ", m, pf, answer) == 0  &&
           pf == "a"  &&  answer == 3);
    assert(evaluate("((a))", m, pf, answer) == 0  &&
           pf == "a"  &&  answer == 3);
    cout << "Passed all tests" << endl;
}
*/