//
// CS 32 Homework 4
// Naman Modani
// badlist.cpp
//

void removeBad(list<Movie*>& li)
{
    list<Movie*>::iterator it;
    for (it = li.begin(); it != li.end();)
    {
        if ((*it)->rating() < 50)
        {
            delete (*it);
            it = li.erase(it);
        }
        else
        {
            it++;
        }
    }
}