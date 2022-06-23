#include <iostream>
#include <cassert>
using namespace std;

// SUBMIT AS YOUR ANSWER ONLY THE CODE BETWEEN THIS COMMENT AND THE
// COMMENT AT THE END OF THE product FUNCTION

int product(int x, int y)
{
    if(y < 0)
    {
        return product(-x, -y);
    }

    if(y == 0)
    {
        return 0;
    }

    if(y == 1)
    {
        return x;
    }

    return x + product(x, y - 1);
}

// SUBMIT AS YOUR ANSWER ONLY THE CODE BETWEEN THIS COMMENT AND THE
// COMMENT AT THE START OF THE product FUNCTION

int main()
{
    assert(product(7, 5) == 35);
    assert(product(-4, 8) == -32);

    cout << "All tests succeeded" << endl;
}
