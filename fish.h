#ifndef FINAL_PROJECT_FISH_H
#define FINAL_PROJECT_FISH_H

#include <iostream>
#include <time.h>
#include "rect.h"
#include "triangle.h"

#include <vector>
using namespace std;

struct ds {
    double width;
    double height;

    /* Constructors */

    //ds();
    ds(double w, double h);

    /* Overloaded Operator */

    friend std::ostream& operator << (std::ostream& outs, const ds &d);
};

enum fishOrientation {fishRight, fishLeft};

// fish struct
struct fish {
    ds d;
    fishOrientation oriented;
    point2D center;
    vector<unique_ptr<Triangle>> triPieces;
    Rect body;
    vector<float> colorVals;

    fish();
    fish(ds d, fishOrientation oriented, vector<float> colorVals);
};

// function to create a fish
fish createFish (ds dim, fishOrientation o, double x, double y, vector<float> cv);

// functions to move fish
void moveFish(fish &f, double delta);
void moveFish(unique_ptr<fish> &f, double delta);

// reset a fish to the side of the screen
void resetFish(unique_ptr<fish> &f);

#endif //FINAL_PROJECT_FISH_H
