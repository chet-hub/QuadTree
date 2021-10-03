cmake_minimum_required(VERSION 3.20)
project(QuadTree)

set(CMAKE_CXX_STANDARD 11)

add_executable(untitled main.cpp QuadTreeNode.cpp QuadTreeNode.h Component.h Rectangle2D.cpp Rectangle2D.h Entity.h)
