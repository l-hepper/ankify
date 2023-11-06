#ifndef _CARD_H_
#define _CARD_H_

#include <iostream>

class Card {
    private:
        string front;
        string back;

    public:
        Card(string front, string back);
        string getFront();
        string getBack();

};

#endif