//
// CS 32 Project 4
// Naman Modani
// MatchMaker.h
//

#ifndef MATCHMAKER_H
#define MATCHMAKER_H

#include "MemberDatabase.h"
#include "AttributeTranslator.h"

class MatchMaker
{
public:
    MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at);
    ~MatchMaker();
    std::vector<EmailCount> IdentifyRankedMatches(std::string email, int threshold) const;
private:
    const MemberDatabase* m_MemberDatabase;
    const AttributeTranslator* m_AttributeTranslator;
};

#endif //MATCHMAKER_H