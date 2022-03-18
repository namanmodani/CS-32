//
// CS 32 Project 4
// Naman Modani
// AttributeTranslator.cpp
//

#include "AttributeTranslator.h"
#include <fstream>
#include <iostream>

using namespace std;

AttributeTranslator::AttributeTranslator()
        : m_RadixTreePairToPair(new RadixTree<std::vector<AttValPair>*>), m_SourceAttValSet(new std::set<std::string>)
{}

AttributeTranslator::~AttributeTranslator()
{
    for (auto it = m_SourceAttValSet->begin(); it != m_SourceAttValSet->end(); it++)
    {
        std::vector<AttValPair>** compatibleVec = m_RadixTreePairToPair->search(*it);
        if (compatibleVec != nullptr)
        {
            // Always true
            delete (*compatibleVec);
        }
    }
    delete m_RadixTreePairToPair;
    delete m_SourceAttValSet;
}

bool AttributeTranslator::Load(std::string filename)
{
    std::ifstream translatorFile(filename);
    if (!translatorFile)
    {
        return false;
    }

    if (translatorFile.is_open())
    {
        std::string attSRead, valSRead, attCRead, valCRead, skip;
        while (std::getline(translatorFile, attSRead, ','))
        {
            attSRead.erase(0, attSRead.find_first_not_of('\n'));
            std::getline(translatorFile, valSRead, ',');
            std::getline(translatorFile, attCRead, ',');
            std::getline(translatorFile, valCRead);

            /*
            cerr << "attSRead " << attSRead << endl;
            cerr << "valSRead " << valSRead << endl;
            cerr << "attCRead " << attCRead << endl;
            cerr << "valCRead " << valCRead << endl;
            */

            std::string sourcePair(attSRead + valSRead);
            AttValPair compatiblePair(attCRead, valCRead);
            std::vector<AttValPair>** compatibleVec = m_RadixTreePairToPair->search(sourcePair);
            if (compatibleVec == nullptr)
            {
                m_RadixTreePairToPair->insert(sourcePair, new std::vector<AttValPair>);
                compatibleVec = m_RadixTreePairToPair->search(sourcePair);
                m_SourceAttValSet->insert(sourcePair);
            }
            (*compatibleVec)->push_back(compatiblePair);
        }
    }
    return true;
}

std::vector<AttValPair> AttributeTranslator::FindCompatibleAttValPairs(const AttValPair& source) const
{
    std::string sourcePair = source.attribute + source.value;
    std::vector<AttValPair>** compatibleVec = m_RadixTreePairToPair->search(sourcePair);
    if (compatibleVec != nullptr)
    {
        return **compatibleVec;
    }
    return std::vector<AttValPair>();
}