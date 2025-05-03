#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Shape.h"

class Triangle : public Shape {
    float x, y, size, r, g, b; // Size can be interpreted as side length or radius from center

public: 
Triangle();
Triangle(float x, float y, float r, float g, float b);
void draw();
bool contains(float mx, float my);
void setColor(float r, float g, float b);
void scale(float factor);

    float getX() const override;
    float getY() const override;
    void moveTo(float newX, float newY) override;

};

#endif