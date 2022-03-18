cmake_minimum_required(VERSION 3.21)
project(Unhinged)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Unhinged
        main.cpp
        AttributeTranslator.h
        AttributeTranslator.cpp
        MatchMaker.h
        MatchMaker.cpp
        MemberDatabase.h
        MemberDatabase.cpp
        PersonProfile.h
        PersonProfile.cpp
        RadixTree.h
        utility.h
        utility.cpp
        members.txt
        provided.h
        translator.txt)
