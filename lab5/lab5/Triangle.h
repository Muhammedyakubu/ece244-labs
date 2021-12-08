//
//  Triangle.h
//  Lab5
//
//  Created by Tarek Abdelrahman on 2020-11-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

#ifndef Triangle_h
#define Triangle_h

#include <iostream>
#include <string>
using namespace std;


#include "Shape.h"

class Triangle : Shape {
private:
    float x_loc1, y_loc1;                  
    float x_loc2, y_loc2;
    float x_loc3, y_loc3;

public:
    // Constructor
    Triangle (string n, float x1, float y1, float x2, float y2, float x3, float y3);
    
    // Destructor
    virtual ~Triangle();
    
    // Accessor
    float getX1() const;
    float getY1() const;
    float getX2() const;
    float getY2() const;
    float getX3() const;
    float getY3() const;

    // Mutator
    void setX1(float x1); 
    void setY1(float y1);
    void setX2(float x2); 
    void setY2(float y2);
    void setX3(float x3);
    void setY3(float y3);

    // Utility methods
    virtual void draw() const;     // Draws the Triangle; for the assignment it
                                   // prints the information of the Triangle
    
    virtual float computeArea() const;   // Computes the area of the Triangle
    
    virtual Shape* clone() const;  // Clones the object
};

#endif /* Triangle_h */


