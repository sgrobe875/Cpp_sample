#ifndef FINAL_PROJECT_BOAT_H
#define FINAL_PROJECT_BOAT_H

#include <iostream>
#include <time.h>
#include "rect.h"
#include "triangle.h"

#include <vector>
using namespace std;

struct dim {
    double width;
    double height;

    /* Constructors */

    dim(double w, double h);

    /* Overloaded Operator */

    friend std::ostream& operator << (std::ostream& outs, const dim &d);
};

// boat struct
struct boat {
    dim d;
    point2D center;
    vector<unique_ptr<Triangle>> triPieces;
    Rect body;
    vector<float> colorVals;

    boat();
    boat(dim d, vector<float> colorVals);
};

// function to create a boat
boat createBoat (dim dim, double x, double y, vector<float> cv);

// function to move a boat side to side
void moveBoat(unique_ptr<boat> &b, double delta, string direction);

#endif //FINAL_PROJECT_BOAT_H
