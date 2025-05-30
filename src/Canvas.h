#ifndef CANVAS_H
#define CANVAS_H

#include <bobcat_ui/all.h>
#include <vector>
#include "Point.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Shape.h"
#include "Scribble.h"


class Canvas : public bobcat::Canvas_ {
    std::vector<Shape*> shapes;
    Scribble* currentScribble = nullptr;
    

public:
    Canvas(int x, int y, int w, int h);

    void addRectangle(float x, float y, float r, float g, float b);

    void addCircle(float x, float y, float r, float g, float b);

    void addTriangle(float x, float y, float r, float g, float b);

    void addPolygon(float x, float y, float r, float g, float b);
    
    void clear();

    void render();

    void startScribble(float r, float g, float b, int size);

    void addScribblePoint(float x, float y);

    void endScribble();

    void removeShape(Shape* shape);

    // For future reference when passing Shape* the function is expecting a pointer to a shape object not the object itself
    void bringToFront(Shape* shape);
    void bringToBack(Shape* shape);

    Shape* getSelectedShape(float mx, float my);
    
};

#endif