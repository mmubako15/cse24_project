#include "Shape.h"
#include <vector>
#include "Point.h"

class Scribble : public Shape {
    std::vector<Point*> points;
    float r, g, b;
    int size;

public:
    Scribble(float r, float g, float b, int size);
    ~Scribble();

    void addPoint(float x, float y);
    void draw() override;
    bool contains(float mx, float my) override;
    void moveTo(float newX, float newY) override;
    float getX() const override;
    float getY() const override;
    void setColor(float r, float g, float b) override;
    void scale(float factor) override;
};