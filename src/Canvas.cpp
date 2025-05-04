#include "Canvas.h"
#include "Circle.h"
#include "Polygon.h"
#include "Triangle.h"
#include <GL/freeglut.h>
#include "Scribble.h"


Canvas::Canvas(int x, int y, int w, int h) : Canvas_(x, y, w, h) {
    // 
}

void Canvas::addPoint(float x, float y, float r, float g, float b, int size) {
    points.push_back(new Point(x, y, r, g, b, size));
}

void Canvas::addRectangle(float x, float y, float r, float g, float b) {
    shapes.push_back(new Rectangle(x, y, r, g, b));
}

void Canvas::addCircle(float x, float y, float r, float g, float b) {
    shapes.push_back(new Circle(x, y, r, g, b));
}
// adding add Triangle
void Canvas::addTriangle(float x, float y, float r, float g, float b){
    shapes.push_back(new Triangle( x,  y, r,  g,  b));
}
void Canvas::addPolygon(float x, float y, float r, float g, float b){
    shapes.push_back(new Polygon( x,  y, r,  g,  b));
    
}
void Canvas::bringToFront(Shape *shape){
    // Last object in vector shapes
    int index = -1;
    for(int i = 0; i< shapes.size(); i++){
        // Once we find the shape we are looking for 
        if(shapes[i] == shape){
            index = i;
            break;
        }
    }
    if(index != -1){
        Shape* temp = shapes[index];
        for(int i = index; i < shapes.size() - 1; ++i){
            shapes[i] = shapes[i+1];
        }
        shapes[shapes.size() - 1] = temp;
    }
}

void Canvas::bringToBack(Shape *shape){
    int index = -1;
    for(int i = 0; i < shapes.size(); i++){
        if(shapes[i] == shape){
            index = i;
            break;
        }
    }
    if(index != -1){
        Shape* temp = shapes[index];
        for(int i = index; i > 0; --i){
            shapes[i] = shapes[i - 1];
        }
        shapes[0] = temp;
    }
}

void Canvas::clear() {
    for (unsigned int i = 0 ; i < points.size(); i++) {
        delete points[i];
    }
    points.clear();

    for (unsigned int i = 0 ; i < shapes.size(); i++) {
        delete shapes[i];
    }
    shapes.clear();
}

void Canvas::render() {
    for (unsigned int i = 0 ; i < points.size(); i++) {
        points[i]->draw();
    }

    for (unsigned int i = 0 ; i < shapes.size(); i++) {
        shapes[i]->draw();
    }
}

Shape* Canvas::getSelectedShape(float mx, float my) {
    Shape* selectedShape = nullptr;
    
    for (unsigned int i = 0; i < shapes.size(); i++) {
        // ask every shape if we clicked on it
        if (shapes[i]->contains(mx, my)) {
            std::cout << "Clicked on shape[" << i << "]" << std::endl;
            selectedShape = shapes[i];
            break;
        }
    }

    if (selectedShape == nullptr) {
        std::cout << "No selected shape" << std::endl;
    }

    return selectedShape;
}

Scribble* currentScribble = nullptr;

void Canvas::startScribble(float r, float g, float b, int size) {
    currentScribble = new Scribble(r, g, b, size);
    shapes.push_back(currentScribble);
}

void Canvas::addScribblePoint(float x, float y) {
    if (currentScribble)
        currentScribble->addPoint(x, y);
}

void Canvas::endScribble() {
    currentScribble = nullptr;
}