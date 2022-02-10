//
// CS 32 Homework 3
// Naman Modani
// Problem 3: maze.cpp
//

class Coord
{
public:
    Coord(int rr, int cc): m_r(rr), m_c(cc){}
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

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    if (sr == er && sc == ec)
        return true;
    maze[sr][sc] = "*";

    // North
    if (sr > 0 && maze[sr - 1][sc] == '.')
    {
        if (pathExists(maze, nRows, nCols, sr - 1, sc, er, ec))
            return true;
    }
    // South
    if (sr < nRows - 1 && maze[sr + 1][sc] == '.')
    {
        if (pathExists(maze, nRows, nCols, sr + 1, sc, er, ec))
            return true;
    }
    // East
    if (sc < nCols - 1 && maze[sr][sc + 1] == '.')
    {
        if (pathExists(maze, nRows, nCols, sr, sc + 1, er, ec))
            return true;
    }
    // West
    if (sc > 0 && maze[sr][sc - 1] == '.')
    {
        if (pathExists(maze, nRows, nCols, sr, sc - 1, er, ec))
            return true;
    }
    return false;
}