#ifndef GRAPHICSEXAMPLES_TRI_H
#define GRAPHICSEXAMPLES_TRI_H

#include "shape.h"
//#include "rect.h"

struct dims {
    double width;
    double height;

    /* Constructors */

    dims();
    dims(double w, double h);

    /* Overloaded Operator */

    friend std::ostream& operator << (std::ostream& outs, const dims &d);
};

// enumerated type for types of triangles
enum orientation {tailRight, tailLeft, boatRight, boatLeft, hookRight, hookLeft};

class Triangle : public Shape {
private:
    dims size;
    orientation oriented;
public:
    /* Constructors */
    Triangle();
    Triangle(dims size, orientation o);
    Triangle(dims size, orientation o, point2D p);


    /* Destructor */
    virtual ~Triangle() = default;

    /* Getters */
    dims getSize() const;
    double getWidth() const;
    double getHeight() const;
    orientation getOrientation() const;

    double getLeftX() const override;
    double getRightX() const override;
    double getTopY() const override;
    double getBottomY() const override;


    /* Setters */
    void setSize(dims size);
    void setSize(double width, double height);
    void setWidth(double width);
    void setHeight(double height);
    void setOrientation(orientation o);
    void changeSize(double deltaWidth, double deltaHeight);
    void changeWidth(double delta);
    void changeHeight(double delta);


    /* Draw */
    void draw() const override;

};


#endif //GRAPHICSEXAMPLES_TRI_H
