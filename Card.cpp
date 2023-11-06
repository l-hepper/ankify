#include "Card.h"

#include <iostream>

// constructs a new card consisting of a front and back
Card::Card(const std::string& front, const std::string& back) {
    this->front = front;
    this->back = back;
}

std::string Card::getFront() {
    return front;
}

std::string Card::getBack() {
    return back;
}