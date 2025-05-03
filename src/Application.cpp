#include "Application.h"
#include "Enums.h"

using namespace bobcat;
using namespace std;

void Application::onCanvasMouseDown(bobcat::Widget* sender, float mx, float my) {
    cout << "Mouse clicked at: " << mx << ", " << my << endl;

    TOOL tool = toolbar->getTool();
    cout << "Current : Tool: " << tool << endl; // Debug satement
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
    else if(tool == PLUS){
       if (selectedShape) {
          cout << "Selected shape exists. Scaling now." << endl; //Debug Statement
          selectedShape->scale(1.1f);
          cout << "Hitting + button" << endl; //Debug Statement
          canvas->redraw();
       }
    } 
    else if(tool == MINUS){
        Shape* shapeUnderCursor = canvas->getSelectedShape(mx,my);
        if(shapeUnderCursor){
            selectedShape = shapeUnderCursor;
            selectedShape->scale(0.9f);
            cout << "Hitting shape under cursor for -" << endl; //Debug Statement
            canvas->redraw();
        }
        else {
            cout << "No shape under cursor for -"; //Debug Statement
        }

    }
    else if (tool == SEND_TO_FRONT){
        if(selectedShape){
            canvas->bringToFront(selectedShape);
            canvas->redraw();
        }
    }
    
    else if (tool == SEND_TO_BACK){
        if(selectedShape){
            canvas->bringToBack(selectedShape);
            canvas->redraw();
        }
    }
    else if (tool == MOUSE) {
        selectedShape = canvas->getSelectedShape(mx, my);
        if (selectedShape) {
        draggingShape = selectedShape;
        dragOffsetX = mx - selectedShape->getX();
        dragOffsetY = my - selectedShape->getY();
    }
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

    if (draggingShape) {
        draggingShape->moveTo(mx - dragOffsetX, my - dragOffsetY);
        canvas->redraw();
    }
}

void Application::onCanvasMouseUp(bobcat::Widget* sender, float mx, float my) {
    draggingShape = nullptr;
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
        cout << "Update selected shape color" << endl; //Debug Statement
        selectedShape->setColor(color.getR(), color.getG(), color.getB());
        canvas->redraw();
    }

    /*
    When shape is selected if minus is pressed then subtract shapes size by 10 percent 
    if + plus is hit then increase shapes size by 10%
    */

}

Application::Application() {
    window = new Window(25, 75, 400, 600, "Paint App");

    selectedShape = nullptr;

    toolbar = new Toolbar(0, 0, 50, 600);
    canvas = new Canvas(50, 0, 350, 550);
    // Defining variables to repersent parameters for ColorSelector
    int height, width, x, y;
    x = 50;
    y = 550;
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