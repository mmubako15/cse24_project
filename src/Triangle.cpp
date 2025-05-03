#include "Triangle.h"
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <cmath>
#include <math.h>

Triangle::Triangle(){
    x = 0.0;
    y = 0.0;
    size = 0.0;
    r = 0.0;
    g = 0.0;
    b = 0.0;
    
}

Triangle::Triangle(float x, float y, float r, float g, float b){
    this->x = x;
    this->y = y;
    size= 0.4;
    this->r = r;
    this->g = g;
    this->b = b;
}

void Triangle::draw(){
    glColor3f(r, g, b);
    float h = (sqrt(3.0f)/2.0f)* size; //Height of the the equilateral triangle like the shape provided
    glBegin(GL_TRIANGLES);
        glVertex2f(x,y +(2.0f / 3.0f)*h); // Point of top vertex
        glVertex2f(x - size /2, y - (1.0f / 3.0f)* h); //Bottom Left it is on the left because subtracted by size
        glVertex2f(x + size /2, y - (1.0f / 3.0f)* h);//Bottom Right it is on the Right because Added by size
    glEnd();
}

void Triangle::scale(float factor){
    size *= factor;
}

bool Triangle::contains(float mx, float my){
    float dx = mx - x;
    float dy = my - y;
    float distanceSquared = dx * dx + dy * dy;
    return distanceSquared <= size * size;
}
void Triangle::setColor(float r, float g, float b){
    this->r = r;
    this->g = g;
    this->b = b;
}

float Triangle::getX() const {
    return x;
}

float Triangle::getY() const {
    return y;
}

void Triangle::moveTo(float newX, float newY) {
    x = newX;
    y = newY;
}
