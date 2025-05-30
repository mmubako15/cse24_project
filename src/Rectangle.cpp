#include "Rectangle.h"
#include <GL/freeglut.h>

Rectangle::Rectangle() {
    x = 0.0;
    y = 0.0;
    width = 0.4;
    height = 0.4;
    r = 0.0;
    g = 0.0;
    b = 0.0;
}

Rectangle::Rectangle(float x, float y, float r, float g, float b) {
    this->x = x;
    this->y = y;
    width = 0.4;
    height = 0.4;
    this->r = r;
    this->g = g;
    this->b = b;
}

void Rectangle::draw() {
    glColor3f(r, g, b);

    glBegin(GL_POLYGON);
        glVertex2f(x - width/2, y + height/2);
        glVertex2f(x + width/2, y + height/2);
        glVertex2f(x + width/2, y - height/2);
        glVertex2f(x - width/2, y - height/2);
    glEnd();
}

void Rectangle::scale(float factor){
    width *= factor;
    height *= factor;
    if(width < 0.01f){
        width =  0.01f;
    }
    if(height < 0.01f){
        height = 0.01f;
    }
}

bool Rectangle::contains(float mx, float my) {
    if (mx >= x - width/2 && mx <= x + width/2 && my <= y + height/2 && my >= y - height/2) {
        return true;
    }
    return false;
}

void Rectangle::setColor(float r, float g, float b) {
    this->r = r;
    this->g = g;
    this->b = b;
}

float Rectangle::getX() const {
    return x;
}

float Rectangle::getY() const {
    return y;
}

void Rectangle::moveTo(float newX, float newY) {
    x = newX;
    y = newY;
}

