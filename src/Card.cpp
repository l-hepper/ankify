#include "Card.h"

#include <iostream>

using namespace std;

// constructs a new card consisting of a front and back
Card::Card(const string& front, const string& back) {
    this->front = front;
    this->back = back;
}

string Card::getFront() const{
    return front;
}

string Card::getBack() const{
    return back;
}