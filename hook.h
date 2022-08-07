#ifndef FINAL_PROJECT_HOOK_H
#define FINAL_PROJECT_HOOK_H

#include <iostream>
#include <time.h>
#include "rect.h"
#include "triangle.h"

#include <vector>
using namespace std;

struct dimens {
    double width;
    double height;

    /* Constructors */

    dimens(double w, double h);

    /* Overloaded Operator */

    friend std::ostream& operator << (std::ostream& outs, const dimens &d);
};

// hook struct
struct hook {
    dimens d;
    point2D center;
    vector<unique_ptr<Triangle>> triPieces;
    Rect rectanglePiece;

    // constructors
    hook();
    hook(dimens d);

};

// function to create a hook
hook createHook (dimens dim, double x, double y);


#endif //FINAL_PROJECT_HOOK_H