#include "graphics.h"
#include "rect.h"
#include <iostream>
using namespace std;

/********************* Dimensions Struct ********************/

dimensions::dimensions() : width(0), height(0) {}

dimensions::dimensions(double w, double h) : width(w), height(h) {}

ostream& operator << (ostream& outs, const dimensions &d) {
    outs << "[" << d.width << ", " << d.height << "]";
    return outs;
}

// constructors
Rect::Rect() : Shape() {}

Rect::Rect(double x, double y) : Shape(x, y), size({0, 0}) {
}

Rect::Rect(dimensions(s)) : Shape() {
    setSize(s);
}

// getters
dimensions Rect::getSize() const {
    return size;
}

double Rect::getWidth() const {
    return size.width;
}

double Rect::getHeight() const {
    return size.height;
}

double Rect::getLeftX() const {
    return center.x - (size.width / 2.0);
}

double Rect::getRightX() const {
    return center.x + (size.width / 2.0);
}

double Rect::getTopY() const {
    return center.y - (size.height / 2.0);
}

double Rect::getBottomY() const {
    return center.y + (size.height / 2.0);
}

// setters
void Rect::setSize(dimensions size) {
    if (size.width >= 0 && size.height >= 0) {
        this->size = size;
    }
}

void Rect::setSize(double width, double height) {
    setSize({width, height});
}

void Rect::setWidth(double width) {
    setSize({width, size.height});
}

void Rect::setHeight(double height) {
    setSize({size.width, height});
}

void Rect::changeSize(double deltaWidth, double deltaHeight) {
    setSize({size.width + deltaWidth, size.height + deltaHeight});
}

void Rect::changeWidth(double delta) {
    setSize({size.width + delta, size.height});
}

void Rect::changeHeight(double delta) {
    setSize({size.width, size.height + delta});
}

// check if rectangles are overlapping
bool Rect::isOverlapping(const Rect &r) const {
    // There are only two cases when rectangles are *not* overlapping:
    // 1. when one is to the left of the other
    if ((getLeftX() > r.getRightX() || getRightX() < r.getLeftX())) {
        return false;
    }

    // 2. when one is above the other
    if ((getBottomY() < r.getTopY() || getTopY() > r.getBottomY())) {
        return false;
    }

    return true; // placeholder value for compilation
}

// draw method
void Rect::draw() const {
    // Don't forget to set the color to the fill field
    glColor3f(fill.red, fill.green, fill.blue);
    glBegin(GL_QUADS);

    // draw points
    glVertex2i(getLeftX(), getTopY());
    glVertex2i(getLeftX(), getBottomY());
    glVertex2i(getRightX(), getBottomY());
    glVertex2i(getRightX(), getTopY());

    // end
    glEnd();
}