//
// Created by bear on 2021-10-01.
//

#ifndef UNTITLED_QUADTREENODE_H
#define UNTITLED_QUADTREENODE_H

#include <unordered_set>
#include <vector>
#include "Rectangle2D.h"

const int CAPACITY = 4;
const int MIN_WIDTH = 5;
const int MIN_HEIGHT = 5;
/**

CAPACITY / MIN_WIDTH / MIN_HEIGHT / time
4           5           5           147ms
5           5           5           153ms
6           5           5           145ms

 */

class QuadTreeNode {
private:
    //how many rectangles a square contain
    static const int capacity = CAPACITY;
    void divideSquare();
public:
    QuadTreeNode *topLeft = nullptr;
    QuadTreeNode *topRight = nullptr;
    QuadTreeNode *bottomLeft = nullptr;
    QuadTreeNode *bottomRight = nullptr;
    std::vector<Rectangle2D> rects;
    Rectangle2D thisRect;
    QuadTreeNode(float minX, float minY, float maxX, float maxY) : thisRect(minX, minY, maxX, maxY) {}
    bool HasChildren();
    void Insert(const Rectangle2D &rect);
    void IntersectCount(int * count);
};

#endif //UNTITLED_QUADTREENODE_H
