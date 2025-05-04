#include "Scribble.h"

Scribble::Scribble(float r, float g, float b, int size)
    : r(r), g(g), b(b), size(size) {}

Scribble::~Scribble() {
    for (auto p : points)
        delete p;
}

void Scribble::addPoint(float x, float y) {
    points.push_back(new Point(x, y, r, g, b, size));
}

void Scribble::draw() {
    for (auto p : points)
        p->draw();
}

bool Scribble::contains(float mx, float my) {
    // Considered clicked if near any point in the scribble
    for (auto p : points) {
        float dx = p->getX() - mx;
        float dy = p->getY() - my;
        if (dx * dx + dy * dy < 16) 
            return true;
    }
    return false;
}

void Scribble::moveTo(float newX, float newY) {
    if (points.empty()) return;

    float dx = newX - getX();
    float dy = newY - getY();
    for (auto p : points) {
        p->setX(p->getX() + dx);
        p->setY(p->getY() + dy);
    }
}

float Scribble::getX() const {
    if (points.empty()) return 0;
    return points[0]->getX();
}

float Scribble::getY() const {
    if (points.empty()) return 0;
    return points[0]->getY();
}

void Scribble::setColor(float r, float g, float b) {
    this->r = r;
    this->g = g;
    this->b = b;

    for (auto p : points) {
        p->setColor(r, g, b);  
    }
}

void Scribble::scale(float factor) {
    if (points.empty()) return;

    float cx = getX();
    float cy = getY();

    for (auto p : points) {
        float dx = p->getX() - cx;
        float dy = p->getY() - cy;
        p->setX(cx + dx * factor);
        p->setY(cy + dy * factor);
    }
}

