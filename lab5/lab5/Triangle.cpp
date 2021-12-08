//
//  Triangle.cpp
//  Lab5
//
//  Created by Tarek Abdelrahman on 2020-11-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student: Write the implementation of the class Rectangle here

#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
using namespace std;

#include "Shape.h"
#include "Triangle.h"

Triangle::Triangle(string n, float x1, float y1, float x2, float y2, float x3, float y3):Shape(n, (x1+x2+x3)/3, (y1+y2+y3)/3) {
    x_loc1 = x1;
    x_loc2 = x2;
    x_loc3 = x3;
    y_loc1 = y1;
    y_loc2 = y2;
    y_loc3 = y3;
}

// Destructor
Triangle::~Triangle() {

}

// Accessor
float Triangle::getX1() const {return x_loc1;}
float Triangle::getX2() const {return x_loc2;}
float Triangle::getX3() const {return x_loc3;}
float Triangle::getY1() const {return y_loc1;}
float Triangle::getY2() const {return y_loc2;}
float Triangle::getY3() const {return y_loc3;}

// Mutator
void Triangle::setX1(float x1) {x_loc1 = x1;}
void Triangle::setY1(float y1) {y_loc1 = y1;}
void Triangle::setX2(float x2) {x_loc2 = x2;}
void Triangle::setY2(float y2) {y_loc2 = y2;}
void Triangle::setX3(float x3) {x_loc3 = x3;}
void Triangle::setY3(float y3) {y_loc3 = y3;}

// Utility methods
void Triangle::draw() const{
    // Set floating point printing to fixed point with 2 decimals
    cout << std::fixed;
    cout << std::setprecision(2);
    
    // Print the information
    cout << "triangle: " << name << " "
         << x_centre << " " << y_centre <<
          " " << x_loc1 << " " << y_loc1
         << " " << x_loc2 << " " << y_loc2 
         << " " << x_loc3 << " " << y_loc3 
         << " " << computeArea() << endl;
}     // Draws the Triangle; for the assignment it
                            // prints the information of the Triangle

float dist(float x1, float x2, float y1, float y2) {
    return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}

float Triangle::computeArea() const {
    float side1 = dist(x_loc1, x_loc2, y_loc1, y_loc2);
    float side2 = dist(x_loc2, x_loc3, y_loc2, y_loc3);
    float side3 = dist(x_loc3, x_loc1, y_loc3, y_loc1);
    float s = (side1 + side2 + side3)/2;
    float area = sqrt(s * (s - side1) * (s - side2) * (s - side3));
    return area;
}   // Computes the area of the Triangle

Shape* Triangle::clone() const {
    return (new Triangle(*this));
}  // Clones the object
