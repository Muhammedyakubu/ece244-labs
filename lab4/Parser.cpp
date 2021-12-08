//
//  parser.cpp
//  Lab4
//
//  Created by Tarek Abdelrahman on 2020-10-25.
//  Copyright © 2020 Tarek Abdelrahman.
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
#include "ShapeNode.h"
#include "GroupNode.h"
#include "ShapeList.h"
#include "GroupList.h"
#define NUM_TYPES 3
#define NUM_KEYWORDS 6
#define MAX_NAMES 1024

// This is a pointer to the groups list
// The list itseld must be allocated
GroupList* gList;

string gNames[MAX_NAMES];
string sNames[MAX_NAMES];
int gCount = 0, sCount = 0;

// ECE244 Student: you may want to add the prototype of
// helper functions you write here

int searchArray(string & val, string* array, int size);
bool inArray(string & val, string* array, int size);
void executeCommand(stringstream & input, int com, GroupList* gList);
ShapeNode* findShapeGroup(GroupNode* & g, string s_name);

int main() {
    // Create the groups list
    gList = new GroupList();
    
    // Create the pool group and add it to the group list
    GroupNode* poolGroup = new GroupNode(keyWordsList[NUM_KEYWORDS-1]);
    gList->insert(poolGroup);
    
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
        lineStream >> command;
        com = searchArray(command, keyWordsList, NUM_KEYWORDS - 1);

        if (command != "")
            executeCommand(lineStream, com, gList);

        command = "";
        
        // Once the command has been processed, prompt for the
        // next command
        cout << "> ";          // Prompt for input
        getline(cin, line);
        
    }  // End input loop until EOF.
    delete gList;
    return 0;
}

int searchArray(string & val, string* array, int size){
    for (int i = 0; i < size ; ++i)
        if (val == array[i]) return i;
    return -1;
}

bool inArray(string & val, string* array, int size){
    return searchArray(val, array, size) + 1;
}

//Modifies targetGroup to contain the address of the group containing
//the Shape name s_name and returns the address of the ShapeNode 
//containing the shape with name s_name
ShapeNode* findShapeGroup(GroupNode* & g, string s_name) {
    ShapeNode* s = nullptr;
    while(g != nullptr) {
        s = g->getShapeList()->find(s_name);
        if (s != nullptr) return s;
        else g = g->getNext();
    }
    return nullptr;
}

void executeCommand(stringstream & input, int com, GroupList* gList) {
    switch (com) {
        case -1:
            cout << "error: invalid command" << endl; break;

        case 0://creating the shape
        {
            string name, type;
            int x_loc, y_loc, x_size, y_size;

            input >> name;
            if(inArray(name, keyWordsList, NUM_KEYWORDS) 
            || inArray(name, shapeTypesList, NUM_TYPES)) {
                cout << "error: invalid name" << endl; break;
            }
            if (inArray(name, gNames, gCount) || inArray(name, sNames, sCount)) {
                cout << "error: name " << name << " exists" << endl;
                break;
            }

            input >> type >> x_loc >> y_loc >> x_size >> y_size;
            Shape* s = new Shape(name, type, x_loc, x_size, y_loc, y_size);
            ShapeNode* sNode = new ShapeNode;
            sNode->setShape(s);
            gList->getHead()->getShapeList()->insert(sNode);
            sNames[sCount++] = name;
            sNode->print();
            break;
        }
        case 1://creating a group
        {
            string name;
            input >> name;
            if(inArray(name, keyWordsList, NUM_KEYWORDS) 
            || inArray(name, shapeTypesList, NUM_TYPES)) {
                cout << "error: invalid name" << endl; break;
            }
            if (inArray(name, gNames, gCount) || inArray(name, sNames, sCount)) {
                cout << "error: name " << name << " exists" << endl;
                break;
            }

            //input is good
            GroupNode* gNode = new GroupNode(name);
            gList->insert(gNode);
            gNames[gCount++] = name;
            cout << gNode->getName() << ": group" << endl;
            break;
        }
        case 2://moving shapes between groups
        {
            string g_name, s_name;
            input >> s_name >> g_name;
            if(inArray(g_name, keyWordsList, NUM_KEYWORDS) 
            || inArray(g_name, shapeTypesList, NUM_TYPES)
            || inArray(s_name, keyWordsList, NUM_KEYWORDS) 
            || inArray(s_name, shapeTypesList, NUM_TYPES)) {
                cout << "error: invalid name" << endl; 
                break;
            }
            if(!inArray(s_name, sNames, sCount)) {
                cout << "error: shape " << s_name << " not found" << endl; 
                break;
            }
            else if (!inArray(g_name, gNames, gCount)) {
                cout << "error: group " << g_name << " not found" << endl; 
                break;
            }

            //All input is good
            //Make a copy of the shape to be moved

            //First find the group that the shape belongs to & the shape
            GroupNode* source_gNode = gList->getHead();
            ShapeNode* source_sNode = findShapeGroup(source_gNode, s_name);

            ShapeNode* dest_sNode = new ShapeNode;
            //copying the target shape into the new shape;
            dest_sNode->setShape(new Shape(*(source_sNode->getShape())));

            //deleting the source shape


            //insert the new shapenode into the destination gNode
            GroupNode* dest_gNode = gList->getHead();
            while (dest_gNode != nullptr){
                if (dest_gNode->getName() == g_name) break;
                else dest_gNode = dest_gNode->getNext();
            }
            
            dest_gNode->getShapeList()->insert(dest_sNode);

            //delete the source shapeNode
            source_gNode->getShapeList()->remove(s_name);

            //output message
            cout << "moved " << s_name << " to " << g_name << endl;
            break;
        }
        case 3://delete a shape or group
        {
            string name;
            input >> name;
            if(inArray(name, keyWordsList, NUM_KEYWORDS) 
            || inArray(name, shapeTypesList, NUM_TYPES)) {
                cout << "error: invalid name" << endl; break;
            }
            //deleting a shape
            if(inArray(name,  sNames, sCount)){
                GroupNode* gNode = gList->getHead();
                findShapeGroup(gNode, name);
                gNode->getShapeList()->remove(name);
                sNames[searchArray(name, sNames, sCount)] = "";
                cout << name << ": deleted" << endl;
            } 
            //deleting a group
            else if(inArray(name, gNames, gCount)){
                //first have to move the shapeNodes from the target gNode
                //to the pool group
                GroupNode* gNode = gList->getHead();
                while (gNode != nullptr){
                    if (gNode->getName() == name) break; 
                    else gNode = gNode->getNext();
                }
                //once the target gNode is found, we loop through each sNode in its sList and insert a copy into pool
                ShapeNode* sNode_ptr = gNode->getShapeList()->getHead();
                while(sNode_ptr != nullptr){
                    ShapeNode* sNode = new ShapeNode;
                    sNode->setShape(new Shape(*(sNode_ptr->getShape())));
                    gList->getHead()->getShapeList()->insert(sNode);
                    sNode_ptr = sNode_ptr->getNext();
                }

                //deleting the groupnode
                gList->remove(name);
                gNames[searchArray(name, gNames, gCount)] = "";
                cout << name << ": deleted" << endl;
            }
            else {
                cout << "error: shape " << name << " not found" << endl;
                break;
            }
            break;
        }
        case 4://draw all shapes and groups
        {
            cout << "drawing:" << endl;
            gList->print();
            break;
        }
    }
}