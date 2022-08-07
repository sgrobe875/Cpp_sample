#include "boat.h"

#include <iostream>
#include <time.h>

#include <vector>

using namespace std;

dim::dim(double w, double h) : width(w), height(h) {}


ostream& operator << (ostream& outs, const dim &d) {
    outs << "[" << d.width << ", " << d.height << "]";
    return outs;
}

// constructors
boat::boat():d(0,0){ };
boat::boat(dim d, vector<float> colorVals) : d(d), colorVals(colorVals) {}

// method to create a boat
boat createBoat (dim dim, double x, double y, vector<float> cv) {
    // set dimensions and color
    boat b = boat(dim, cv);
    // set center point for entire boat
    b.center = point2D(x,y);

    // helper variables
    double pieceWidth = b.d.width / 4.0;
    double pieceHeight = b.d.height;

    // create rectangle for body/main part of the boat
    b.body = Rect(dimensions(pieceWidth*2, pieceHeight));
    b.body.setCenter(x, y);

    // create triangles for either side of the main part
    b.triPieces.push_back(make_unique<Triangle>(dims(pieceWidth, pieceHeight), boatLeft, point2D(x - b.d.width * (3/8.0), y)));
    b.triPieces.push_back(make_unique<Triangle>(dims(pieceWidth, pieceHeight), boatRight, point2D(x + b.d.width * (3/8.0), y)));

    // set the color to all three pieces
    b.body.setColor(b.colorVals[0], b.colorVals[1], b.colorVals[2], 1.0f);
    b.triPieces[0]->setColor(b.colorVals[0], b.colorVals[1], b.colorVals[2], 1.0f);
    b.triPieces[1]->setColor(b.colorVals[0], b.colorVals[1], b.colorVals[2], 1.0f);

    // return the boat
    return b;
}

// method to move the boat
void moveBoat(unique_ptr<boat> &b, double delta, string direction) {
    // if moving to the right, increase x
    if (direction == "right") {
        // move all three pieces
        for (int i = 0; i < 2; i++) {
            b->triPieces[i]->moveX(delta * 1);
        }
        b->body.moveX(delta * 1);

    // if moving to the left, decrease x
    }  else {
        // move all three pieces
        for (int i = 0; i < 2; i++) {
            b->triPieces[i]->moveX(delta * -1);
        }
        b->body.moveX(delta * -1);
    }
}