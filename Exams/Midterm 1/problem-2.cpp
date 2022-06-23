#include <iostream>
#include <cassert>
using namespace std;

class Weight
{
public:
    Weight(int w) : m_w(w) {}
    int getw() const { return m_w; }
private:
    int m_w;
};

class Pod
{
public:
    Pod(int p);
    ~Pod();
    Pod(const Pod& other);
private:
    Weight* m_wt;
    int m_ppp;
    int* m_peas;
};

Pod::Pod(int p)
{
    m_wt = new Weight(p);
    m_ppp = 3 * p;
    m_peas = &m_ppp;
}

// SUBMIT AS YOUR ANSWER ONLY THE CODE BETWEEN THIS COMMENT AND THE
// COMMENT AFTER THE END OF THE DESTRUCTOR AND COPY CONSTRUCTOR
// IMPLEMENTATIONS

Pod::~Pod()
{
    delete m_wt;
}

Pod::Pod(const Pod &other)
{
    m_ppp = other.m_ppp;
    m_peas = &m_ppp;
    m_wt = new Weight(m_ppp/3);
}

// SUBMIT AS YOUR ANSWER ONLY THE CODE BETWEEN THIS COMMENT AND THE
// COMMENT BEFORE THE START OF THE DESTRUCTOR AND COPY CONSTRUCTOR
// IMPLEMENTATIONS

void test()
{
    Pod p1(2);
    Pod p2(p1);
}

int main()
{
    test();
    cout << "All tests succeeded" << endl;
}
