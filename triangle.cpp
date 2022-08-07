#include "graphics.h"
#include "triangle.h"
#include <iostream>
using namespace std;

/********************* dims Struct ********************/

dims::dims() : width(0), height(0) {}

dims::dims(double w, double h) : width(w), height(h) {}

ostream& operator << (ostream& outs, const dims &d) {
    outs << "[" << d.width << ", " << d.height << "]";
    return outs;
}

// constructors
Triangle::Triangle() : Shape(), size({0, 0}) {
}

Triangle::Triangle(dims size, orientation o) : Shape() {
    setSize(size);
    setOrientation(o);
}

Triangle::Triangle(dims size, orientation o, point2D p) {
    setSize(size);
    setOrientation(o);
    setCenter(p);
}

// getters
dims Triangle::getSize() const {
    return size;
}

double Triangle::getWidth() const {
    return size.width;
}

double Triangle::getHeight() const {
    return size.height;
}

double Triangle::getLeftX() const {
    return center.x - (size.width / 2.0);
}

double Triangle::getRightX() const {
    return center.x + (size.width / 2.0);
}

double Triangle::getTopY() const {
    return center.y - (size.height / 2.0);
}

double Triangle::getBottomY() const {
    return center.y + (size.height / 2.0);
}

orientation Triangle::getOrientation() const {
    return oriented;
}

// setters
void Triangle::setSize(dims size) {
    if (size.width >= 0 && size.height >= 0) {
        this->size = size;
    }
}

void Triangle::setSize(double width, double height) {
    setSize({width, height});
}

void Triangle::setWidth(double width) {
    setSize({width, size.height});
}

void Triangle::setHeight(double height) {
    setSize({size.width, height});
}

void Triangle::setOrientation(orientation o) {
    oriented = o;
}

void Triangle::changeSize(double deltaWidth, double deltaHeight) {
    setSize({size.width + deltaWidth, size.height + deltaHeight});
}

void Triangle::changeWidth(double delta) {
    setSize({size.width + delta, size.height});
}

void Triangle::changeHeight(double delta) {
    setSize({size.width, size.height + delta});
}

// draw method
void Triangle::draw() const {
    // set color
    glColor3f(fill.red, fill.green, fill.blue);
    glBegin(GL_TRIANGLES);

    // helper variables for dimensionality
    double midHeight = size.height / 2;
    double midWidth = size.width / 2;
    double currX, currY;

    // draw triangle differently depending on orientation (enumerated type)
    switch (oriented) {
        // isosceles pointing to the left (fish tail on the right side)
        case tailRight:
            // leftmost point
            currX = getCenterX() - midWidth;
            currY = getCenterY();
            glVertex2f(currX, currY);

            // right & top point
            currX = getCenterX() + midWidth;
            currY = getCenterY() - midHeight;
            glVertex2f(currX, currY);

            // right & bottom point
            currY = getCenterY() + midHeight;
            glVertex2f(currX, currY);
            break;
        // isosceles pointing to the right (fish tail on the left side)
        case tailLeft:
            // rightmost point
            currX = getCenterX() + midWidth;
            currY = getCenterY();
            glVertex2f(currX, currY);

            // right & top point
            currX = getCenterX() - midWidth;
            currY = getCenterY() - midHeight;
            glVertex2f(currX, currY);

            // right & bottom point
            currY = getCenterY() + midHeight;
            glVertex2f(currX, currY);
            break;
        // right triangle pointing right (right side of boat)
        case boatRight:
            // rightmost point
            currX = getCenterX() + midWidth;
            currY = getCenterY() - midHeight;
            glVertex2f(currX, currY);

            // left & top point
            currX = getCenterX() - midWidth;
            glVertex2f(currX, currY);

            // left & bottom point
            currY = getCenterY() + midHeight;
            glVertex2f(currX, currY);
            break;
        // right triangle pointing left (left side of boat)
        case boatLeft:
            // leftmost point
            currX = getCenterX() - midWidth;
            currY = getCenterY() - midHeight;
            glVertex2f(currX, currY);

            // right & top point
            currX = getCenterX() + midWidth;
            glVertex2f(currX, currY);

            // right & bottom point
            currY = getCenterY() + midHeight;
            glVertex2f(currX, currY);
            break;
        // right triangle pointing right (left side of hook)
        case hookLeft:
            // rightmost point
            currX = getCenterX() + midWidth;
            currY = getCenterY() + midHeight;
            glVertex2f(currX, currY);

            // left & bottom point
            currX = getCenterX() - midWidth;
            glVertex2f(currX, currY);

            // left & top point
            currY = getCenterY() - midHeight;
            glVertex2f(currX, currY);
            break;
        // right triangle pointing left (right side of hook)
        case hookRight:
            // leftmost point
            currX = getCenterX() - midWidth;
            currY = getCenterY() + midHeight;
            glVertex2f(currX, currY);

            // right & bottom point
            currX = getCenterX() + midWidth;
            glVertex2f(currX, currY);

            // right & top point
            currY = getCenterY() - midHeight;
            glVertex2f(currX, currY);
            break;
    }

    // end
    glEnd();
}