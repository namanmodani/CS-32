#ifndef HISTORY_H
#define HISTORY_H

#include "globals.h"

class History
{
public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;
    ~History();

private:
    char *m_recTable;
    char m_rows;
    char m_cols;
};

#endif // Include guard

