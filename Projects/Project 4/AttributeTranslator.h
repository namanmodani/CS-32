//
// CS 32 Project 4
// Naman Modani
// AttributeTranslator.h
//

#ifndef ATTRIBUTETRANSLATOR
#define ATTRIBUTETRANSLATOR

#include <vector>
#include <set>
#include <string>
#include "provided.h"
#include "RadixTree.h"

class AttributeTranslator
{
public:
    AttributeTranslator();
    ~AttributeTranslator();
    bool Load(std::string filename);
    std::vector<AttValPair> FindCompatibleAttValPairs(const AttValPair& source) const;
private:
    // Tree of AttVal strings to vector of compatible AttValPairs
    RadixTree<std::vector<AttValPair>*>* m_RadixTreePairToPair;
    // Set of AttVal strings
    std::set<std::string>* m_SourceAttValSet;
};

#endif //ATTRIBUTETRANSLATOR