#include "hook.h"

#include <iostream>
#include <time.h>

#include <vector>

using namespace std;

dimens::dimens(double w, double h) : width(w), height(h) {}


ostream& operator << (ostream& outs, const dimens &d) {
    outs << "[" << d.width << ", " << d.height << "]";
    return outs;
}

// constructors
hook::hook():d(0,0){ };
hook::hook(dimens d) : d(d) {}

// function to create a hook
hook createHook (dimens d, double x, double y) {
    hook h = hook(d);
    h.center = point2D(x,y);

    // helper variables
    double pieceWidth = h.d.width / 3.0;
    double pieceHeight = h.d.height / 2.0;

    // create the rectangular piece, the main part of the hook
    h.rectanglePiece = Rect(dimensions(pieceWidth, h.d.height));
    h.rectanglePiece.setCenter(x - d.width * (1/6.0),  y);

    // two triangle pieces to make the hook part
    h.triPieces.push_back(make_unique<Triangle>(dims(pieceWidth, pieceHeight), hookLeft, point2D(x, y + (pieceHeight/2.0))));
    h.triPieces.push_back(make_unique<Triangle>(dims(pieceWidth, pieceHeight), hookRight, point2D(x + d.width * (1/6.0), y + (pieceHeight/2.0))));

    // change the color of all three pieces
    h.rectanglePiece.setColor(125/255.0, 125/255.0, 125/255.0, 1.0f);
    h.triPieces[0]->setColor(125/255.0, 125/255.0, 125/255.0, 1.0f);
    h.triPieces[1]->setColor(125/255.0, 125/255.0, 125/255.0, 1.0f);

    // return the hook
    return h;
}