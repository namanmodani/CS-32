//
// CS 32 Homework 3
// Naman Modani
// Problem 3: maze.cpp
//

class Coord
{
public:
    (int rr, int cc): m_r(rr), m_c(cc){}
    int r() const
    {
        return m_r;
    }
    int c() const
    {
        return m_c;
    }
private:
    int m_r;
    int m_c;
};

bool pathExists(string maze[], int nRows, int nCold, int sr, int sc, int er, int ec)
{
    if (sr == er && sc == ec)
        return true;
    maze[sr][sc] = "!";

    // North
    if (maze[sr - 1][sc] == '.' && pathExists(maze, nRows, nCold, sr - 1, sc, er, ec))
        return true;
    // South
    if (maze[sr + 1][sc] == '.' && pathExists(maze, nRows, nCold, sr + 1, sc, er, ec))
        return true;
    // East
    if (maze[sr][sc + 1] == '.' && pathExists(maze, nRows, nCold, sr, sc + 1, er, ec))
        return true;
    // West
    if (maze[sr][sc - 1] == '.' && pathExists(maze, nRows, nCold, sr, sc - 1, er, ec))
        return true;
    return false;
}