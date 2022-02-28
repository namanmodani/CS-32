cmake_minimum_required(VERSION 3.21)
project(Project_3)

set(CMAKE_CXX_STANDARD 14)

include_directories(SuperPeachSisters)

add_executable(Project_3
        SuperPeachSisters/Actor.cpp
        SuperPeachSisters/Actor.h
        SuperPeachSisters/GameConstants.h
        SuperPeachSisters/GameController.cpp
        SuperPeachSisters/GameController.h
        SuperPeachSisters/GameWorld.cpp
        SuperPeachSisters/GameWorld.h
        SuperPeachSisters/GraphObject.h
        SuperPeachSisters/Level.h
        SuperPeachSisters/main.cpp
        SuperPeachSisters/SoundFX.h
        SuperPeachSisters/SpriteManager.h
        SuperPeachSisters/StudentWorld.cpp
        SuperPeachSisters/StudentWorld.h SuperPeachSisters/Actor.cpp SuperPeachSisters/Actor.h SuperPeachSisters/StudentWorld.cpp SuperPeachSisters/StudentWorld.h)
