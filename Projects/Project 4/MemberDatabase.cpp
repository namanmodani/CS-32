//
// CS 32 Project 4
// Naman Modani
// MemberDatabase.cpp
//

#include "MemberDatabase.h"
#include "provided.h"
#include <fstream>
#include <iostream>

MemberDatabase::MemberDatabase()
        : m_RadixTreeEmailToProfile(new RadixTree<PersonProfile*>), m_RadixTreeAttValToEmails(new RadixTree<std::vector<std::string>*>),
          m_EmailSet(new std::set<std::string>), m_AttValSet(new std::set<std::string>)
{}

MemberDatabase::~MemberDatabase()
{
    for (auto it = m_EmailSet->begin(); it != m_EmailSet->end(); it++)
    {
        PersonProfile** pp = m_RadixTreeEmailToProfile->search(*it);
        if (pp != nullptr)
        {
            // Always true
            delete (*pp);
        }
    }
    for (auto it = m_AttValSet->begin(); it != m_AttValSet->end(); it++)
    {
        std::vector<std::string>** emails = m_RadixTreeAttValToEmails->search(*it);
        if (emails != nullptr)
        {
            // Always true
            delete (*emails);
        }
    }
    delete m_RadixTreeEmailToProfile;
    delete m_RadixTreeAttValToEmails;
    delete m_EmailSet;
    delete m_AttValSet;
}

bool MemberDatabase::LoadDatabase(std::string filename)
{
    std::ifstream databaseFile(filename);
    if (!databaseFile)
    {
        return false;
    }

    if (databaseFile.is_open())
    {
        std::string name, email, att, val, skip;
        int attvalCount = 0;
        while (databaseFile.good())
        {
            std::getline(databaseFile, name);
            std::getline(databaseFile, email);
            if (m_EmailSet->find(email) != m_EmailSet->end())
            {
                // Invalid database when member with email already exists
                return false;
            }
            m_RadixTreeEmailToProfile->insert(email, new PersonProfile(name, email));
            PersonProfile** ppToAdd = m_RadixTreeEmailToProfile->search(email);
            m_EmailSet->insert(email);

            databaseFile >> attvalCount;
            std::getline(databaseFile, skip);
            for (int i = 0; i != attvalCount; i++)
            {
                std::getline(databaseFile, att, ',');
                std::getline(databaseFile, val);
                (*ppToAdd)->AddAttValPair(AttValPair(att, val));

                std::string attvalKey = att + val;
                std::vector<std::string>** emailVec = m_RadixTreeAttValToEmails->search(attvalKey);
                if (emailVec == nullptr)
                {
                    m_RadixTreeAttValToEmails->insert(attvalKey, new std::vector<std::string>);
                    emailVec = m_RadixTreeAttValToEmails->search(attvalKey);
                    m_AttValSet->insert(attvalKey);
                }
                (*emailVec)->push_back(email);
            }
            std::getline(databaseFile, skip);
        }
    }
    return true;
}

std::vector<std::string> MemberDatabase::FindMatchingMembers(const AttValPair& input) const
{
    std::string relevantAttVal = input.attribute + input.value;
    std::vector<std::string>** matchingMembersVec = m_RadixTreeAttValToEmails->search(relevantAttVal);
    if (matchingMembersVec != nullptr)
    {
        return **matchingMembersVec;
    }
    return std::vector<std::string>();
}

const PersonProfile* MemberDatabase::GetMemberByEmail(std::string email) const
{
    PersonProfile** pp = m_RadixTreeEmailToProfile->search(email);
    if (pp != nullptr)
    {
        return *pp;
    }
    return nullptr;
}