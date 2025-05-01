#include "Application.h"
#include "Enums.h"

using namespace bobcat;
using namespace std;

void Application::onCanvasMouseDown(bobcat::Widget* sender, float mx, float my) {
    TOOL tool = toolbar->getTool();
    Color color = colorSelector->getColor();

    if (tool == PENCIL) {
        canvas->addPoint(mx, my, color.getR(), color.getG(), color.getB(), 7);
        canvas->redraw();
    }
    else if (tool == ERASER) {
        canvas->addPoint(mx, my, 1.0, 1.0, 1.0, 14);
        canvas->redraw();
    }
    else if (tool == RECTANGLE) {
        canvas->addRectangle(mx, my, color.getR(), color.getG(), color.getB());
        canvas->redraw();
    }
    else if (tool == CIRCLE) { 
        canvas->addCircle(mx, my, color.getR(), color.getG(), color.getB());
        canvas->redraw();
    }
    else if (tool == TRIANGLE){
        canvas->addTriangle(mx, my, color.getR(), color.getG(), color.getB());
        canvas->redraw();
    }
    else if(tool == POLYGON){
        canvas->addPolygon(mx, my, color.getR(), color.getG(), color.getB());
        canvas->redraw();
    }
    // If tool is plus
    else if(tool == PLUS){
        
    }
   

    else if (tool == MOUSE) {
        selectedShape = canvas->getSelectedShape(mx, my);
    }

}

void Application::onCanvasDrag(bobcat::Widget* sender, float mx, float my) {
    TOOL tool = toolbar->getTool();
    Color color = colorSelector->getColor();

    if (tool == PENCIL) {
        canvas->addPoint(mx, my, color.getR(), color.getG(), color.getB(), 7);
        canvas->redraw();
    }
    else if (tool == ERASER) {
        canvas->addPoint(mx, my, 1.0, 1.0, 1.0, 14);
        canvas->redraw();
    }
}

void Application::onToolbarChange(bobcat::Widget* sender) {
    ACTION action = toolbar->getAction();

    if (action == CLEAR) {
        canvas->clear();
        canvas->redraw();
    }
}

void Application::onColorSelectorChange(bobcat::Widget* sender) {
    Color color = colorSelector->getColor();

    if (selectedShape) {
        cout << "Update selected shape color" << endl;
        selectedShape->setColor(color.getR(), color.getG(), color.getB());
        canvas->redraw();
    }

    /*
    When shape is selected if minus is pressed then subtract shapes size by 10 percent 
    if + plus is hit then increase shapes size by 10%
    */

}

Application::Application() {
    window = new Window(25, 75, 400, 500, "Paint App");

    selectedShape = nullptr;

    toolbar = new Toolbar(0, 0, 50, 500);
    canvas = new Canvas(50, 0, 350, 450);
    // Defining variables to repersent parameters for ColorSelector
    int height, width, x, y;
    x = 50;
    y = 450;
    width = 350;
    height = 550;
    colorSelector = new ColorSelector(x, y, width, height);
    colorSelector->box(FL_BORDER_BOX);

    window->add(toolbar);
    window->add(canvas);
    window->add(colorSelector);

    ON_MOUSE_DOWN(canvas, Application::onCanvasMouseDown);
    ON_DRAG(canvas, Application::onCanvasDrag);
    ON_CHANGE(toolbar, Application::onToolbarChange);
    ON_CHANGE(colorSelector, Application::onColorSelectorChange);

    window->show();
}
/*
Change window size to big to find color selector.
*/