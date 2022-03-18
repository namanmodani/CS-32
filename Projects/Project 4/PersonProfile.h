//
// CS 32 Project 4
// Naman Modani
// PersonProfile.h
//

#ifndef PERSONPROFILE_H
#define PERSONPROFILE_H

#include <string>
#include "RadixTree.h"
#include <vector>
#include <set>

struct AttValPair;

class PersonProfile
{
public:
    PersonProfile(std::string name, std::string email);
    ~PersonProfile();
    std::string GetName() const;
    std::string GetEmail() const;
    void AddAttValPair(const AttValPair& attval);
    int GetNumAttValPairs() const;
    bool GetAttVal(int attribute_num, AttValPair& attval) const;
private:
    std::string m_name;
    std::string m_email;
    int m_countAttValPairs;
    // Maps string attributes to set of string values
    RadixTree<std::set<std::string>*>* m_RadixTreeAttVal;
    // Vector of all distinct AttValPairs
    std::vector<AttValPair*>* m_AttValVector;
};

#endif //PERSONPROFILE_H