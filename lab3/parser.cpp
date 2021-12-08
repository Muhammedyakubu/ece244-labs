//
//  parser.cpp
//  lab3
//
//  Modified by Tarek Abdelrahman on 2020-10-04.
//  Created by Tarek Abdelrahman on 2018-08-25.
//  Copyright © 2018-2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.


#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "globals.h"
#include "Shape.h"

// This is the shape array, to be dynamically allocated
Shape** shapesArray;

// The number of shapes in the database, to be incremented 
int shapeCount = 0;

// The value of the argument to the maxShapes command
int max_shapes;

// The array containing names of created shapes
string *namesArray;

// ECE244 Student: you may want to add the prototype of
// helper functions you write here
int hashCmd(string & command);
void Error(int i);
int inArray(string & val, string* array, int size);
int makeShapesArray(stringstream & input);
int createShape(stringstream & input);
int moveShape(stringstream & input);
int rotateShape(stringstream & input);
int drawShape(stringstream & input);
int deleteShape(stringstream & input);

int main() {

    string line;
    string command;
    int com;
    
    cout << "> ";         // Prompt for input
    getline(cin, line);    // Get a line from standard input

    while ( !cin.eof () ) {
        // Put the line in a linestream for parsing
        // Making a new sstream for each line so flags etc. are cleared
        stringstream lineStream (line);
        
        // Read from string stream into the command
        // The only way this can fail is if the eof is encountered
        lineStream >> command;// remember to error check for if input here is valid
        com = hashCmd(command);

        switch (com) {
            case -1:// if invalid command
                Error(1);//error message
                break;

            case 1: //maxshapes
                Error(makeShapesArray(lineStream));
                break;

            case 2://create shape
                Error(createShape(lineStream));
                break;

            case 3://move shape
                Error(moveShape(lineStream));
                break;

            case 4://rotate
                Error(rotateShape(lineStream));
                break;
            
            case 5://draw
                Error(drawShape(lineStream));
                break;

            case 6://delete
                Error(deleteShape(lineStream));
                break;




            
        }
        // Check for the command and act accordingly
        // ECE244 Student: Insert your code here
        command = "";
        
        
        
        // Once the command has been processed, prompt for the
        // next command
        cout << "> ";          // Prompt for input
        getline(cin, line);
        
    }  // End input loop until EOF.
    
    return 0;
}

int hashCmd(string & command){
    for(int i = 0; i < 7; ++i){
        if(command == keyWordsList[i])
            return i;
    }
    return (-1);
}

void Error(int i){
    switch (i) {
        case 1:
            cout << "Error: invalid command" << endl;
            break;
        case 2:
            cout << "Error: invalid argument" << endl;
            break;
        case 3:
            cout << "Error: invalid shape name" << endl;
            break;
        case 5:
            cout << "Error: shape name not found" << endl;
            break;
        case 6:
            cout << "Error: invalid shape type" << endl;
            break;
        case 7:
            cout << "Error: invalid value" << endl;
            break;
        case 8:
            cout << "Error: too many arguments" << endl;
            break;
        case 9:
            cout << "Error: too few arguments" << endl;
            break;
        case 10:
            cout << "Error: shape array is full" << endl;
            break;
    }
}

int makeShapesArray(stringstream & input){
    string extra;
    int old_max_shapes = max_shapes;

    input >> max_shapes;
    if(input.fail() && input.eof())
        return 9;
    if(input.fail() || (input.peek() != 32 && input.peek() != EOF))
        return 2;
    if(max_shapes < 0)
        return 7;

    //at this point I know max_shapes input is good but now I check that it is the last input on the line
    input >> extra;
    if(extra != "" || !input.eof())
        return 8;

    if(old_max_shapes){//if there was a pre-existing array then I want to delete it so it does not cause a memory leak
        for(int i = 0; i < shapeCount; ++i){
            if(shapesArray[i] != nullptr) {delete shapesArray[i]; shapesArray[i] = nullptr;}
        }
        delete [] shapesArray; shapesArray = nullptr;
        delete [] namesArray;
        shapeCount = 0;
    }

    shapesArray = new Shape* [max_shapes];
    namesArray = new string[max_shapes];
    cout << "New database: max shapes is " << max_shapes << endl;

    return 0;
}

int createShape(stringstream & input){
    if(input.eof())
        return 9;

    string name, type, extra;
    int x_loc, y_loc, x_size, y_size;

    input >> name;
    if(input.fail() && input.eof())
        return 9;
    if(input.fail() || (input.peek() != 32 && input.peek() != EOF))
        return 2;
    if((inArray(name, keyWordsList, 7) + 1) || (inArray(name, shapeTypesList, 4) + 1))
        return(3);
    if((inArray(name, namesArray, shapeCount) + 1)){
        cout << "Error: shape " << name << " exists" << endl;  //Error 4
        return(0);
    }

    input >> type;
    if(input.fail() && input.eof())
        return 9;
    if(input.fail() || (input.peek() != 32 && input.peek() != EOF))
        return 2;
    if(!(inArray(type, shapeTypesList, 4) + 1))
        return(6);

    input >> x_loc;
    if(input.fail() && input.eof())
        return 9;
    if(input.fail() || (input.peek() != 32 && input.peek() != EOF))
        return 2;
    if(x_loc < 0)
        return(7);

    input >> y_loc;
    if(input.fail() && input.eof())
        return 9;
    if(input.fail() || (input.peek() != 32 && input.peek() != EOF))
        return 2;
    if(y_loc < 0)
        return(7);

    input >> x_size;
    if(input.fail() && input.eof())
        return 9;
    if(input.fail() || (input.peek() != 32 && input.peek() != EOF))
        return 2;
    if(x_size < 0)
        return(7);

    input >> y_size;
    if(input.fail() && input.eof())
        return 9;
    if(input.fail() || (input.peek() != 32 && input.peek() != EOF))
        return 2;
    if(y_size < 0 || (type == "circle" && x_size != y_size))
        return(7);

    input >> extra;
    if(extra != "" || !input.eof())     //if not EOF here then too many arguments
        return 8;

    if(shapeCount == max_shapes)
        return 10;

    // at this point, all input is good
    // create Shape object and input data
    shapesArray[shapeCount] = new Shape(name, type, x_loc, x_size, y_loc, y_size);
    namesArray[shapeCount] = name;
    cout << "Created ";
    shapesArray[shapeCount]->draw();
    shapeCount++;

    return 0;
}

