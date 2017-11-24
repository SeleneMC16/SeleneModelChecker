cmake_minimum_required(VERSION 3.8)
project(SeleneModelChecker)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp)
set(SOURCE_FILES cppitertools/itertools.hpp main.cpp AtlModel.cpp AtlModel.h DisjointUnion.cpp DisjointUnion.h SeleneModel.cpp SeleneModel.h)
add_executable(SeleneModelChecker ${SOURCE_FILES})