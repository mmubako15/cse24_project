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
        // canvas->addPoint(mx, my, color.getR(), color.getG(), color.getB(), 7);     These 2 lines are not needed anymore
       // canvas->redraw();                                                          because scribble handles it
        Color c = colorSelector->getColor();
        canvas->startScribble(c.getR(), c.getG(), c.getB(), 7);
    }
    else if (tool == ERASER) {
        Shape* shapeUnderCursor = canvas->getSelectedShape(mx, my);
    if (shapeUnderCursor) {
        canvas->removeShape(shapeUnderCursor);
        delete shapeUnderCursor;  
        canvas->redraw();
    }
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
        if(selectedShape){
            selectedShape->scale(0.9f);
            canvas->redraw();
        }
        else{
            cout << "No shape selected for -" <<endl;
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
        draggingShape = selectedShape; //updating what new shape to drag 
        if (draggingShape) {
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
        canvas->addScribblePoint(mx, my); //creating a scribble along with normal point
        canvas->redraw();
    }
    else if (tool == ERASER) {
        canvas->redraw();
    }

    if (draggingShape) {
        draggingShape->moveTo(mx - dragOffsetX, my - dragOffsetY);
        canvas->redraw();
    }
}

void Application::onCanvasMouseUp(bobcat::Widget* sender, float mx, float my) {
    draggingShape = nullptr;
    canvas->endScribble();
}

void Application::onToolbarChange(bobcat::Widget* sender) {
   static TOOL previousTool = MOUSE;
   TOOL currentTool = toolbar->getTool();

   if(currentTool != previousTool){
    onToolChanged(currentTool);
    previousTool = currentTool;
   }
   ACTION action = toolbar->getAction();

   if(action == CLEAR){
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

void Application::onToolChanged(TOOL newTool){
    // Currently is interfering with the + button - button and bring to back/front
    // On any tool that is not those listed above we change selectedShape and draggingShape to nullptr
     if(newTool == PENCIL ||
        newTool == RECTANGLE ||
        newTool == CIRCLE ||
        newTool == TRIANGLE ||
        newTool == POLYGON ||
        newTool == ERASER){

            selectedShape = nullptr;
            draggingShape = nullptr;
        }
        
    
    
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