int inArray(string & val, string* array, int size){
    for (int i = 0; i < size ; ++i)
        if (val == array[i]) return i;
    return -1;
}

int moveShape(stringstream & input){
    string name, extra;
    int x_loc, y_loc;

    input >> name;
    if(input.fail() && input.eof())
        return 9;
    if(input.fail() || (input.peek() != 32 && input.peek() != EOF))
        return 2;
    if((inArray(name, keyWordsList, 7) + 1) || (inArray(name, shapeTypesList, 4) + 1))
        return(3);
    if(!(inArray(name, namesArray, shapeCount) + 1)){
        cout << "Error: shape " << name << " not found" << endl;
        return(0);
    }


    input >> x_loc;
    if(input.fail() && input.eof())
        return 9;
    if(input.fail() || (input.peek() != 32 && input.peek() != EOF))
        return 2;
    if(x_loc < 0)
        return(7);

    input >> y_loc;
    if(input.fail() && input.eof())
        return 9;
    if(input.fail() || (input.peek() != 32 && input.peek() != EOF))
        return 2;
    if(y_loc < 0)
        return(7);

    input >> extra;
    if(extra != "" || !input.eof())
        return 8;
    
    //All input is good
    int index = inArray(name, namesArray, shapeCount);
    shapesArray[index]->setXlocation(x_loc);
    shapesArray[index]->setYlocation(y_loc);
    cout << "Moved " << name << " to " << x_loc << " " << y_loc << endl;
    
    return 0;
}

int rotateShape(stringstream & input){
    string name, extra;
    int angle;

    input >> name;
    if(input.fail() && input.eof())
        return 9;
    if(input.fail() || (input.peek() != 32 && input.peek() != EOF))
        return 2;
    if((inArray(name, keyWordsList, 7) + 1) || (inArray(name, shapeTypesList, 4) + 1))
        return(3);
    if(!(inArray(name, namesArray, shapeCount) + 1)){
        cout << "Error: shape " << name << " not found" << endl;   //Error 5
        return(0);
    }

    input >> angle;
    if(input.fail() && input.eof())
        return 9;
    if(input.fail() || (input.peek() != 32 && input.peek() != EOF))
        return 2;
    if(angle < 0 || angle > 360)
        return 7;

    input >> extra;
    if(extra != "" || !input.eof())
        return 8;

    //All input is good, rotate shape
    int index = inArray(name, namesArray, shapeCount);
    shapesArray[index]->setRotate(angle);
    cout << "Rotated " << name << " by " << angle << " degrees" << endl;
    
    return 0;
}

int drawShape(stringstream & input){
    string name, extra;

    input >> name;
    if(input.fail() && input.eof())
        return 9;
    if(input.fail() || (input.peek() != 32 && input.peek() != EOF))
        return 2;
    if((name != "all" && (inArray(name, keyWordsList, 7) + 1)) || (inArray(name, shapeTypesList, 4) + 1))
        return(3);
    if(name != "all" && !(inArray(name, namesArray, shapeCount) + 1)){
        cout << "Error: shape " << name << " not found" << endl;   //Error 5
        return(0);
    }

    input >> extra;
    if(extra != "" || !input.eof())
        return 8;
    
    if(name == "all"){
        cout << "Drew all shapes" << endl;
        for(int i = 0; i < shapeCount; ++i){
            if(shapesArray[i] != nullptr) shapesArray[i]->draw();
        }
    }
    else {
        cout << "Drew ";
        shapesArray[inArray(name, namesArray, shapeCount)]->draw();
    }
    return 0;
}

int deleteShape(stringstream & input){
    string name, extra;

    input >> name;
    if(input.fail() && input.eof())
        return 9;
    if(input.fail() || (input.peek() != 32 && input.peek() != EOF))
        return 2;
    if((name != "all" && (inArray(name, keyWordsList, 7) + 1)) || (inArray(name, shapeTypesList, 4) + 1))
        return(3);
    if(name != "all" && !(inArray(name, namesArray, shapeCount) + 1)){
        cout << "Error: shape " << name << " not found" << endl;   //Error 5
        return(0);
    }

    input >> extra;
    if(extra != "" || !input.eof())
        return 8;

    if(name == "all"){
        for(int i = 0; i < shapeCount; ++i){
            if(shapesArray[i] != nullptr) {delete shapesArray[i]; shapesArray[i] = nullptr;}
        }
        shapeCount = 0;
        cout << "Deleted: all shapes" << endl;
    }
    else {
        int index = inArray(name, namesArray, shapeCount);
        delete shapesArray[index]; shapesArray[index] = nullptr;
        namesArray[index] = "";
        cout << "Deleted shape " << name << endl;
    }

    return 0;
}