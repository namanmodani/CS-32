#include <iostream>

#include "History.h"
#include "globals.h"

using namespace std;

History::History(int nRows, int nCols) : m_rows(nRows), m_cols(nCols)
{
    const int LEN = nRows * nCols;
    m_recTable = new char[LEN];
    for (int i = 0; i < LEN; i++)
    {
        m_recTable[i] = '.';
    }
}

bool History::record(int r, int c)
{
    if (r > m_rows || c > m_cols)
        return false;
    char &ch = m_recTable[(r - 1) * m_cols + c - 1];
    if (ch == '.')
        ch = 'A';
    else if (ch < 'Z')
        ch++;
    return true;
}

void History::display() const
{
    clearScreen();
    for (int i = 0; i < m_rows; i++)
    {
        for (int j = 0; j < m_cols; j++)
        {
            cout << m_recTable[i * m_cols+ j];
        }
        cout << endl;
    }
    cout << endl;
}

History::~History()
{
    delete[] m_recTable;
}