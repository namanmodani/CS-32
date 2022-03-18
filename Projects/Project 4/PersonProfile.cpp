//
// CS 32 Project 4
// Naman Modani
// PersonProfile.cpp
//

#include "PersonProfile.h"
#include "provided.h"

PersonProfile::PersonProfile(std::string name, std::string email)
        : m_name(name), m_email(email), m_countAttValPairs(0), m_RadixTreeAttVal(new RadixTree<std::set<std::string>*>), m_AttValVector(new std::vector<AttValPair*>)
{}

PersonProfile::~PersonProfile()
{
    for (auto it = m_AttValVector->begin(); it != m_AttValVector->end(); it++)
    {
        std::set<std::string>** attSet = m_RadixTreeAttVal->search((*it)->attribute);
        if (attSet != nullptr)
        {
            // Always true
            delete (*attSet);
            // Do not delete the same thing twice
            *attSet = nullptr;
        }
        delete (*it);
    }
    delete m_RadixTreeAttVal;
    delete m_AttValVector;
}

std::string PersonProfile::GetName() const
{
    return m_name;
}

std::string PersonProfile::GetEmail() const
{
    return m_email;
}

void PersonProfile::AddAttValPair(const AttValPair& attval)
{
    std::set<std::string>** foundAttSet = m_RadixTreeAttVal->search(attval.attribute);
    if (foundAttSet == nullptr)
    {
        m_RadixTreeAttVal->insert(attval.attribute, new std::set<std::string>);
        foundAttSet = m_RadixTreeAttVal->search(attval.attribute);
    }
    if ((*foundAttSet)->find(attval.value) == (*foundAttSet)->end())
    {
        (*foundAttSet)->insert(attval.value);
        m_AttValVector->push_back(new AttValPair(attval));
        m_countAttValPairs++;
    }
}

int PersonProfile::GetNumAttValPairs() const
{
    return m_countAttValPairs;
}

bool PersonProfile::GetAttVal(int attribute_num, AttValPair& attval) const
{
    if (attribute_num < 0 || attribute_num >= GetNumAttValPairs())
    {
        return false;
    }
    attval = *(*m_AttValVector)[attribute_num];
    return true;
}