#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape.h"

class Rectangle : public Shape {
    float x;
    float y;
    float width;
    float height;
    float r;
    float g;
    float b;

public:
    Rectangle();
    Rectangle(float x, float y, float r, float g, float b);
    void draw();
    bool contains(float mx, float my);
    void setColor(float r, float g, float b);
    void scale(float factor);

    float getX() const override;
    float getY() const override;
    void moveTo(float newX, float newY) override;
};

#endif