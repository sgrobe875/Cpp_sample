#include "fish.h"

#include <iostream>
#include <time.h>

#include <vector>

using namespace std;

ds::ds(double w, double h) : width(w), height(h) {}


ostream& operator << (ostream& outs, const ds &d) {
    outs << "[" << d.width << ", " << d.height << "]";
    return outs;
}

// constructors
fish::fish():d(0,0){ };
fish::fish(ds d, fishOrientation oriented, vector<float> colorVals) : d(d), oriented(oriented), colorVals(colorVals) {}

// method to create a fish
fish createFish (ds dim, fishOrientation o, double x, double y, vector<float> cv) {
    // initialize dimensions, orientatino, and color
    fish f = fish(dim, o, cv);
    // set the center of the whole fish
    f.center = point2D(x,y);

    // helper variables
    double pieceWidth = f.d.width / 4;
    double pieceHeight = f.d.height;
    Triangle curr1, curr2, curr3;

    // if fish is swimming to the left
    if (f.oriented == fishLeft) {
        // head
        curr1 = Triangle(dims(pieceWidth, pieceHeight), tailRight, point2D(x - (f.d.width * (1/8.0)), y));
        f.triPieces.push_back(make_unique<Triangle>(curr1));

        // rear
        curr2 = Triangle(dims(pieceWidth, pieceHeight), tailLeft);
        curr2.setCenterY(y);
        curr2.setCenterX(x - (f.d.width * (3/8.0)));
        f.triPieces.push_back(make_unique<Triangle>(curr2));

        // tail
        curr3 = Triangle(dims(pieceWidth, pieceHeight), tailRight);
        curr3.setCenterY(y);
        curr3.setCenterX(x - (f.d.width * (7/8.0)));
        f.triPieces.push_back(make_unique<Triangle>(curr3));

        // body
        f.body = Rect(dimensions(pieceWidth, pieceHeight));
        f.body.setCenterY(y);
        f.body.setCenterX(f.center.x - f.d.width * (5/8.0));

    // if swimming to the right
    } else {
        // body
        f.body = Rect(dimensions(pieceWidth, pieceHeight));
        f.body.setCenterY(y);
        f.body.setCenterX(f.center.x - f.d.width * (3/8.0));

        // rear
        curr1 = Triangle(dims(pieceWidth, pieceHeight), tailRight);
        curr1.setCenterY(y);
        curr1.setCenterX(x - (f.d.width * (5/8.0)));
        f.triPieces.push_back(make_unique<Triangle>(curr1));

        // head
        curr2 = Triangle(dims(pieceWidth, pieceHeight), tailLeft);
        curr2.setCenterY(y);
        curr2.setCenterX(x - (f.d.width * (7/8.0)));
        f.triPieces.push_back(make_unique<Triangle>(curr2));

        // tail
        curr3 = Triangle(dims(pieceWidth, pieceHeight), tailLeft);
        curr3.setCenterY(y);
        curr3.setCenterX(x - (f.d.width * (1/8.0)));
        f.triPieces.push_back(make_unique<Triangle>(curr3));
    }

    // set color of all four pieces
    f.body.setColor(f.colorVals[0], f.colorVals[1], f.colorVals[2], 1.0f);
    f.triPieces[0]->setColor(f.colorVals[0], f.colorVals[1], f.colorVals[2], 1.0f);
    f.triPieces[1]->setColor(f.colorVals[0], f.colorVals[1], f.colorVals[2], 1.0f);
    f.triPieces[2]->setColor(f.colorVals[0], f.colorVals[1], f.colorVals[2], 1.0f);

    // return the fish
    return f;
}

// method to move fish
void moveFish(fish &f, double delta) {
    double oldCenterX = f.center.x;
    double newCenterX;

    // if moving to the left, lower x value
    if (f.oriented == fishLeft) {
        for (int i = 0; i < 3; i++) {
            f.triPieces[i]->moveX(delta * -1);
        }
        f.body.moveX(delta * -1);
    // if moving to the right, raise x value
    } else {
        for (int i = 0; i < 3; i++) {
            f.triPieces[i]->moveX(delta * 1);
        }
        f.body.moveX(delta * 1);
    }
}

// alternate method of moving fish using a pointer to the fish
void moveFish(unique_ptr<fish> &f, double delta) {
    double oldCenterX = f->center.x;
    double newCenterX;
    // as above, if moving to the left, decrease x
    if (f->oriented == fishLeft) {
        for (int i = 0; i < 3; i++) {
            f->triPieces[i]->moveX(delta * -1);
        }
        f->body.moveX(delta * -1);
    // if moving right, increase x
    } else {
        for (int i = 0; i < 3; i++) {
            f->triPieces[i]->moveX(delta * 1);
        }
        f->body.moveX(delta * 1);
    }
}

// reset the fish to off the screen
void resetFish(unique_ptr<fish> &f) {
    double oldCenterX = f->center.x;
    double newCenterX;
    // if swimming to the left, move to the right side of the screen
    if (f->oriented == fishLeft) {
        f->center = point2D(1520, f->center.y);
    // if swimming to the right, move to the left side of the screen
    } else {
        f->center = point2D(-20, f->center.y);
    }
    // return the updated fish
    *f = createFish(f->d, f->oriented, f->center.x, f->center.y, f->colorVals);
}