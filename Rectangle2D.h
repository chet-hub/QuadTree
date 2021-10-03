//
// Created by bear on 2021-10-01.
//

#ifndef UNTITLED_RECTANGLE2D_H
#define UNTITLED_RECTANGLE2D_H


class Rectangle2D {
public:
    float minX;
    float minY;
    float maxX;
    float maxY;

    Rectangle2D(const Rectangle2D &rect) : minX(rect.minX), minY(rect.minY), maxX(rect.maxX), maxY(rect.maxY) {};

    Rectangle2D(float minX, float minY, float maxX, float maxY) : minX(minX), minY(minY), maxX(maxX), maxY(maxY) {};

    bool Intersect(const Rectangle2D &rectangle2D) const;

    bool Contain(const Rectangle2D &rect) const;
    
    bool Contain(float x,float y);
};


#endif //UNTITLED_RECTANGLE2D_H
