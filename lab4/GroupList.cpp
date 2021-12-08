//
//  GroupList.cpp
//  Lab4
//
//  Created by Tarek Abdelrahman on 2020-10-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student:
//  Write the implementation (and only the implementation) of the GroupList class below
#include <iostream>
#include <string>
#include "GroupList.h"

    GroupList::GroupList() {head = nullptr;}                      // sets head to nullptr
    GroupList::~GroupList() {
        GroupNode* ptr = nullptr;
        while (head != nullptr) {
            ptr = head;
            head = head->getNext();
            delete ptr;
        }
    }                     // deletes all list nodes, including all the ShapeList
                                      // attached to each GroupNode
    
    GroupNode* GroupList::getHead() const {return head;}       // returns the head pointer

    void GroupList::setHead(GroupNode* ptr) {head = ptr;}     // sets the head pointer to ptr

    void GroupList::insert(GroupNode* s) {
        if (head == nullptr) {
            head = s;
            s->setNext(nullptr);
        }
        else {
            GroupNode* ptr = head;
            while(ptr->getNext() != nullptr) ptr = ptr->getNext();
            ptr->setNext(s);
            s->setNext(nullptr);
        }
        
    }        // inserts the node pointed to by s at the end of the list

    GroupNode* GroupList::remove(string name) {
        if(head == nullptr) return nullptr;
        GroupNode* tptr = head;
        GroupNode* pptr = nullptr;
        while (tptr != nullptr) {
            if (tptr->getName() == name) break;
            pptr = tptr;
            tptr = tptr->getNext();
        }
        if (tptr == nullptr) return nullptr;
        if (tptr == head) {
            head = head->getNext(); delete tptr; return tptr; 
        }
        pptr->setNext(tptr->getNext());
        delete tptr; return tptr;
    }   // removes the group with the name "name" from the list
                                      // and returns a pointer to the removed GroupNode
                                      // returns nullptr is name is not found on list
    void GroupList::print() const {
        GroupNode* ptr = head;
        while (ptr != nullptr) {
            ptr->print();
            ptr = ptr->getNext();
        }
    }               // prints the list, one GroupNode at a time


