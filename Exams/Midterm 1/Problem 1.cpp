#include <iostream>
#include <string>
#include <cassert>
using namespace std;

class StringList
{
public:
    StringList(string text);
    // You may declare other member functions for your test code to call
    void eraseThrees();
    void printItem() const;
private:
    struct Node
    {
        char  value;
        Node* next;
        Node(char v, Node* n) : value(v), next(n) {}
    };
    Node* head;  // points to first Node in the list
};

StringList::StringList(string text)
{
    //  For example, StringList s("heap"); creates s containing
    //  a list with values  'h'  'e'  'a'  'p'
    head = nullptr;
    for (int k = text.size(); k > 0; k--)
        head = new Node(text[k-1], head);
}

// You may implement other member functions here for test purposes,
// but you will not turn them in as part of your submission.

// SUBMIT AS YOUR ANSWER ONLY THE CODE BETWEEN THIS COMMENT AND THE
// COMMENT AFTER THE END OF THE eraseThrees IMPLEMENTATION

void StringList::eraseThrees()
{
    if (head == nullptr)
        return;

    Node *prev = head;

    if (prev->next == nullptr)
        return;

    Node *deletedNode = prev->next;

    int i = 2;
    while (deletedNode != nullptr)
    {
        if (i % 3 == 0)
        {
            prev->next = deletedNode->next;
            delete deletedNode;
            deletedNode = prev->next;
            i++;
        }
        else
        {
            deletedNode = deletedNode->next;
            prev = prev->next;
            i++;
        }
    }
}

void StringList::printItem() const // add this to public functions
{
    for (Node* p = head; p!= nullptr; p = p->next)
    {
        cout << p->value << " ";
    }
    cout << endl;
}

// SUBMIT AS YOUR ANSWER ONLY THE CODE BETWEEN THIS COMMENT AND THE
// COMMENT BEFORE THE START OF THE eraseThrees IMPLEMENTATION

int main()
{
    StringList x("I love Smallberg"); // e h y
    x.eraseThrees();
    x.printItem();
    StringList y("123123"); // 3 3
    y.eraseThrees();
    y.printItem();
    StringList z("");
    z.eraseThrees();
    z.printItem();
}