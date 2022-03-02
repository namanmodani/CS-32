//
// CS 32 Homework 4
// Naman Modani
// list.cpp
//

void listAll(string path, const Class* c)  // two-parameter overload
{
    path += c->name();
    cout << path << endl;
    vector<Class*>::const_iterator it;
    for (it = c->subclasses().begin(); it != c->subclasses().end(); it++)
    {
        listAll(path + "=>", *it);
    }
}
