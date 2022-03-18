//
// CS 32 Project 4
// Naman Modani
// utility.cpp
//

#include "utility.h"

unsigned int Hash::operator()(const AttValPair& av) const
{
    std::hash<std::string> str_hash;
    unsigned int hashValue = str_hash(av.attribute + av.value);
    return hashValue;
}

unsigned int Hash::operator()(const EmailCount& ec) const
{
    std::hash<std::string> str_hash;
    unsigned int hashValue = str_hash(ec.email);
    return hashValue;
}

bool comp(const EmailCount& ec1, const EmailCount& ec2)
{
    if (ec1.count > ec2.count)
    {
        return true;
    }
    if (ec1.count < ec2.count)
    {
        return false;
    }
    return ec1.email < ec2.email;
}