//
// CS 32 Homework 2
// Naman Modani
// mazestack.cpp
//

#include <iostream>
#include <stack>
#include <string>

using namespace std;

class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const {return m_r;}
    int c() const {return m_c;}
private:
    int m_r;
    int m_c;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    // Return true if there is a path from (sr,sc) to (er,ec)
    // through the maze; return false otherwise

    stack<Coord> coordStack;
    coordStack.push(Coord(sr, sc));

    maze[sr][sc] = '!';
    while (!coordStack.empty())
    {
        Coord current = coordStack.top();
        coordStack.pop();

        if (current.r() == er & current.c() == ec)
            return true;
        if (maze[current.r()][current.c() - 1] == '.')
        {
            maze[current.r()][current.c() - 1] = '!';
            coordStack.push(Coord(current.r(), current.c() - 1));
        }
        if (maze[current.r() + 1][current.c()] == '.')
        {
            maze[current.r() + 1][current.c()] = '!';
            coordStack.push(Coord(current.r() + 1, current.c()));
        }
        if (maze[current.r()][current.c() + 1] == '.')
        {
            maze[current.r()][current.c() + 1] = '!';
            coordStack.push(Coord(current.r(), current.c() + 1));
        }
        if (maze[current.r() - 1][current.c()] == '.')
        {
            maze[current.r() - 1][current.c()] = '!';
            coordStack.push(Coord(current.r() - 1, current.c()));
        }
    }
    return false;
}

// int main()
//{
//    string maze[10] = {
//            "XXXXXXXXXX",
//            "X.X..X...X",
//            "X....XXX.X",
//            "X.XXXX.X.X",
//            "X......XXX",
//            "X.XX.X...X",
//            "X.X..X.X.X",
//            "X.X.XXXX.X",
//            "X.X...X..X",
//            "XXXXXXXXXX"
//    };
//
//    if (pathExists(maze, 10,10, 4,6, 1,1))
//        cout << "Solvable!" << endl;
//    else
//        cout << "Out of luck!" << endl;
//}