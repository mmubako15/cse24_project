#include "Polygon.h"
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <cmath>

Polygon::Polygon(){
    x = 0.0;
    y = 0.0;
    size = 0.0;
    r = 0.0;
    g = 0.0;
    b = 0.0;
    
}
Polygon::Polygon(float x, float y, float r, float g, float b){
    this->x = x;
    this->y = y;
    size = 0.2;
    this->r = r;
    this->g = g;
    this->b = b;
}

void Polygon::draw(){
    glColor3f(r, g, b);

    float half = size/2.0f;

    glBegin(GL_POLYGON);
        glVertex2d (x, y + size);
        glVertex2d(x + 0.951f * size, y + 0.309f * size);
        glVertex2d(x + 0.588f * size, y - 0.809f * size);
        glVertex2d(x - 0.588f * size, y - 0.809f * size);
        glVertex2d(x - 0.951f * size, y + 0.309f * size);
    glEnd();
}   

void Polygon::scale(float factor){
    size *= factor;
    if (size < 0.01f){
        size = 0.01f;
    }
}

bool Polygon::contains(float mx, float my){
    float dx = mx -x;
    float dy = my - y;
    float distanceSquared =  dx* dx + dy * dy;
    return distanceSquared <= size*size;
}

void Polygon::setColor(float r, float g, float b){
    this->r = r;
    this->g = g;
    this->b = b;
}

float Polygon::getX() const {
    return x;
}

float Polygon::getY() const {
    return y;
}

void Polygon::moveTo(float newX, float newY) {
    x = newX;
    y = newY;
}