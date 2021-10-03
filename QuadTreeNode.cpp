//
// Created by bear on 2021-10-01.
//


#include <iostream>
#include "QuadTreeNode.h"
#include "Rectangle2D.h"

void QuadTreeNode::divideSquare() {
    topLeft = new QuadTreeNode(thisRect.minX,
                               (thisRect.minY + thisRect.maxY) / 2,
                               (thisRect.minX + thisRect.maxX) / 2,
                               thisRect.maxY);

    topRight = new QuadTreeNode((thisRect.minX + thisRect.maxX) / 2,
                                (thisRect.minY + thisRect.maxY) / 2,
                                thisRect.maxX,
                                thisRect.maxY);

    bottomLeft = new QuadTreeNode(thisRect.minX,
                                  thisRect.minY,
                                  (thisRect.maxX + thisRect.minX) / 2,
                                  (thisRect.maxY + thisRect.minY) / 2);

    bottomRight = new QuadTreeNode((thisRect.minX + thisRect.maxX) / 2,
                                   thisRect.minY,
                                   thisRect.maxX,
                                   (thisRect.maxY + thisRect.minY) / 2);

    for (int i = 0; i < rects.size(); i++) {
        if (topLeft->thisRect.Contain(rects[i])) {
            topLeft->Insert(rects[i]);
            rects.erase(rects.begin() + i);
        } else if (topRight->thisRect.Contain(rects[i])) {
            topRight->Insert(rects[i]);
            rects.erase(rects.begin() + i);
        } else if (bottomLeft->thisRect.Contain(rects[i])) {
            bottomLeft->Insert(rects[i]);
            rects.erase(rects.begin() + i);
        } else if (bottomRight->thisRect.Contain(rects[i])) {
            bottomRight->Insert(rects[i]);
            rects.erase(rects.begin() + i);
        }
    }
}

bool QuadTreeNode::HasChildren() {
    return (topLeft != nullptr);
}

void QuadTreeNode::Insert(const Rectangle2D &rect) {
    if (!thisRect.Contain(rect)) {
        std::cerr << "rect is out of the area of the quadTree node" << ".\n";
        return;
    }
    if (HasChildren()) { // insert the point to the children nodes
        if (topLeft->thisRect.Contain(rect)) {
            topLeft->Insert(rect);
        } else if (topRight->thisRect.Contain(rect)) {
            topRight->Insert(rect);
        } else if (bottomLeft->thisRect.Contain(rect)) {
            bottomLeft->Insert(rect);
        } else if (bottomRight->thisRect.Contain(rect)) {
            bottomRight->Insert(rect);
        } else {
            rects.push_back(rect);
        }
    } else {// new children nodes and reinsert the nodes
        rects.push_back(rect);
        if (rects.size() > QuadTreeNode::capacity
            && (thisRect.maxX - thisRect.minX) > MIN_WIDTH
            && (thisRect.maxY - thisRect.minY) > MIN_HEIGHT
                ) {
            this->divideSquare();
        }
    }
}


void ChildNodeCount(Rectangle2D *rect, QuadTreeNode *node, int *count) {
    if (!rect->Intersect(node->thisRect)) {
        return;
    }
    for (int i = 0; i < node->rects.size(); i++) {
        if (node->rects[i].Intersect(*rect)) {
            (*count)++;
        }
    }
    if (node->HasChildren()) {
        ChildNodeCount(rect, node->topLeft, count);
        ChildNodeCount(rect, node->topRight, count);
        ChildNodeCount(rect, node->bottomLeft, count);
        ChildNodeCount(rect, node->bottomRight, count);
    }
}


void NodeCount(QuadTreeNode *node, int *count) {

    for (int i = 0; i < node->rects.size(); i++) {
        for (int j = i + 1; j < node->rects.size(); j++) {
            if (node->rects[i].Intersect(node->rects[j])) {
                (*count)++;
            }
        }
        if (node->HasChildren()) {
            ChildNodeCount(&(node->rects[i]), node->topLeft, count);
            ChildNodeCount(&(node->rects[i]), node->topRight, count);
            ChildNodeCount(&(node->rects[i]), node->bottomLeft, count);
            ChildNodeCount(&(node->rects[i]), node->bottomRight, count);
        }
    }

    if (node->HasChildren()) {
        NodeCount(node->topLeft, count);
        NodeCount(node->topRight, count);
        NodeCount(node->bottomLeft, count);
        NodeCount(node->bottomRight, count);
    }
}


void QuadTreeNode::IntersectCount(int *count) {
    NodeCount(this, count);
}


