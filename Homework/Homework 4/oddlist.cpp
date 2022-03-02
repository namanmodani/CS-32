//
// CS 32 Homework 4
// Naman Modani
// oddlist.cpp
//

void removeOdd(list<int>& li)
{
    list<int>::iterator it;
    for (it = li.begin(); it != li.end();)
    {
        if ((*it) % 2 != 0)
        {
            it = li.erase(it);
        }
        else
        {
            it++;
        }
    }
}