//
// Created by bear on 2021-10-01.
//

/*
Programmer – C++ Evaluation

The sections in this test build upon each other to form one solution for submission. The work
has been divided into the three logical steps below.

Programmer Evaluation – Step 1 of 3

Design and implement a C++ program with the following:
• An axis-aligned Rectangle2D with floating-point coordinates.
• An algorithm that checks if two Rectangle2Ds intersect.
• Test code that verifies your implementation’s correctness.

*/


#include "Rectangle2D.h"

bool Rectangle2D::Intersect(const Rectangle2D &rect) const {
    //not non-intersect equals intersect
    //return !(minX > rect.maxX || maxX < rect.minX || minY > rect.maxY || maxY < rect.minY);
    return minX <= rect.maxX && maxX >= rect.minX && minY <= rect.maxY && maxY >= rect.minY;
}

bool Rectangle2D::Contain(const Rectangle2D &rect) const {
    return minX < rect.minX
           && maxX > rect.maxX
           && minY < rect.minY
           && maxY > rect.maxY;
}

bool Rectangle2D::Contain(float x,float y){
    return minX < x
           && maxX > x
           && minY < y
           && maxY > y;
}

/**
 * There are 4 cases need to test
 *  1. inner_Rectangle
 *  2. out_Rectangle
 *  3. intersect_edge_Rectangle
 *  4. contained_Rectangle
 *
 *  +---------contained_Rectangle-------+
 *  |                                   |
 *  |                                   |
 *  |   +---rectangle----+              |
 *  |   |                |              |
 *  |   |                |              |
 *  |   |   |inner| +-edge--+ +-out-+   |
 *  |   |   |     | |    |  | |     |   |
 *  |   |   |     | |    |  | |     |   |
 *  |   |   +-----+ +----+--+ +-----+   |
 *  |   |                |              |
 *  |   |                |              |
 *  |   +----------------+              |
 *  |                                   |
 *  |                                   |
 *  +-----------------------------------+
 *
 * @return
 */
bool test_Rectangle2D_intersect() {

    auto rectangle =  Rectangle2D(1,1,4,4);

    auto inner_Rectangle = Rectangle2D(2,2,3,3);
    auto out_Rectangle =  Rectangle2D(5,2,6,3);
    auto intersect_edge_Rectangle = Rectangle2D(3,2,5,3);
    auto contained_Rectangle =  Rectangle2D(0,0,7,5);

    if (rectangle.Intersect(inner_Rectangle)) return true;
    if (rectangle.Contain(inner_Rectangle)) return true;
    if (!rectangle.Intersect(out_Rectangle)) return true;
    if (rectangle.Intersect(intersect_edge_Rectangle)) return true;
    if (rectangle.Intersect(contained_Rectangle)) return true;
    if (contained_Rectangle.Intersect(rectangle)) return true;

    return false;
}