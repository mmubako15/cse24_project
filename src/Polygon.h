#ifndef POLYGON_H
#define POLYGON_H

#include "Shape.h"

class Polygon : public Shape {
    float x, y, size, r, g ,b;
    
public:
Polygon();
Polygon(float x, float y, float r, float g, float b);
void draw();
bool contains(float mx, float my);
void setColor(float r, float g, float b);
};
#endif